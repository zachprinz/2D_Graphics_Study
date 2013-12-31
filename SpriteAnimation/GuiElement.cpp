#include "GuiElement.h"
#include "GamePanel.h"

GuiElement::GuiElement(int x,int y,std::string textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	isSliced = false;
	SetPosition(sf::Vector2f(x,y));
	foreground = new Drawn(fgTextureName);
	foreground->SetPosition(sf::Vector2f(x,y));
	pressed = false;
};
GuiElement::GuiElement(int x,int y,SlicedSprite* textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,textureName->GetSize().x,textureName->GetSize().y);
	isSliced = true;
	base = textureName;
	SetPosition(sf::Vector2f(x,y));
	foreground = new Drawn(fgTextureName);
	foreground->SetPosition(sf::Vector2f(x,y));
	pressed = false;
};
void GuiElement::SetForegroundSprite(std::string spriteRect){
	foreground = new Drawn(spriteRect);
};
void GuiElement::Update(GamePanel* panel){

};
void GuiElement::OnClick(){

};
void GuiElement::OnHover(bool hovered){

};
void GuiElement::SetPosition(sf::Vector2f pos){
	if(!isSliced)
		Drawn::SetPosition(pos);
};
void GuiElement::CenterForeground(){
	foreground->GetSprite()->setOrigin(sf::Vector2f((foreground->GetSize().x / 2.0f),(foreground->GetSize().y / 2.0f)));
	foreground->SetPosition(GetPosition() + sf::Vector2f(GetSize().x / 2.0f, GetSize().y / 2.0f));
};
void GuiElement::SetOrgin(int x,int y){
	sprite.setOrigin(x,y);
};
void GuiElement::OnMousePress(){
    std::cout << "GuiElement Pressed" << std::endl;
    pressed = true;
};
void GuiElement::OnMouseRelease(){
    pressed = false;
    this->OnClick();
};