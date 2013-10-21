#include "Container.h"
#include "StatsPanel.h"
#include <iostream>

Container::Container(int x,int y,std::string textureName) : GuiElement(x,y,textureName){
	isFull = false;
	foregroundSprite.setOrigin(foregroundSprite.getLocalBounds().width / 2, foregroundSprite.getLocalBounds().height);
	///foregroundSprite.setPosition(foregroundSprite.getPosition().x + 16, foregroundSprite.getPosition().y + 16);
};
Container::Container(int x,int y,std::string textureName, sf::Sprite* fgSprite) : GuiElement(x,y,textureName,fgSprite){
	isFull = false;
};
void Container::SetUp(){

};
void Container::AddItem(Item item){
	ClearContents();
	contents = item;
	foregroundSprite.setTexture(Drawn::gameTexture);
	foregroundSprite.setTextureRect(Drawn::GetTextureFromAtlas("itemsprites/" + item.GetId() + ".png"));
	foregroundSprite.setScale(2,2);
	EnableRClick(item.name);
	isFull = true;
};
Item Container::ClearContents(){
	DisableRClick();
	isFull = false;
	return contents;
};
Item Container::GetContents(){
	return contents;
};
void Container::OnClick(){

}
void Container::OnHover(bool hovered){
	if(isFull && StatsPanel::instance->currentName != contents.name)
		StatsPanel::instance->SetItem(&contents);
	if(hovered){
		foregroundSprite.setScale(foregroundSprite.getScale().x * 1.05, foregroundSprite.getScale().y * 1.05);
		//CenterForeground();
	}
	else{
		foregroundSprite.setScale(foregroundSprite.getScale().x * 0.95238, foregroundSprite.getScale().y * 0.95238);
		//CenterForeground();
	}
};
void Container::Update(sf::RenderTexture& panel){
	panel.draw(sprite);
	if(isFull)
		panel.draw(foregroundSprite);
}
bool Container::GetIsFull(){
	return isFull;
}
bool Container::Contains(Item item){
	if(contents.GetId() == item.GetId())
		return true;
	else
		return false;
};
void Container::OnMenuSelection(std::string){

}