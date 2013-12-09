#include "Button.h"
#include "GamePanel.h"
#include <iostream>
#include "GamePanel.h"


std::string Button::circleButtonBackground = "circlebuttonbackground.png";
std::string Button::x = "x.png";

Button::Button(int x,int y,std::string texture,std::string fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = new GamePanel();
	moveOnHover = false;
};
Button::Button(int x,int y,SlicedSprite* texture,std::string fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = new GamePanel();
	moveOnHover = false;
};
void Button::Update(sf::RenderTexture& panel){
	if(foreground->GetIsMoving())
		foreground->UpdateMove();
	if(foreground->GetIsExpanding()){
		foreground->UpdateExpand();
		CenterForeground();
	}
	panel.draw(sprite);
	panel.draw(*foreground->GetSprite());
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
	foreground->Draw(panel);
};
void Button::OnClick(){
	target->OnButtonEvent(function);
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
void Button::CenterForeground(){
	if(isSliced)
		foreground->GetSprite()->setPosition(sprite.getPosition().x + ((elementBounds.GetSize().x - foreground->GetSprite()->getGlobalBounds().width) / 2),sprite.getPosition().y + ((elementBounds.GetSize().y - foreground->GetSprite()->getGlobalBounds().height) / 2));
	else
		foreground->GetSprite()->setPosition(sprite.getPosition().x + ((sprite.getGlobalBounds().width - foreground->GetSprite()->getGlobalBounds().width) / 2),sprite.getPosition().y + ((sprite.getGlobalBounds().height - foreground->GetSprite()->getGlobalBounds().height) / 2));
};
void Button::SetMoveOnHover(bool yn){
	moveOnHover = yn;
};
void Button::OnHover(bool hovered){
	if(!moveOnHover){
		if(hovered){
			foreground->ExpandBy(1.1,sf::seconds(0.1));
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
