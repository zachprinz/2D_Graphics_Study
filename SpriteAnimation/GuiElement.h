#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "ARectangle.h"

class GuiElement : public RClickable
{
public:
	GuiElement(int,int,sf::Texture);
	GuiElement(int,int,std::string textureName);
	GuiElement(int,int,sf::Texture,sf::Texture);
	GuiElement(int,int,std::string textureName,std::string fgTextureName);
	GuiElement(int,int,std::string,sf::Texture);
	GuiElement(int,int,sf::Texture,std::string);
	void SetForegroundSprite(sf::Texture);
	void SetForegroundSprite(std::string);
	void SetForegroundSprite(sf::Texture,sf::IntRect);
	void SetBackgroundSprite(sf::Texture);
	virtual void Update(sf::RenderTexture&);
	virtual void Update(GamePanel*);
	virtual void OnClick();
	virtual void OnHover(bool);
	ARectangle* GetBounds();
	virtual void SetLocation(float,float);
	//sf::Sprite foregroundSprite;
	Drawn* foreground;
	void SetOrgin(int,int);
protected:
	ARectangle elementBounds;
	//sf::Texture foregroundSpriteTexture;
};

#endif