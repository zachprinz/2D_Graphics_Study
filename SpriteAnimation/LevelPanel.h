#ifndef LEVELPANEL_H
#define LEVELPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "EquipedContainer.h"
#include "LevelSet.h"

class LevelPanel : public GamePanel
{
public:
	LevelPanel(int,int);
	LevelPanel();
	static LevelPanel* instance;
	void AddElement(std::string,Drawn*);
	bool CheckUpdate();
	void OnButtonEvent(std::string);
	void ResetButtonPositions();
private:
	void SetUp();
};

#endif