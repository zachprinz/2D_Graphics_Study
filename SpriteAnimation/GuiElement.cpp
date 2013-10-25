#include "GuiElement.h"

GuiElement::GuiElement(int x,int y,sf::Texture text) : RClickable(text){
	elementBounds.SetRectangle(x,y,text.getSize().x,text.getSize().y);
	foreground = new Drawn();
	foreground->SetLocation(x,y);
	SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,std::string textureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	SetLocation(x,y);
	foreground = new Drawn();
	foreground->SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,sf::Texture text,sf::Texture fgText) : RClickable(text){
	elementBounds.SetRectangle(x,y,text.getSize().x,text.getSize().y);
	foreground = new Drawn(fgText);
	foreground->SetLocation(x,y);
	SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,std::string text,sf::Texture fgText) : RClickable(text){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	foreground = new Drawn(fgText);
	foreground->SetLocation(x,y);
	SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,sf::Texture text,std::string fgText) : RClickable(text){
	elementBounds.SetRectangle(x,y,text.getSize().x,text.getSize().y);
	foreground = new Drawn(fgText);
	foreground->SetLocation(x,y);
	SetLocation(x,y);
};
GuiElement::GuiElement(int x,int y,std::string textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	SetLocation(x,y);
	foreground = new Drawn(fgTextureName);
	foreground->SetLocation(x,y);
};
void GuiElement::SetForegroundSprite(sf::Texture fgText){
	foreground = new Drawn(fgText);
	foreground->GetSprite()->setTextureRect(sf::IntRect(0,0,fgText.getSize().x,fgText.getSize().y));
	foreground->GetSprite()->setScale((sprite.getLocalBounds().width - 16) / fgText.getSize().x,(sprite.getLocalBounds().height - 16) / fgText.getSize().y);
};
void GuiElement::SetForegroundSprite(sf::Texture fgText,sf::IntRect spriteRect){
	foreground = new Drawn(fgText);
	foreground->GetSprite()->setTextureRect(spriteRect);
	foreground->GetSprite()->setScale((sprite.getLocalBounds().width - 16) / spriteRect.width,(sprite.getLocalBounds().height - 16) / spriteRect.height);
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
