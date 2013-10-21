#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
typedef void (__thiscall GamePanel::*CallBack)(void);


class Button : public GuiElement
{
public:
	Button(int,int,sf::Texture,sf::Texture);
	Button(int,int,std::string,sf::Texture);
	Button(int,int,std::string,std::string);
	void Update(sf::RenderTexture&);
	void OnClick();
	void SetScale(float,float);
	static sf::Texture* circleButtonBackground;
	static sf::Texture* x;
	static void OnStart();
	void SetFunction(std::string);
	void SetTarget(GamePanel*);
	void CenterForeground();
	void OnHover(bool);
protected:
	GamePanel* target;
	std::string function;
};

#endif
