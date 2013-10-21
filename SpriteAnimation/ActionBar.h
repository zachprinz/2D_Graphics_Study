#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"

class ActionBar : public GamePanel
{
public:
	ActionBar(int,int);
	ActionBar();
	static ActionBar* instance;
	void AddElement(std::string,Drawn*);
	void UpdateElements();
	void SetUp();
	void OnButtonEvent(std::string);
	bool CheckUpdate();
private:
	std::vector<sf::RectangleShape*> sheets;
};

#endif