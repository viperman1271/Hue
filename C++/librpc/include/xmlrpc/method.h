#pragma once

#include <xmlrpc/param_list.h>
#include <xmlrpc/value.h>

#include <string>
#include <memory>

namespace xmlrpc
{
class method
{
public:
	virtual void execute(param_list const& paramList, value& returnVal) = 0;
	const std::string& name() const { return m_name; }

protected:
	method(const std::string& help, const std::string& name);
	virtual ~method();

private:
	const std::string m_help;
	const std::string m_name;
};

template<class return_type, class...args>
class remote_method
{
public:
	virtual return_type call(args... arguments) = 0;
};

using methodPtr = std::shared_ptr<xmlrpc::method>;
} //xmlrpc