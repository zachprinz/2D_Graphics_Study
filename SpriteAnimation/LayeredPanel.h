#ifndef LayeredPanel_H
#define LayeredPanel_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"

class LayeredPanel : public GamePanel
{
public:
	static LayeredPanel* instance;
	LayeredPanel(std::vector<GamePanel*>);
	LayeredPanel();
	std::vector<GamePanel*> panels;
	void Update();
	int currentPanel;
	void AddElement(std::string,Drawn*);
	void SetUp();
	void OnButtonEvent(std::string);
	static sf::Vector2i GetLayeredPanelSize(std::vector<GamePanel*>);
	void UpdatePanelsPosition();
	void SetPosition(int x, int y);
	void UpdateCurrentPanel();
	void OnHover(sf::Vector2i);
private:
	std::vector<sf::RectangleShape*> sheets;
	sf::Vector2i largestSubpanelSize;
};

#endif