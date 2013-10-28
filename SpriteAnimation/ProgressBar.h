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
	void SetPercent(float*);
	static void SetUp();
	static sf::Texture CreateBackground(int length);
	static sf::Texture CreateTiledTexture(int length, sf::Texture);
	bool stationary;
	float GetPercent();
protected:
	static sf::Texture blankText;
	static sf::Texture backgroundLeft;
	static sf::Texture backgroundRight;
	static sf::Texture backgroundCenter;
	static sf::Texture foregroundCenter;
	sf::Sprite* relative;
	float* percent;
	sf::Transformable* fg;
	sf::RectangleShape foregroundRect;
	sf::RectangleShape background;
	sf::Vector2i offset;
	void SetBarPosition(sf::Vector2f);
};

#endif
