#include "GuiElement.h"
#include "GamePanel.h"

GuiElement::GuiElement(int x,int y,std::string textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,texturePart.width,texturePart.height);
	isSliced = false;
	SetPosition(sf::Vector2f(x,y));
	foreground = new Drawn(fgTextureName);
	foreground->SetPosition(sf::Vector2f(x,y));
};
GuiElement::GuiElement(int x,int y,SlicedSprite* textureName,std::string fgTextureName) : RClickable(textureName){
	elementBounds.SetRectangle(x,y,textureName->GetSize().x,textureName->GetSize().y);
	isSliced = true;
	base = textureName;
	SetPosition(sf::Vector2f(x,y));
	foreground = new Drawn(fgTextureName);
	foreground->SetPosition(sf::Vector2f(x,y));
};
void GuiElement::SetForegroundSprite(std::string spriteRect){
	foreground = new Drawn(spriteRect);
};
void GuiElement::Update(sf::RenderTexture&){

};
void GuiElement::Update(GamePanel* panel){

};
void GuiElement::OnClick(){

};
void GuiElement::OnHover(bool hovered){

};
ARectangle* GuiElement::GetBounds(){
	return &elementBounds;
}
void GuiElement::SetPosition(sf::Vector2f pos){
	if(!isSliced)
		//base->SetPosition(pos);
	//else
		Drawn::SetPosition(pos);
};
void GuiElement::CenterForeground(){
	//if(isSliced)
	//	foreground->GetSprite()->setPosition(sprite.getPosition().x + ((elementBounds.GetSize().x - foreground->GetSprite()->getGlobalBounds().width) / 2),sprite.getPosition().y + ((elementBounds.GetSize().y - foreground->GetSprite()->getGlobalBounds().height) / 2));
	//else{
		foreground->GetSprite()->setOrigin(sf::Vector2f(-1*(foreground->GetSize().x / 2.0f),-1*(foreground->GetSize().y / 2.0f)));
		foreground->SetPosition(GetPosition() + sf::Vector2f(GetSize().x / 2.0f, GetSize().y / 2.0f));
	//}
};
