#include "GuiElement.h"

GuiElement::GuiElement(int x,int y,sf::Texture text,sf::Sprite* fgSprite) : RClickable(text){
	elementBounds.SetRectangle(x,y,text.getSize().x,text.getSize().y);
	SetLocation(x,y);
	foregroundSprite.setPosition(x,y);
};
GuiElement::GuiElement(int x,int y,std::string textureName,sf::Sprite* fgSprite) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	SetLocation(x,y);
	foregroundSprite.setPosition(x,y);
};
GuiElement::GuiElement(int x,int y,sf::Texture text) : RClickable(text){
	elementBounds.SetRectangle(x,y,text.getSize().x,text.getSize().y);
	foregroundSprite.setPosition(x,y);
	SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,std::string textureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	SetLocation(x,y);
	foregroundSprite.setPosition(x,y);
};
void GuiElement::SetForegroundSprite(sf::Texture fgText){
	foregroundSpriteTexture = fgText;
	foregroundSprite.setTexture(foregroundSpriteTexture);
	foregroundSprite.setTextureRect(sf::IntRect(0,0,fgText.getSize().x,fgText.getSize().y));
	foregroundSprite.setScale((sprite.getLocalBounds().width - 16) / foregroundSpriteTexture.getSize().x,(sprite.getLocalBounds().height - 16) / foregroundSpriteTexture.getSize().y);
};
void GuiElement::SetForegroundSprite(sf::Texture fgText,sf::IntRect spriteRect){
	foregroundSpriteTexture = fgText;
	foregroundSprite.setTexture(foregroundSpriteTexture);
	foregroundSprite.setTextureRect(spriteRect);
	foregroundSprite.setScale((sprite.getLocalBounds().width - 16) / spriteRect.width,(sprite.getLocalBounds().height - 16) / spriteRect.height);
};
void GuiElement::SetBackgroundSprite(sf::Texture bgSprite){
	texture = bgSprite;
	sprite.setTexture(texture);
};
void GuiElement::Update(sf::RenderTexture&){

};
void GuiElement::OnClick(){

};
void GuiElement::OnHover(bool hovered){

};
Rectangle* GuiElement::GetBounds(){
	return &elementBounds;
}
void GuiElement::SetLocation(float x,float y){
	Drawn::SetLocation(x,y);
};