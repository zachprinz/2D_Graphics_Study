#include "RClickMenu.h"
#include <iostream>
#include "GamePanel.h"

std::vector<Label*> RClickMenu::OptionButtons;
sf::Texture RClickMenu::menuTexture;
std::vector<Label*> RClickMenu::labels;
bool RClickMenu::isOpen = false;
GamePanel* RClickMenu::currentPanel;
RClickable* RClickMenu::currentTarget;
float RClickMenu::width; 

void RClickMenu::AddOption(int x, int y, int op){
	OptionButtons[op]->SetLocation(x,(labels.size() * 30) + y);
	labels.push_back(OptionButtons[op]);
	labels[labels.size() - 1]->SetTextOffset(5,2);
};
void RClickMenu::Reset(int x,int y,std::string name,RClickable* target, GamePanel* panel){
	Clear();
	SetOrgin(TopLeft);
	isOpen = true;
	currentPanel = panel;
	currentTarget = target;
	GetTextWidth(name);
	labels.push_back(new Label(x,y,width,"menubackground.png",Label::Fonts::Game, name));
	labels[0]->SetTextOffset((width - GetTextWidth(name)) / 2,2);
	labels[0]->SetTextColor(sf::Color(255,0,0,255));
};
std::vector<Label*> RClickMenu::GetMenu(){
	return labels;
};
void RClickMenu::OnStart(){
	std::string optionNames[] = {"Drop","Equip","Unequip","Deposit","Withdraw","Barter","Craft"};
	GetTextWidth("Withdraw ");
	for(int x = 0; x < 7; x++){
		OptionButtons.push_back(new Label(0,0,width,"menubackground.png",Label::Fonts::Game,optionNames[x]));
	}
};
void RClickMenu::Clear(){
	labels.clear();
};
bool RClickMenu::GetIsOpen(){
	return isOpen;
};
void RClickMenu::Update(sf::RenderTexture& panel){
	if(isOpen){
		std::vector<Label*> temp = RClickMenu::GetMenu();
		for(int x = 0; x < temp.size(); x++){
			temp[x]->Update(panel);
		}
	}
}
float RClickMenu::GetTextWidth(std::string string){
	sf::Text text;
	text.setFont(Label::fonts[Label::Fonts::Game]);
	text.setCharacterSize(22);
	text.setString(string);
	if(text.getLocalBounds().width > width)
		width = text.getLocalBounds().width;
	return text.getLocalBounds().width;
};
bool RClickMenu::Contains(sf::Vector2f point){
	for(int x = 0; x < labels.size(); x++){
		sf::FloatRect rect = labels[x]->GetSprite()->getGlobalBounds();
		std::cout << "Left: " << rect.left << " Right: " << (rect.left + rect.width) << " Top: " << rect.top << " Bottom: " << rect.top + rect.height << std::endl;
		if(rect.contains(point)){
			if(x != 0){
				std::cout << "Found RClick Menu Selection" << std::endl;
				currentTarget->OnMenuSelection(labels[x]->GetText()->getString());
				Close();
			}
			return true;
		}
	}
	return false;
}
void RClickMenu::Close(){
	isOpen = false;
	Clear();
}
void RClickMenu::SetOrgin(Orgins orgin){
	for(int x = 0; x < labels.size(); x++){
		Label* tempLabel = labels[x];
		sf::Sprite* tempSprite = tempLabel->GetSprite();
		sf::Text* tempText = tempLabel->GetText();
		switch(orgin){
			case(TopLeft):
				tempSprite->setOrigin(0,0);
				tempLabel->CenterText();
				break;
			case(TopRight):
				tempSprite->setOrigin(tempSprite->getLocalBounds().width,0);
				tempLabel->CenterText();
				break;
			case(BottomLeft):
				tempSprite->setOrigin(0,tempSprite->getLocalBounds().height);
				tempLabel->CenterText();
				break;
			case(BottomRight):
				tempSprite->setOrigin(tempSprite->getLocalBounds().width,tempSprite->getLocalBounds().height);
				tempLabel->CenterText();
				break;
		}
	}
};
