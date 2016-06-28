namespace xmlrpc
{
template<class T>
void registry::serializer::serialize(const T& value)
{
	static_assert(false, "Not implemented for this type");
}

template<>
void registry::serializer::serialize(const int& value)
{
	char buffer[12];
	_itoa_s(value, buffer, 10);
	serialized.push_back(buffer);
}

template<class T, class... Args>
void registry::serializer::serialize(const T& value, Args... args)
{
	serialize(value);
	serialize(args...);
}
} //xmlrpc
