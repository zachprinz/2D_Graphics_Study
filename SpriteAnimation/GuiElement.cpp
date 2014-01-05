#include "GuiElement.h"
#include "GamePanel.h"
#include "DropDownMenu.h"

GuiElement::GuiElement(int x,int y,std::string textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	isSliced = false;
	foreground = new Drawn(fgTextureName);
    	SetPosition(sf::Vector2f(x,y));
	pressed = false;
};
GuiElement::GuiElement(int x,int y,SlicedSprite* textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,textureName->GetSize().x,textureName->GetSize().y);
	isSliced = true;
	base = textureName;
	foreground = new Drawn(fgTextureName);
	SetPosition(sf::Vector2f(x,y));
	pressed = false;
};
void GuiElement::SetForegroundSprite(std::string spriteRect){
	foreground = new Drawn(spriteRect);
};
void GuiElement::Update(GamePanel* panel){

};
void GuiElement::OnClick(){

};
void GuiElement::OnRClick(sf::Vector2i,GamePanel* panel){
    new DropDownMenu(sf::Mouse::getPosition().x - panel->GetPosition().x,sf::Mouse::getPosition().y - panel->GetPosition().y,rightClickOptions);
    DropDownMenu::instance->SetTarget(this);
};
void GuiElement::OnHover(bool hovered){

};
void GuiElement::SetPosition(sf::Vector2f pos){
	sf::Vector2f difference = pos - GetPosition();
	if(!isSliced)
		Drawn::SetPosition(pos);
	foreground->SetPosition(foreground->GetPosition() + difference);
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
void GuiElement::OnButtonEvent(std::string){

};