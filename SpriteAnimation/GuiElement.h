#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "ARectangle.h"

class GuiElement : public RClickable
{
public:
	GuiElement(int,int,std::string textureName,std::string fgTextureName);
	GuiElement(int,int,SlicedSprite* textureName,std::string fgTextureName);
	void SetForegroundSprite(std::string);
	virtual void Update(GamePanel*);
	virtual void OnClick();
	virtual void OnHover(bool);
	virtual void OnMousePress();
	virtual void OnMouseRelease();
	virtual void SetPosition(sf::Vector2f);
	Drawn* foreground;
	void SetOrgin(int,int);
	void CenterForeground();
	bool pressed;
protected:
	bool isSliced;
	SlicedSprite* base;
	ARectangle elementBounds;
};

#endif