#include "Button.h"
#include "GamePanel.h"
#include <iostream>

sf::Texture* Button::circleButtonBackground = new sf::Texture();
sf::Texture* Button::x = new sf::Texture();

Button::Button(int x,int y,sf::Texture texture,sf::Texture fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = new GamePanel();
	moveOnHover = false;
};
Button::Button(int x,int y,std::string texture,sf::Texture fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = new GamePanel();// Should Really Remove this line... TODO
	moveOnHover = false;
};
Button::Button(int x,int y,std::string texture,std::string fgTexture) : GuiElement(x,y,texture,fgTexture){
	target = new GamePanel();
	moveOnHover = false;
};
Button::Button(int x,int y,sf::Texture texture,std::string fgTexture) : GuiElement(x,y,texture,fgTexture){
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
void Button::OnClick(){
	target->OnButtonEvent(function);
};
void Button::OnStart(){
	circleButtonBackground->loadFromFile("circlebuttonbackground.png");
	x->loadFromFile("x.png");
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
