#include "ProgressBar.h"
#include <iostream>

ProgressBar::ProgressBar(int x, int y, int length, float* percent) : Bar(x,y,percent,length,new SlicedSprite(x,y,length),"green.png"){
	foreground->SetScale(sf::Vector2f(((float)(length-50))/3.0f,16.75));
	fullscale = 4 * (length-50)/4.0f;
	foreground->SetPosition(sf::Vector2f(x + 22,y + 3));
	this->percent = percent;
};

void ProgressBar::Update(GamePanel* panel){
	if(percent > 0)
	    foreground->SetScale(sf::Vector2f((*percent) * fullscale,foreground->GetScale().y));
	base->Update(panel);
	foreground->Draw(panel);
};
void ProgressBar::SetBarPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
	foreground->GetSprite()->setPosition(sf::Vector2f(pos.x + 25,pos.y));
};