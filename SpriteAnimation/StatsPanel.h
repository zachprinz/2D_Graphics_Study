#ifndef STATSPANEL_H
#define STATSPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "LevelSet.h"
#include "Item.h"
#include "pugixml\pugixml.hpp"


class Combatant;
class StatsPanel : public GamePanel
{
public:
	StatsPanel(int,int);
	static StatsPanel* instance;
	void SetItem(Item* item);
	void SetCombatant(Combatant* combatant);
	void SetLevel(std::string);
	std::string currentName;
	void UpdateElements();
	bool CheckUpdate();
	void OnButtonEvent(std::string);
private:
	ElementList itemMap;
	ElementList combatantMap;
	ElementList levelMap;
	float mainLevelPercent;
	std::vector<float> subLevelPercents;
	void SetUp();
	void SetUpItemMap();
	void SetUpLevelMap();
	void SetUpCombatantMap();
};

#endif