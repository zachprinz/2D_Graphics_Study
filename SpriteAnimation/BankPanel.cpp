#include "BankPanel.h"
#include <iostream>
#include "Button.h"
#include "SlicedSpriteCreator.h"
#include "Label.h"

sf::Texture* BankPanel::bankBackground = new sf::Texture();
BankPanel* BankPanel::instance = new BankPanel();


BankPanel::BankPanel(int x,int y) : ScrollingPanel(x,(y*2),x,y){
	SetUp();
	createPanelLabel = false;
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
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			BankContainer* element = new BankContainer((y*80) + 8,((1+x)*80) + 8,"containerbackground.png");
			dynamicElements.insert(MyPair(std::to_string((x*6) + y), element));
			std::cout << std::to_string((x*6) + y) << std::endl;
		}
	}
	Button* exitButton = new Button(441,8,*Button::circleButtonBackground,*Button::x);
	Label* bankLabel = new Label(140,22,200,SlicedSpriteCreator::GetSlicedTexture(200,30,SlicedSpriteCreator::WoodPanel),Label::Fonts::Game,"Bank");
	bankLabel->CenterText();
	exitButton->SetScale(0.5,0.5);
	exitButton->SetTarget(this);
	exitButton->SetFunction("Close");
	staticElements.insert(MyPair("BankLabel", bankLabel));
	dynamicElements.insert(MyPair("ExitButton",exitButton));
};
void BankPanel::OnButtonEvent(std::string func){
	if(func == "Close")
		GamePanel::Close();
	else
		std::cout <<"they're not the same "  << " " << func << std::endl;
};