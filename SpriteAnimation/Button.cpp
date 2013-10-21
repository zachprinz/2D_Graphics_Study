#include "Button.h"
#include "GamePanel.h"

sf::Texture* Button::circleButtonBackground = new sf::Texture();
sf::Texture* Button::x = new sf::Texture();

Button::Button(int x,int y,sf::Texture texture,sf::Texture fgTexture) : GuiElement(x,y,texture){
	target = new GamePanel();
	foregroundSpriteTexture = fgTexture;
	foregroundSprite.setTexture(foregroundSpriteTexture);
	foregroundSprite.setPosition(x,y);
};
Button::Button(int x,int y,std::string texture,sf::Texture fgTexture) : GuiElement(x,y,texture){
	target = new GamePanel();
	foregroundSpriteTexture = fgTexture;
	foregroundSprite.setTexture(foregroundSpriteTexture);
	foregroundSprite.setPosition(x,y);
};
Button::Button(int x,int y,std::string texture,std::string fgTexture) : GuiElement(x,y,texture){
	target = new GamePanel();
	foregroundSprite.setTexture(Drawn::gameTexture);
	foregroundSprite.setTextureRect(Drawn::GetTextureFromAtlas(fgTexture));
	foregroundSprite.setPosition(x,y);
};
void Button::Update(sf::RenderTexture& panel){
	panel.draw(sprite);
	panel.draw(foregroundSprite);
};
void Button::OnClick(){
	target->OnButtonEvent(function);
};
void Button::OnStart(){
	circleButtonBackground->loadFromFile("circlebuttonbackground.png");
	x->loadFromFile("x.png");
};
void Button::SetScale(float x,float y){
	foregroundSprite.setScale(x,y);
	sprite.setScale(x,y);
};
void Button::SetFunction(std::string str){
	function = str;
};
void Button::SetTarget(GamePanel* myTarget){
	target = myTarget;
};
void Button::CenterForeground(){
	foregroundSprite.setPosition(sprite.getPosition().x + ((sprite.getGlobalBounds().width - foregroundSprite.getGlobalBounds().width) / 2),sprite.getPosition().y + ((sprite.getGlobalBounds().height - foregroundSprite.getGlobalBounds().height) / 2));
};
void Button::OnHover(bool hovered){
	if(hovered){
	foregroundSprite.setScale(1.05,1.05);
	CenterForeground();
	}
	else{
		foregroundSprite.setScale(1,1);
		CenterForeground();
	}
};
