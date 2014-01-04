#include "BankPanel.h"
#include <iostream>
#include "Button.h"
#include "Label.h"

sf::Texture* BankPanel::bankBackground = new sf::Texture();
BankPanel* BankPanel::instance = new BankPanel();


BankPanel::BankPanel(int x,int y) : ScrollingPanel(x,((float)(y-80)*2),x,y,"Bank"){
	SetUp();
	instance = this;
	isPanelOpen = false;
};
BankPanel::BankPanel(){

};
void BankPanel::AddElement(std::string,Drawn*){

};
BankContainer* BankPanel::GetOpenContainer(){
	for(int x = 0; x < 36; x++){
		if(!((BankContainer*)(dynamicElements[std::to_string(x)]))->GetIsFull())
			return (BankContainer*)(dynamicElements[std::to_string(x)]);
	}
};
void BankPanel::Add(Item item){
	GetOpenContainer()->AddItem(item);
};
void BankPanel::Remove(Item item){

};
void BankPanel::Remove(std::vector<Item> items){

};
bool BankPanel::DoesContain(Item item){
	for(MyPair x: dynamicElements){
		if(((BankContainer*)x.second)->GetIsFull() && !((BankContainer*)x.second)->Contains(item))
			return true;
	}
	return false;
};
bool BankPanel::DoesContain(std::vector<Item> items){
	for(int x = 0; x < items.size(); x++){
		if(!DoesContain(items[x]))
			return false;
	}
	return true;
};
BankContainer* BankPanel::FindContainerOf(Item item){
	for(int x = 0; x < 36; x++){
		if(((BankContainer*)(dynamicElements[std::to_string(x)]))->GetIsFull() && !((BankContainer*)(dynamicElements[std::to_string(x)]))->Contains(item))
			return ((BankContainer*)(dynamicElements[std::to_string(x)]));
	}
};
void BankPanel::SetUp(){
	std::cout << "Setting up bank slots...";
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			BankContainer* element = new BankContainer((y*80) + 8,x*80,"containerbackground.png");
			dynamicElements.insert(MyPair(std::to_string((x*6) + y), element));
		}
	}
	std::cout << " Done" << std::endl;
	Button* exitButton = new Button(467,15,Button::circleButtonBackground,Button::x);
	Label* bankLabel = new Label(164,33,200,new SlicedSprite(164,33,200,30,SlicedSprite::WoodPanel),Label::Fonts::Game,"Bank");
	bankLabel->CenterText();
	exitButton->SetScale(0.5,0.5);
	exitButton->SetTarget(this);
	exitButton->SetFunction("Close");
	backgroundElements.insert(MyPair("bankLabel", bankLabel));
	backgroundElements.insert(MyPair("exitButton",exitButton));
};
void BankPanel::OnButtonEvent(std::string func){
	if(func == "Close")
		GamePanel::Close();
	else
		ScrollingPanel::OnButtonEvent(func);
};