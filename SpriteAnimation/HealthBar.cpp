#include "HealthBar.h"

HealthBar::HealthBar(float* percent, sf::Sprite* relative) : Bar(0,0,percent,32,"blank.png","blank.png"){
	this->relative = relative;
	backgroundRect = sf::RectangleShape(sf::Vector2f(26,2));
	backgroundRect.setFillColor(sf::Color(255,0,0,255));
	backgroundRect.setOutlineColor(sf::Color::Black);
	backgroundRect.setOutlineThickness(1);
	foregroundRect = sf::RectangleShape(sf::Vector2f(26,2));
	foregroundRect.setFillColor(sf::Color(0,255,0,255));
	foregroundRect.setOutlineColor(sf::Color::Black);
	foregroundRect.setOutlineThickness(1);
	foregroundRect.setScale(*percent,1.f);
};

void HealthBar::Update(GamePanel* panel){
	if(percent > 0)
	    foregroundRect.setScale(*percent,1.f);
	SetBarPosition(sf::Vector2f(relative->getPosition().x + 4,relative->getPosition().y - foregroundRect.getSize().y));
	Drawn::DrawOther(&backgroundRect,panel);
    	Drawn::DrawOther(&foregroundRect,panel);
};

void HealthBar::SetBarPosition(sf::Vector2f pos){
	backgroundRect.setPosition(pos);
	foregroundRect.setPosition(pos);
};