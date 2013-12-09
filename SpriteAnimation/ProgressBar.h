#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
typedef void (__thiscall GamePanel::*CallBack)(void);

class ProgressBar : public GuiElement
{
public:
	ProgressBar(float* percent,sf::Sprite* relative);
	ProgressBar(int x, int y, int length, float* percent);
	ProgressBar();
	void Update(sf::RenderTexture&);
	void Update(GamePanel*);
	void SetPercent(float*);
	bool stationary;
	float GetPercent();
protected:
	sf::Sprite* relative;
	float* percent;
	sf::Transformable* fg;
	sf::RectangleShape foregroundRect;
	sf::RectangleShape background;
	sf::Vector2i offset;
	void SetBarPosition(sf::Vector2f);
};

#endif
