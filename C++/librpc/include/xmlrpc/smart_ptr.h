#pragma once

namespace xmlrpc
{
template<class T>
class smart_ptr
{
public:
	smart_ptr() = delete;

	explicit smart_ptr(T* in_ptr)
	: m_ptr(in_ptr)
	{
	}
private:
	T* m_ptr;
};
}
