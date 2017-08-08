#pragma once
#include "GamepadConfiguration.h"


namespace REKFramework
{
	GamepadConfiguration::GamepadConfiguration()
	{
		gamepad = nullptr;
	}


	GamepadConfiguration::~GamepadConfiguration()
	{
		
	}


	void GamepadConfiguration::PlugGamepad()
	{
		if (SDL_IsGameController(0))
		{
			gamepad = std::unique_ptr<SDL_GameController, SdlDeleter>(SDL_GameControllerOpen(0), SdlDeleter());
			if (gamepad != nullptr)
			{
				DisplayDebugInformations();
			}
		}
	}

	void GamepadConfiguration::UnplugGamepad()
	{
		if (gamepad != nullptr)
		{
			std::cout << "Game controller " << SDL_GameControllerName(gamepad.get()) << "Removed" << std::endl << std::endl;
			gamepad.reset();
		}
	}

	void GamepadConfiguration::DisplayDebugInformations() const
	{
		std::cout << "Gamepad controller informations : " << std::endl;
		std::cout << "Name : " << SDL_GameControllerName(gamepad.get()) << std::endl << std::endl;
	}
}
