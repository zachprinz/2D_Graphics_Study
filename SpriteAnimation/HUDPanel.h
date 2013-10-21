#ifndef HUDPANEL_H
#define HUDPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "LevelSet.h"
#include "Combatant.h"
#include "Item.h"

class HUDPanel : public GamePanel
{
public:
	HUDPanel(Combatant*, int,int);
	Combatant* target;
	void UpdateUserImage();
	static HUDPanel* instance;
	static HUDPanel* instanceEnemy;
private:
	void SetUp();
};

#endif