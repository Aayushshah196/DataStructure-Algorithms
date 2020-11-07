#include <stdexcept>
#include <iostream>
#include "Animation.h"

int main()
{
	try
	{
		Animation animation;
		animation.run();
	}
	catch (std::exception & e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}