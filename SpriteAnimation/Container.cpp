#include "Container.h"
#include "StatsPanel.h"
#include <iostream>

Container::Container(int x,int y,std::string textureName) : GuiElement(x,y,textureName){
	isFull = false;
	foreground->GetSprite()->setOrigin(foreground->GetSprite()->getLocalBounds().width / 2, foreground->GetSprite()->getLocalBounds().height);
	///foregroundSprite.setPosition(foregroundSprite.getPosition().x + 16, foregroundSprite.getPosition().y + 16);
};
//Container::Container(int x,int y,std::string textureName, sf::Sprite* fgSprite) : GuiElement(x,y,textureName,fgSprite){
//	isFull = false;
//};
void Container::SetUp(){

};
void Container::AddItem(Item item){
	ClearContents();
	contents = item;
	foreground->GetSprite()->setTexture(Drawn::gameTexture);
	foreground->GetSprite()->setTextureRect(Drawn::GetTextureFromAtlas("itemsprites/" + item.GetId() + ".png"));
	foreground->GetSprite()->setScale(2,2);
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
		foreground->ExpandBy(1.1,sf::seconds(0.1));
	}
	else{
		foreground->ReturnExpand();
	}
};
void Container::Update(sf::RenderTexture& panel){
	if(foreground->GetIsExpanding()){
		foreground->UpdateExpand();
		//CenterForeground();
	}
	panel.draw(sprite);
	if(isFull)
		panel.draw(*foreground->GetSprite());
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