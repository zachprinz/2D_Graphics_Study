#ifndef MAPPANEL_H
#define MAPPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "InventoryContainer.h"

class MapPanel : public GamePanel
{
public:
	MapPanel(int,int);
	MapPanel();
	static MapPanel* instance;
	void AddElement(std::string,Drawn*);
	sf::View view;
	void UpdateElements();
	sf::RectangleShape box;
	sf::FloatRect GetMapViewRect();
	sf::FloatRect mapRect;
	bool CheckUpdate();
};

#endif