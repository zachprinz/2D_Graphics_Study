#include "HUDPanel.h"
#include "Button.h"
#include "Label.h"
#include "ProgressBar.h"
#include "SlicedSpriteCreator.h"
#include "User.h"
#include <iostream>

HUDPanel* HUDPanel::instance;
HUDPanel* HUDPanel::instanceEnemy;

HUDPanel::HUDPanel(Combatant* target, int x,int y) : GamePanel(x,y,"HUD"){
	this->target = target;
	SetUp();
};
void HUDPanel::SetUp(){
	if(target != NULL){
		sf::Texture tempText;
		tempText.loadFromFile("blank.png");

		Label* valueElement = new Label(100,18,tempText,Label::Fonts::Game,"Endurance");
		dynamicElements.insert(MyPair("enduranceValue",valueElement));
		ProgressBar* progBar = new ProgressBar(100 + valueElement->GetText()->getLocalBounds().width + 15,18, 240, &target->endurancePercent);
		dynamicElements.insert(MyPair("enduranceBar",progBar));

		Label* valueElement2 = new Label(100,50,tempText,Label::Fonts::Game,"Health");
		dynamicElements.insert(MyPair("healthValue",valueElement2));
		ProgressBar* progBar2 = new ProgressBar(100 + valueElement->GetText()->getLocalBounds().width + 15,50, 240, &target->healthPercent);
		dynamicElements.insert(MyPair("healthBar",progBar2));

		tempText.loadFromFile("attacktextures/background.png");
		sf::Texture tempText2;
		tempText2.loadFromFile("attacktextures/default.png");
		Button* tempButton = new Button(8,5,tempText,User::player->GetActorTexture());
		tempButton->SetTarget(this);
		tempButton->SetFunction("none");
		tempButton->CenterForeground();
		dynamicElements.insert(MyPair("Image",tempButton));
		GamePanel::SetUp();
	}
};
void HUDPanel::UpdateUserImage(){
	((Button*)dynamicElements["Image"])->SetForegroundSprite(User::player->GetActorTexture());
};