#ifdef LINUX_VS
#	include "../lib_curl_linux/include/curl/curl.h"
#elif LINUX_VS_UNIFIED
#	include "../libcurl_src/include/curl/curl.h"
#else
#	include <curl/curl.h>
#endif

#include <string>

class HttpClient
{
public:
    static HttpClient* GetInstance()
    {
        if (ms_instance == nullptr)
        {
            ms_instance = new HttpClient();
        }
        return ms_instance;
    }

    std::string Get(const std::string& url);
    std::string Put(const std::string& url, const std::string& data);
    std::string Post(const std::string& url, const std::string& data);
private:
    struct MemoryStruct 
    {
        char* memory;
        size_t size;
    };

    struct WriteThis
    {
        const char* memory;
        int sizeleft;
    };

    CURL* Config();
    static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);
    static size_t ReadMemoryCallback(void *ptr, size_t size, size_t nmemb, void *userp);
private:
    static HttpClient* ms_instance;

    MemoryStruct m_memoryStruct;
};