#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class ErrorMessageManager
{
public:
	ErrorMessageManager();
	~ErrorMessageManager();

	static void WriteErrorMessageToConsole(char* userMessage);
};
