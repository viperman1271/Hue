#include "HttpClient.h"

HttpClient* HttpClient::ms_instance = nullptr;

CURL* HttpClient::Config()
{
    CURLcode res;

    if (m_memoryStruct.size > 0)
    {
        free(m_memoryStruct.memory);
        m_memoryStruct.memory = nullptr;
        m_memoryStruct.size = 0;
    }

    m_memoryStruct.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
    m_memoryStruct.size = 0;    /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    CURL* curl = curl_easy_init();

    /* specify URL to get */
    //res = curl_easy_setopt(curl, CURLOPT_URL, "https://www.meethue.com/api/nupnp");

    /* send all data to this function  */
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    if (res != CURLE_OK)
    {
        return nullptr;
    }

    /* we pass our 'chunk' struct to the callback function */
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&m_memoryStruct);
    if (res != CURLE_OK)
    {
        return nullptr;
    }

    /* some servers don't like requests that are made without a user-agent
    field, so we provide one */
    res = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    if (res != CURLE_OK)
    {
        return nullptr;
    }

    return curl;
}

size_t HttpClient::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

std::string HttpClient::Get(const std::string& url)
{
    CURL* curl = Config();

    CURLcode res = curl_easy_setopt(curl, CURLOPT_URL, url);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return m_memoryStruct.memory;
}

std::string HttpClient::Post(const std::string& url, const std::string& data)
{
    CURL* curl = Config();
    if (!curl)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    CURLcode res = curl_easy_setopt(curl, CURLOPT_POST, 1L);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_setopt(curl, CURLOPT_URL, url);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return m_memoryStruct.memory;
}

std::string HttpClient::Put(const std::string& url, const std::string& data)
{
    CURL* curl = Config();
    if (!curl)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    CURLcode res = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }
    
    res = curl_easy_setopt(curl, CURLOPT_URL, url);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return m_memoryStruct.memory;
}