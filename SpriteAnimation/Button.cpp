#include "Button.h"
#include "GamePanel.h"
#include <iostream>
#include "GamePanel.h"
#include "Label.h"


std::string Button::circleButtonBackground = "circlebuttonbackground.png";
std::string Button::x = "x.png";

Button::Button(int x,int y,std::string texture,std::string fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = NULL;
	elementTarget = NULL;
	moveOnHover = false;
	hasText = false;
	CenterForeground();
};
Button::Button(int x, int y,SlicedSprite::SpriteStyle style, std::string str) : GuiElement(x,y,GetSlicedSpriteForText(x,y,str),"blank.png"){
    foreground = new Label(x + 4,y + 2,"blank.png",Label::Fonts::Game,str);
    ((Label*)foreground)->SetText(sf::Text(str,Label::fonts[Label::Fonts::Game],30));
    target = NULL;
    elementTarget = NULL;
    moveOnHover = false;
    isSliced = true;
    hasText = true;
    CenterForeground();
};
Button::Button(int x, int y, std::string str) : GuiElement(x,y,GetSlicedSpriteForText(x,y,str),"blank.png"){
    foreground = new Label(x + 4,y + 2,"blank.png",Label::Fonts::Game,str);
    ((Label*)foreground)->SetText(sf::Text(str,Label::fonts[Label::Fonts::Game],30));
    float textPartWidth = ((Label*)foreground)->GetText()->getGlobalBounds().width;
    float textPartHeight = ((Label*)foreground)->GetText()->getGlobalBounds().height;
    target = NULL;
    elementTarget = NULL;
    moveOnHover = false;
    isSliced = false;
    hasText = true;
};
Button::Button(int x, int y, std::string bg, std::string str,bool idk) : GuiElement(x,y,bg,"blank.png"){
    foreground = new Label(x + 4,y + 2,"blank.png",Label::Fonts::Game,str);
    ((Label*)foreground)->SetText(sf::Text(str,Label::fonts[Label::Fonts::Game],30));
    target = NULL;
    elementTarget = NULL;
    moveOnHover = false;
    isSliced = false;
	hasText = true;
};
SlicedSprite* Button::GetSlicedSpriteForText(int x, int y, std::string str){
    float width = (sf::Text(str,Label::fonts[0],30)).getGlobalBounds().width + 8;
    float height = (sf::Text(str,Label::fonts[0],30)).getGlobalBounds().height + 16;
	return new SlicedSprite(x,y,width,height,SlicedSprite::SpriteStyle::WoodPanel);
};
void Button::Update(GamePanel* panel){
	if(foreground->GetIsMoving())
		foreground->UpdateMove();
	if(foreground->GetIsExpanding()){
		foreground->UpdateExpand();
		CenterForeground();
	}
	if(isSliced)
		base->Update(panel);
	else
		Draw(panel);
	if(hasText)
		foreground->Update(panel);
	else
		foreground->Draw(panel);
};
void Button::OnClick(){
	if(target != NULL)
	    target->OnButtonEvent(function);
	if(elementTarget != NULL)
	    elementTarget->OnButtonEvent(function);
};
void Button::OnStart(){
	circleButtonBackground = "circlebuttonbackground.png";
	x = "x.png";
};
void Button::SetScale(float x,float y){
	foreground->GetSprite()->setScale(x,y);
	sprite.setScale(x,y);
};
void Button::SetFunction(std::string str){
	function = str;
};
void Button::SetTarget(GamePanel* myTarget){
	target = myTarget;
};
void Button::SetTarget(GuiElement* myTarget){
    elementTarget = myTarget;
}
void Button::SetMoveOnHover(bool yn){
	moveOnHover = yn;
};
void Button::OnHover(bool hovered){
	if(!moveOnHover){
		if(hovered){
			foreground->ExpandBy(1.075,sf::seconds(0.1));
		}
		else{
			foreground->ReturnExpand();
		}
	}
	if(moveOnHover){
		if(hovered){
			foreground->MoveTo(hoverMovePosition.x,hoverMovePosition.y,sf::seconds(0.15));
		}
		else{
			foreground->Return();
		}
	}
};
void Button::SetHoverMovePosition(sf::Vector2i hoverMovePosition){
	this-> hoverMovePosition = hoverMovePosition;
};
