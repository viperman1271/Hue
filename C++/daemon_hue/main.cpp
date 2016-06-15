#include "Daemon.h"
#include "IniFile.h"
#include "LibHue.h"

#include <iostream>

void RegistationError(int error)
{
    if (error == 101)
    {
        std::cout << "Press the button on the link bridge" << std::endl;
    }
}

void ExceptionHandler()
{
    std::cerr << "Unhandled exception caught" << std::endl;
    abort();
}

int main()
{
    std::set_terminate(ExceptionHandler);

    LibHue::Initialize(RegistationError);

	if (IniFile::Init())
	{
		return -1;
	}
	return Daemon::Run();
}