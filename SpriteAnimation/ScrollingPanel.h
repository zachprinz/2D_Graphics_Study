#ifndef SCROLLINGPANEL_H
#define SCROLLINGPANEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "GamePanel.h"
#include "LevelSet.h"
#include "Item.h"

class ScrollingPanel : public GamePanel
{
public:
	ScrollingPanel(int,int,int,int);
	ScrollingPanel();
	void OnClick(sf::Vector2i);
	void OnRClick(sf::Vector2i);
	void ScrollDown();
	void ScrollUp();
	virtual bool CheckUpdate();
	void SetPosition(int, int);
	void Update(sf::RenderWindow&);
	Rectangle* GetBounds();
private:
	sf::View scrollView;
	sf::Vector2f visibleSize;
	sf::Texture backgroundWindowTexture;
	sf::Sprite* backgroundWindowSprite;
};

#endif