#include <xmlrpc/method.h>

namespace xmlrpc
{
//////////////////////////////////////////////////////////////////////////
method::method(const std::string& help, const std::string& name) 
: m_help(help)
, m_name(name)
{

}

//////////////////////////////////////////////////////////////////////////
method::~method()
{

}
} //xmlrpc
