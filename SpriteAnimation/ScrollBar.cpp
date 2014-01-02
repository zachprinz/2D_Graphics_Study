#include "ScrollBar.h"
#include "GamePanel.h"
#include "OptionPanel.h"

ScrollBar::ScrollBar(int x, int y, int length, float* percent) : Bar(x,y,percent,length,new SlicedSprite(x,y,length),"slider.png"){
    isVerticle = false;
    isHorizontle = true;
    foreground->SetPosition(sf::Vector2f(x + 15 + ((length - 15) * (*percent)),y));
    this->percent = percent;
    SetHorizontle();
    oPos = sf::Vector2f(x,y);
    SetDrawBounds(true);
    foreground->GetSprite()->setOrigin(0,7);
    texturePart = sf::IntRect(0,0,length,30);
};
void ScrollBar::Update(GamePanel* panel){
	//AABB temp = GetBounds(OptionPanel::instance->GetRenderPanel().getView());
	//std::cout << "Lower( X: " << temp.GetLowerBound().x << " Y: " << temp.GetLowerBound().y << " ) Upper( X: " << temp.GetUpperBound().x << " Y: " << temp.GetUpperBound().y << ")" << std::endl;
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
		if(tempPast > fullscale)
			tempPast = fullscale;
		(*percent) = tempPast / fullscale;
	}
	if(isVerticle){
		foreground->SetPosition(sf::Vector2f(oPos.x,GetPosition().y + ((*percent) * fullscale)));
	}
	if(isHorizontle){
		foreground->SetPosition(sf::Vector2f(oPos.x + 22 + ((*percent) * (fullscale - 60)),oPos.y));
	}
	AABB tempBounds = ((Drawn*)base)->GetBounds();
	base->Update(panel);
	foreground->Draw(panel);
};
void ScrollBar::SetHorizontle(){
    isHorizontle = true;
    isVerticle = false;
    base->SetRotation(0);
    foreground->SetRotation(90);
    foreground->SetPosition(sf::Vector2f(GetPosition().x + ((*percent) * fullscale),GetPosition().y));
};
void ScrollBar::SetVerticle(){
    isHorizontle = false;
    isVerticle = true;
    foreground->SetRotation(0);
    base->SetRotation(90);
    foreground->SetPosition(sf::Vector2f(GetPosition().x,GetPosition().y + ((*percent) * fullscale)));
};