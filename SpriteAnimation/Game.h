#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "RoomTile.h"
#include "Room.h"
#include "User.h"
#include "Enemy.h"
#include "GroundItem.h"
#include "Bank.h"
#include "SpritePanel.h"
#include "InventoryPanel.h"
#include "Label.h"
#include "RClickMenu.h"
#include <iostream>
#include "BankPanel.h"
#include "Button.h"
#include <MapLoader.h>
#include "SlicedSprite.h"
#include "ActionBar.h"
#include "StatsPanel.h"
#include "ProgressBar.h"
#include "HUDPanel.h"
#include "TextPanel.h"
#include "Clock.h"

class Game
{
public:
	Game();
	void Update();
	static bool run;
	void Load();
	static bool mouseIsPressed;
private:
	enum State{LogOn,GamePlay};
	State gameState;
	void StartLogOnScreen();
	void CheckForInput();
	void UpdatePanels();
	void CreatePanels();
	void OnStart();
	void HandleMouseClick(sf::Event);
	void HandleMouseMovement(sf::Event);
	void HandleMouseScroll(sf::Event);
	TextPanel* textPanel;
	SpritePanel* spritePanel;
	ActionBar* actionBar;
	StatsPanel* statsPanel;
	HUDPanel* hudPanel;
	sf::RenderWindow* window;
};
#endif