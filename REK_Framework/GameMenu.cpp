#pragma once
#include "GameMenu.h"


GameMenu::GameMenu()
{
	gameMenuItems.clear();
	gameMenuItems[0] = PLAY;
	gameMenuItems[1] = CREDITS;
	gameMenuItems[2] = QUITGAME;

	GameMenuLevel = 0;

	selectedItem = PLAY;
	selectedItemIndex = 0;

	background = nullptr;

	drawTextSrvc = new DrawTextService();
	DrawGameButtonLabelSrvc = new DrawGameButtonLabelService();

	backgroundPositionX = (SCREEN_WIDTH / 4);
	backgroundPositionY = (SCREEN_HEIGHT / 8);
}

GameMenu::~GameMenu()
{
	if (background != nullptr) SDL_DestroyTexture(background);
	delete drawTextSrvc;
	delete DrawGameButtonLabelSrvc;
}

void GameMenu::Draw()
{
	if (GameMenuLevel == 0)
	{
		DrawMainMenu();
	}
	else
	{
		switch (selectedItem)
		{
		case CREDITS:
			DrawCredits();
			break;
		}
	}
}

void GameMenu::NavigateDown()
{
	if (selectedItemIndex < gameMenuItems.size() - 1 && GameMenuLevel == 0)
	{
		selectedItemIndex++;
		selectedItem = gameMenuItems[selectedItemIndex];
	}
}

void GameMenu::NavigateUp()
{
	if (selectedItemIndex > 0 && GameMenuLevel == 0)
	{
		selectedItemIndex--;
		selectedItem = gameMenuItems[selectedItemIndex];
	}
}

void GameMenu::SelectItemMenu()
{
	switch (selectedItem)
	{
	case PLAY:
		break;
	case CREDITS:
		GameMenuLevel = 1;
		break;
	case QUITGAME:
		SDL_Event quitGame;
		quitGame.type = SDL_QUIT;
		SDL_PushEvent(&quitGame);
		break;
	}
}

void GameMenu::MenuBack()
{
	switch (selectedItem)
	{
	case PLAY:
	case QUITGAME:
		break;
	case CREDITS:
		GameMenuLevel = 0;
		break;
	}
}

bool GameMenu::MustDestroyGameMenuOnSelect() const
{
	return (selectedItem == PLAY || selectedItem == QUITGAME);
}

bool GameMenu::MustDestroyGameMenuOnBack() const
{
	return GameMenuLevel == 0;
}

SDL_Texture* GameMenu::CreateBackground(SDL_Rect* gameMenuPosition)
{
	gameMenuPosition->x = backgroundPositionX;
	gameMenuPosition->y = backgroundPositionY;
	gameMenuPosition->w = (SCREEN_WIDTH / 2);
	gameMenuPosition->h = (SCREEN_HEIGHT / 1.5);

	auto backgroundSurface = SDL_CreateRGBSurface(0, gameMenuPosition->w, gameMenuPosition->h, 32, 0, 0, 0, 0);
	SDL_FillRect(backgroundSurface, nullptr, SDL_MapRGB(backgroundSurface->format, 0x00, 0x00, 0x00));

	background = SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRenderer(), backgroundSurface);

	// Active Alpha Blending (Opacity) to "background" texture
	SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(background, 0xAA);

	SDL_FreeSurface(backgroundSurface);

	return background;
}

void GameMenu::DrawMainMenu()
{
	SDL_Rect* gameMenuPosition = new SDL_Rect();
	background = CreateBackground(gameMenuPosition);

	SDL_RenderCopy(SDLMainObjectsProvider::GetRenderer(), background, nullptr, gameMenuPosition);

	DrawItemsMenu();
	AddValidButton();
	AddBackButton();

	delete gameMenuPosition;
	SDL_DestroyTexture(background);
	background = nullptr;
}

void GameMenu::DrawItemsMenu() const
{
	int x = backgroundPositionX + 20;
	int y = backgroundPositionY + 20;

	DrawItemMenu("Play", PLAY, x, y);
	y += 40;
	DrawItemMenu("Credits", CREDITS, x, y);
	y += 40;
	DrawItemMenu("Quit game", QUITGAME, x, y);
}

void GameMenu::DrawItemMenu(const char* itemMenuName, GameMenuItem gameMenuItem, int x, int y) const
{
	SDL_Color textColorSelected = { 255, 255, 0 };

	if (selectedItem == gameMenuItem)
	{
		drawTextSrvc->DrawTextWithColor(itemMenuName, x, y, &textColorSelected);
	}
	else
	{
		drawTextSrvc->DrawText(itemMenuName, x, y);
	}
}

void GameMenu::DrawCredits()
{
	SDL_Rect* gameMenuPosition = new SDL_Rect();
	background = CreateBackground(gameMenuPosition);
	SDL_RenderCopy(SDLMainObjectsProvider::GetRenderer(), background, nullptr, gameMenuPosition);

	int x = backgroundPositionX + 40;
	int y = backgroundPositionY + 40;

	drawTextSrvc->DrawText("Game made by", x, y);

	y += 50;

	drawTextSrvc->DrawTextWithSize("REK", x, y, 72);
	
	AddBackButton();

	delete gameMenuPosition;
	SDL_DestroyTexture(background);
	background = nullptr;
}

void GameMenu::AddBackButton() const
{
	int textureWidth, textureHeight;
	SDL_QueryTexture(background, nullptr, nullptr, &textureWidth, &textureHeight);
	int x = backgroundPositionX + (textureWidth - (textureWidth / 3.5));
	int y = backgroundPositionY + (textureHeight - (textureHeight / 8));

	DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::BButton, "Back", x, y);
}

void GameMenu::AddValidButton() const
{
	int textureWidth, textureHeight;
	SDL_QueryTexture(background, nullptr, nullptr, &textureWidth, &textureHeight);
	int x = backgroundPositionX + 5;
	int y = backgroundPositionY + (textureHeight - (textureHeight / 8));

	DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::AButton, "Select", x, y);
}