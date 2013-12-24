#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "Bar.h"
typedef void (__thiscall GamePanel::*CallBack)(void);

class ProgressBar : public Bar
{
public:
	ProgressBar(int x, int y, int length, float* percent);
	void Update(GamePanel*);
	sf::Transformable* fg;
	void SetBarPosition(sf::Vector2f);
};

#endif
