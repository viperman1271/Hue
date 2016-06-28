#pragma once

#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <typeinfo>

namespace xmlrpc
{
class value
{
public:
	value();

	const std::string& get_type() const { return m_type; }
	const std::string& get_value() const { return m_value; }

	template<class T>
	void set_type()
	{
		static_assert(std::is_pod<T>::value, "POD types only");
		
		m_type = typeid(T).name();
	}


	template<class T>
	bool is_same_type() const
	{
		static_assert(std::is_pod<T>::value, "POD types only");

		return m_type == typeid(T).name();
	}

	template<class T>
	bool get_value(T& val) const
	{
		static_assert(std::is_pod<T>::value, "POD types only");

		if (typeid(T).name() != m_type)
			return false;

		memcpy(&val, m_rawValue, sizeof(T));

		return true;
	}

	template<class T>
	void set_value(T& val)
	{
		static_assert(std::is_pod<T>::value, "POD types only");

		m_rawValue = malloc(sizeof(T));
		memcpy(m_rawValue, &val, sizeof(T));
		m_type = typeid(T).name();
	}

	template<class T>
	static value* create(T& in_value)
	{
		static_assert(std::is_pod<T>::value, "POD types only");

		value* r = new value();
		r->set_value<T>(in_value);
		return r;
	}
private:
	std::string m_value;
	std::string m_type;
	void* m_rawValue;
};
} //xmlrpc
