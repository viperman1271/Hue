#include <iostream>

namespace libhue_callbacks
{
	void RegistationError(int error)
	{
		if (error == 101)
		{
			std::cout << "Press the button on the link bridge" << std::endl;
		}
	}
}