#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <typeinfo>

class RpcValue
{
public:
	RpcValue()
		: m_rawValue(nullptr)
	{

	}

	const std::string& GetType() const { return m_type; }
	const std::string& GetValue() const { return m_value; }

	template<class T>
	void SetType()
	{
		m_type = typeid(T).name();
	}


	template<class T>
	bool IsSameType() const
	{
		return m_type == typeid(T).name();
	}

	template<class T>
	bool GetValue(T& val) const
	{
		static_assert(std::is_pod<T>::value, "POD types only");
		if (typeid(T).name() != m_type)
			return false;

		memcpy(&val, m_rawValue, sizeof(T));

		return true;
	}

	template<class T>
	void SetValue(T& val)
	{
		m_rawValue = malloc(sizeof(T));
		memcpy(m_rawValue, &val, sizeof(T));
		m_type = typeid(T).name();
	}

	template<class T>
	static RpcValue* Create(T& value)
	{
		RpcValue* r = new RpcValue();
		r->SetValue<T>(value);
		return r;
	}
private:
	std::string m_value;
	std::string m_type;
	void* m_rawValue;
};

using RpcParamList = std::vector<RpcValue*>;
