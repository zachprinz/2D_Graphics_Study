#ifndef LayeredPanel_H
#define LayeredPanel_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"

class LayeredPanel : public GamePanel
{
public:
	LayeredPanel(std::vector<GamePanel*>);
	LayeredPanel();
	std::vector<GamePanel*> panels;
	int currentPanel;
	void Update(sf::RenderWindow&);
	static LayeredPanel* instance;
	void AddElement(std::string,Drawn*);
	void UpdateElements();
	void SetUp();
	void OnButtonEvent(std::string);
	bool CheckUpdate();
	static sf::Vector2i GetLayeredPanelSize(std::vector<GamePanel*>);
	void UpdatePanelsPosition();
	void SetPosition(int x, int y);
private:
	std::vector<sf::RectangleShape*> sheets;
	sf::Vector2i largestSubpanelSize;
};

#endif