#include "Container.h"
#include "StatsPanel.h"
#include <iostream>

Container::Container(int x,int y,std::string textureName) : GuiElement(x,y,textureName,"blank.png"){
	rightClickOptions.push_back("name");
	isFull = false;	
};
void Container::SetUp(){

};
void Container::AddItem(Item item){
	rightClickOptions[0] = item.GetName();
	std::cout << "Container adding a found item." << std::endl;
	ClearContents();
	contents = item;
	SetForegroundSprite("itemsprites/" + item.imageName);
	foreground->SetScale(sf::Vector2f(2,2));
	CenterForeground();
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
		//foreground->ExpandBy(1.1,sf::seconds(0.1));
	}
	else{
		//foreground->ReturnExpand();
	}
};
void Container::Update(GamePanel* panel){
	if(foreground->GetIsExpanding()){
		foreground->UpdateExpand();
	}
	Draw(panel);
	if(isFull)
		foreground->Draw(panel);
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
void Container::OnButtonEvent(std::string){

}