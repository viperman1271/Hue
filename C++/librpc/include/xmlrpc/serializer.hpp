namespace xmlrpc
{
template<class T>
void serializer::serialize(const T& value)
{
	
}

// template<>
// void serializer::serialize(const int& value)
// {
// 	char buffer[12];
// 	_itoa_s(value, buffer, 10);
// 	serialized.push_back(buffer);
// }

template<class T, class... Args>
void serializer::serialize(const T& value, Args... args)
{
	serialize(value);
	serialize(args...);
}
} //xmlrpc
