#include "HUDPanel.h"
#include "Button.h"
#include "Label.h"
#include "ProgressBar.h"
#include "User.h"
#include "StatsPanel.h"
#include <iostream>

HUDPanel* HUDPanel::instance;
HUDPanel* HUDPanel::instanceEnemy;

HUDPanel::HUDPanel(Combatant* target, int x,int y) : GamePanel(x,y,"HUD"){
	instance = this;
	this->target = target;
	SetUp();
};
void HUDPanel::SetUp(){
	if(target != NULL){
		Label* valueElement = new Label(100,18,"blank.png",Label::Fonts::Game,"Endurance");
		AddDynamicElement(MyPair("enduranceValue",valueElement));
		ProgressBar* progBar = new ProgressBar(100 + valueElement->GetText()->getLocalBounds().width + 15,18, 240, &target->endurancePercent);
		AddDynamicElement(MyPair("enduranceBar",progBar));

		Label* valueElement2 = new Label(100,50,"blank.png",Label::Fonts::Game,"Health");
		AddDynamicElement(MyPair("healthValue",valueElement2));
		ProgressBar* progBar2 = new ProgressBar(100 + valueElement->GetText()->getLocalBounds().width + 15,50, 240, &target->healthPercent);
		AddDynamicElement(MyPair("healthBar",progBar2));

		Button* tempButton = new Button(8,8,"attacktextures/background.png","attacktextures/default.png"); //TODO
		tempButton->SetTarget(this);
		tempButton->SetFunction("user");
		tempButton->CenterForeground();
		AddDynamicElement(MyPair("Image",tempButton));
		GamePanel::SetUp();
	}
};
void HUDPanel::UpdateUserImage(){
	//((Button*)dynamicElements["Image"])->SetForegroundSprite(User::player->GetActorTexture()); //TODO
};
void HUDPanel::OnButtonEvent(std::string message){
	if(message == "user"){
		StatsPanel::instance->SetCombatant(User::player);
	}
};