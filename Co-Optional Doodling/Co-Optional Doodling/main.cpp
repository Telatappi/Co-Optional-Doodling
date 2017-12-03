#include "Core.h"
#include <iostream>

int main(int argc, char* argv)
{

	core::InitGame();
	
	while (!core::sceneManager.LoopActiveScene());
	{
	}

	fflush(stdin);
	getchar();
	return 0;
}

