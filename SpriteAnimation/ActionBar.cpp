#include "ActionBar.h"
#include "User.h"
#include "Button.h"
#include <iostream>

ActionBar* ActionBar::instance;

ActionBar::ActionBar(int x ,int y) : GamePanel(x,y,"ActionBar"){
	instance = this;
	SetUp();
};
ActionBar::ActionBar(){

};
void ActionBar::AddElement(std::string,Drawn*){

};
void ActionBar::UpdateElements(){
	GamePanel::UpdateElements();
	for(int x = 0; x < User::player->currentAttacks.size(); x++){
		sheets[x]->setScale(1,1 - User::player->attacks[User::player->currentAttacks[x]]->percentCooledDown);
		panel.draw(*sheets[x]);
		Drawn::DrawOther(sheets[x],this);
	}
};
void ActionBar::UpdateActionImages(){
	Combatant::AttackMap::iterator it = User::player->attacks.begin();
	for(int x = 0; x < User::player->attacks.size(); x++){//Combatant::AttackPair x: User::player->attacks){
		Button* tempButton = ((Button*)dynamicElements["Button" + std::to_string(x)]);
		tempButton->SetForegroundSprite("attacktextures/" + it->second->name + ".png");
		((Button*)dynamicElements["Button" + std::to_string(x)])->CenterForeground();
		it++;
	}
};
void ActionBar::SetUp(){
	for(Combatant::AttackPair x: User::player->attacks){
		Button* tempButton = new Button((dynamicElements.size() * 110) + 30,4,"attacktextures/background.png","attacktextures/" + x.second->name + ".png");
		tempButton->SetTarget(this);
		tempButton->SetFunction(std::to_string(dynamicElements.size()));
		tempButton->CenterForeground();
		std::cout << "Button" << std::to_string(dynamicElements.size()) << std::endl;
		AddDynamicElement(MyPair("Button" + std::to_string(dynamicElements.size()),tempButton));
	}
	for(int x = dynamicElements.size(); x < 9; x++){
		Button* tempButton = new Button((x * 110) + 30,4,"attacktextures/background.png","attacktextures/default.png");
		tempButton->SetTarget(this);
		tempButton->SetFunction(std::to_string(x));
		tempButton->CenterForeground();
		AddDynamicElement(MyPair("Button" + std::to_string(dynamicElements.size()),tempButton));
	}
	for(MyPair x: dynamicElements){
		sheets.push_back(new sf::RectangleShape(sf::Vector2f(64,64)));
		sheets[sheets.size() - 1]->setPosition(((Button*)(x.second))->foreground->GetSprite()->getPosition() - ((Button*)(x.second))->foreground->GetSprite()->getOrigin());
		sheets[sheets.size() - 1]->setFillColor(sf::Color(0,0,0,150));
	}
	GamePanel::SetUp();
};
void ActionBar::OnButtonEvent(std::string btnFunction){
	std::cout << "Action Bar Button Clicked" << std::endl;
	int bot = std::stoi(btnFunction);
	User::player->TryLaunchAttack(User::player->currentAttacks[bot]);
};