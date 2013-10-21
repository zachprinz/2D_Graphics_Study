#ifndef RCLICKABLE_H
#define RCLICKABLE_H

#include <vector>
#include "Drawn.h"
#include <SFML/Graphics.hpp>

class RClickMenu;
class GamePanel;
class RClickable : public Drawn
{
public:
	RClickable(std::string);
	RClickable(sf::Texture);
	RClickable();
	virtual void OnClick();
	virtual void OnRClick(sf::Vector2i,GamePanel*);
	virtual void OnHover(bool);
	void AddRClickOption(int);
	void Update(sf::RenderTexture&);
	void EnableRClick(std::string);
	void DisableRClick();
	bool GetRClickEnabled();
	virtual void OnMenuSelection(std::string);
protected:
	std::string name;
	bool isMenuOpen;
	bool rClickEnabled;
	std::vector<int> rClickOptions;
};

#endif