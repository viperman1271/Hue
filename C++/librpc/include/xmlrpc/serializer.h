#pragma once

namespace xmlrpc
{
class serializer
{
public:
	template<class T>
	void serialize(const T& value);

	template<class T, class... Args>
	void serialize(const T& value, Args... args);

	const std::vector<std::string>& get_serialized() const { return serialized; }

private:
	std::vector<std::string> serialized;
};
}

#include <xmlrpc/serializer.hpp>