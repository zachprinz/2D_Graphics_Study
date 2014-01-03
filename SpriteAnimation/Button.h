#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
//typedef void (__thiscall GamePanel::*CallBack)(void);


class Button : public GuiElement
{
public:
	Button(int,int,std::string,std::string);
	Button(int,int,SlicedSprite::SpriteStyle,std::string);
    	Button(int,int,std::string);
	Button(int,int,std::string,std::string, bool);
	void Update(GamePanel*);
	void OnClick();
	void SetScale(float,float);
	static std::string circleButtonBackground;
	static std::string x;
	static void OnStart();
	void SetFunction(std::string);
	void SetTarget(GamePanel*);
	void SetTarget(GuiElement*);
	void OnHover(bool);
	void SetMoveOnHover(bool);
	void SetHoverMovePosition(sf::Vector2i);
	static SlicedSprite* GetSlicedSpriteForText(int,int,std::string);
protected:
	bool hasText;
	sf::Vector2i hoverMovePosition;
	sf::Vector2i hoverMoveTarget;
	bool moveOnHover;
	GamePanel* target;
	GuiElement* elementTarget;
	std::string function;
};

#endif
