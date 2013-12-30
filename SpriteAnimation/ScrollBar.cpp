#include "ScrollBar.h"
#include "GamePanel.h"

ScrollBar::ScrollBar(int x, int y, int length, float* percent) : Bar(x,y,percent,new SlicedSprite(x,y,length),"slider.png"){
    isVerticle = false;
    isHorizontle = true;
    foreground->SetPosition(sf::Vector2f(x + 15 + (length * (*percent)),y));
    this->percent = percent;
};
void ScrollBar::Update(GamePanel* panel){
	if(pressed){
		float tempPast = 0.0f;
	    if(isVerticle){
		tempPast = sf::Mouse::getPosition().y - (GetPosition().y + GetPosition().x + panel->GetPosition().y);
		}
	    if(isHorizontle){
		tempPast = sf::Mouse::getPosition().x - (GetPosition().x + panel->GetPosition().x);
		}
		if(tempPast < 0)
			tempPast = 0;
		if(tempPast > length)
			tempPast = length;
		(*percent) = tempPast / length;
	}
	if(isVerticle){
		foreground->SetPosition(sf::Vector2f(GetPosition().x,GetPosition().y + ((*percent) * length));
	}
	if(isHorizontle){
		foregorund->SetPosition(sf::Vector2f(GetPosition().x + ((*percent) * length),GetPosition().y));
	}
	base->Update(panel);
	foreground->Draw(panel);
};
void ScrollBar::SetHorizontle(){
    isHorizontle = true;
    isVerticle = false;
    base->SetRotation(0);
    foreground->SetRotation(0);
    foregorund->SetPosition(sf::Vector2f(GetPosition().x + ((*percent) * length),GetPosition().y));
};
void ScrollBar::SetVerticle(){
    isHorizontle = false;
    isVerticle = true;
    foreground->SetRotation(90);
    base->SetRotation(90);
    foreground->SetPosition(sf::Vector2f(GetPosition().x,GetPosition().y + ((*percent) * length));
};