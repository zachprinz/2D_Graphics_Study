#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "Rectangle.h"

class GuiElement : public RClickable
{
public:
	GuiElement(int,int,sf::Texture,sf::Sprite*);
	GuiElement(int,int,std::string,sf::Sprite*);
	GuiElement(int,int,sf::Texture);
	GuiElement(int,int,std::string textureName);
	void SetForegroundSprite(sf::Texture);
	void SetForegroundSprite(sf::Texture,sf::IntRect);
	void SetBackgroundSprite(sf::Texture);
	virtual void Update(sf::RenderTexture&);
	virtual void OnClick();
	virtual void OnHover(bool);
	Rectangle* GetBounds();
	virtual void SetLocation(float,float);
	sf::Sprite foregroundSprite;
	void SetOrgin(int,int);
protected:
	Rectangle elementBounds;
	sf::Texture foregroundSpriteTexture;
};

#endif