#include "Daemon.h"
#include "IniFile.h"

int main()
{
	if (IniFile::Init())
	{
		return -1;
	}
	return Daemon::Run();
}