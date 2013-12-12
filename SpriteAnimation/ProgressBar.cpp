#include "ProgressBar.h"
#include <iostream>

ProgressBar::ProgressBar(float* percent,sf::Sprite* relative) : GuiElement(0,0,"blank.png","blank.png"){
	this->percent = percent;
	this->relative = relative;
	background = sf::RectangleShape(sf::Vector2f(26,2));
	background.setFillColor(sf::Color(255,0,0,255));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(1);
	foregroundRect = sf::RectangleShape(sf::Vector2f(26,2));
	foregroundRect.setFillColor(sf::Color(0,255,0,255));
	foregroundRect.setOutlineColor(sf::Color::Black);
	foregroundRect.setOutlineThickness(1);
	foregroundRect.setScale(*percent,1.f);
	fg = &foregroundRect;
	stationary = false;
};
ProgressBar::ProgressBar(int x, int y, int length, float* percent) : GuiElement(x,y,new SlicedSprite(x,y,length),"green.png"){
	foreground->SetScale(sf::Vector2f(((float)(length-50))/3.0f,16.75));
	fullScale = 4 * (length-50)/4.0f;
	foreground->SetPosition(sf::Vector2f(x + 22,y + 3));
	fg = &(foregroundRect);
	this->percent = percent;
	stationary = true;
};
ProgressBar::ProgressBar() : GuiElement(0,0,"blank.png","blank.png") {

};
void ProgressBar::Update(GamePanel* panel){
	if(!stationary){
		if(percent > 0)
			foregroundRect.setScale(*percent,1.f);
		SetBarPosition(sf::Vector2f(relative->getPosition().x + 4,relative->getPosition().y - foregroundRect.getSize().y));
		Drawn::DrawOther(&background,panel);
		Drawn::DrawOther(&foregroundRect,panel);
	}
	else{
		if(percent > 0){
			foreground->SetScale(sf::Vector2f((*percent) * fullScale,foreground->GetScale().y));
		}
		base->Update(panel);
		foreground->Draw(panel);
	}
};
float ProgressBar::GetPercent(){
	return *percent;
};
void ProgressBar::SetBarPosition(sf::Vector2f pos){
	if(!stationary){
		background.setPosition(pos);
		foregroundRect.setPosition(pos);
	}
	else{
		sprite.setPosition(pos);
		foreground->GetSprite()->setPosition(sf::Vector2f(pos.x + 25,pos.y));
	}
};
void ProgressBar::SetPercent(float* newPercent){
	percent = newPercent;
};