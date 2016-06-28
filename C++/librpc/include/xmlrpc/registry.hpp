namespace xmlrpc
{
template<class... T>
void registry::callMethod(const std::string& methodName, T... args)
{
	serializer s;
	s.serialize(args...);
}
} //xmlrpc