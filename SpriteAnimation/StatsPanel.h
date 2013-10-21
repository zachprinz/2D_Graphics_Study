#ifndef STATSPANEL_H
#define STATSPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "LevelSet.h"
#include "Item.h"

class Combatant;
class StatsPanel : public GamePanel
{
public:
	StatsPanel(int,int);
	static StatsPanel* instance;
	void SetItem(Item* item);
	void SetCombatant(Combatant* combatant);
	std::string currentName;
	void UpdateElements();
	bool CheckUpdate();
private:
	ElementList itemMap;
	ElementList combatantMap;
	void SetUp();
	void SetUpItemMap();
	void SetUpCombatantMap();
};

#endif