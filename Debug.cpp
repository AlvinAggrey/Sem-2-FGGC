#include "Debug.h"

void Debug::OutputLog(std::string message)
{
	static int x = 0;
	char sz[1024] = { 0 };
	sprintf_s(sz, "the number is %d \n", x);
	OutputDebugStringA((message + "\n").c_str());
	x++;
}
