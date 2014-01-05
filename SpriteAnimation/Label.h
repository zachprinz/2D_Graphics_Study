#ifndef LABEL_H
#define LABEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiElement.h"

class Label : public GuiElement
{
public:
	enum Fonts{Game};
	Label(int,int,std::string, Fonts, std::string);
	Label(int,int,int,std::string, Fonts, std::string);
	Label(int,int,int,SlicedSprite*,Fonts,std::string);
	void SetText(sf::Text);
	sf::Text* GetText();
	void Update(GamePanel*);
	static void OnStart();
	void SetLocation(float,float);
	static std::vector<sf::Font> fonts;
	void SetTextOffset(float,float);
	void SetTextColor(sf::Color);
	void CenterText();
	void SetText(std::string);
	static int GetPixelLengthOfString(std::string);
	void SetPosition(sf::Vector2f);
protected:
	sf::Text text;
};

#endif