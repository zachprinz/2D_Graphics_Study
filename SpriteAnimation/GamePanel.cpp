#include "GamePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"
#include "Label.h"
#include "SlicedSpriteCreator.h"
#include "SlicedSprite.h"
#include "SpritePanel.h"

GamePanel* GamePanel::currentMousePanel;
Drawn* GamePanel::currentMouseElement;

GamePanel::GamePanel(int x, int y, std::string name){
	mySize = sf::Vector2f(x,y);
	currentMouseElement = new Drawn();
	doUpdate = true;
	createPanelLabel = true;
	if(name == "Bank" || name == "Game" || name == "ActionBar" || "HUD")
		createPanelLabel = false;
	isPanelOpen = true;
	drawCollision = false;
	if(createPanelLabel)
		backgroundPanel.create(x + 16, y + 46);
	else
		backgroundPanel.create(x + 16, y + 16);
	panel.create(x,y);
	panelName = name;
	panel.setSmooth(true);
	panelSprite.setTexture(panel.getTexture());
	backgroundPanelSprite.setTexture(backgroundPanel.getTexture());
};
GamePanel::GamePanel(){

}
void GamePanel::Update(){
	if(isPanelOpen){
	//	if(this->CheckUpdate() || doUpdate == true){
			UpdateElements();
	//	}
	//	else{

	//	}
	}
};
void GamePanel::InitiateElements(){

};
void GamePanel::UpdateElements(){
	for(MyPair x: backgroundElements){
		//((SlicedSprite*)x.second)->Update(this);
	}
	for(MyPair x: staticElements){
		x.second->Update(this);
	}
	if(drawCollision)
		SpritePanel::room->DrawTiles(panel);
	for(MyPair x: dynamicElements){
		x.second->Update(this);
	}
	if(RClickMenu::currentPanel == this){
		RClickMenu::Update(panel);
	}
};
void GamePanel::Open(){
	isPanelOpen = true;
};
void GamePanel::Close(){
	isPanelOpen = false;
};
void GamePanel::SetPosition(int x, int y){
	panelSprite.setPosition(x + 8,y + 8);
	//if(createPanelLabel)
	//	backgroundPanelSprite.setPosition(x,y - 30);
	//else
		backgroundPanelSprite.setPosition(x,y);
	panelBounds = AABB(Vec2f(x,y),Vec2f(x + GetSize().x,y + GetSize().y));
}
void GamePanel::OnClick(sf::Vector2i point){
	std::cout << "Target Point: " << point.x << "," << point.y << std::endl;
	for(MyPair x: dynamicElements){
		if(x.second->GetSprite()->getGlobalBounds().contains(point.x - panelSprite.getPosition().x,point.y - panelSprite.getPosition().y)){
			x.second->OnClick();
		}
		else{
			sf::FloatRect rect = x.second->GetSprite()->getGlobalBounds();
		}
	}
}
void GamePanel::OnRClick(sf::Vector2i point){
	std::cout << "Right Click" << std::endl;
	for(MyPair x: dynamicElements){
		if(((RClickable*)(x.second))->GetRClickEnabled() && x.second->GetSprite()->getGlobalBounds().contains(point.x - panelSprite.getPosition().x,point.y - panelSprite.getPosition().y)){
			((RClickable*)(x.second))->OnRClick(sf::Vector2i(point.x - panelSprite.getPosition().x , point.y - panelSprite.getPosition().y),this);
		}
		else if(((RClickable*)(x.second))->GetRClickEnabled()){
			std::cout << "RClickEnabled on this one." << std::endl;
		}
	}
}
void GamePanel::OnHover(sf::Vector2i point){
	for(MyPair x: dynamicElements){
		if(x.second->GetSprite()->getGlobalBounds().contains(point.x - panelSprite.getPosition().x,point.y - panelSprite.getPosition().y)){
			if(GamePanel::currentMouseElement != x.second){
				if(currentMouseElement != NULL)
					currentMouseElement->OnHover(false);
				currentMouseElement = x.second;
				(x.second)->OnHover(true);
			}
		}
	}
};
AABB GamePanel::GetBounds(){
	return panelBounds;
}
void GamePanel::RemoveDynamicElement(std::string key){
		dynamicElements.erase(key);
};
GamePanel::ElementList* GamePanel::GetDynamicElements(){
	return &dynamicElements;
}
sf::RenderTexture& GamePanel::GetRenderPanel(){
	return panel;
};
sf::Vector2f GamePanel::GetPosition(){
	return panelSprite.getPosition();
}
void GamePanel::SetUp(){
	//SlicedSprite* background = new SlicedSprite(-8,-8,panel.getSize().x + 16,panel.getSize().y + 16,SlicedSprite::Pixel);
	//if(createPanelLabel)
	//	background->SetPosition(sf::Vector2f(0,30));
	//backgroundElements.insert(MyPair("Background", background));
	//if(createPanelLabel){
	//	Label* label = new Label((panel.getSize().x - 200) / 2,0,200,new SlicedSprite((panel.getSize().x - 200) / 2,0,200,30,SlicedSprite::WoodPanel),Label::Fonts::Game,panelName);
	//	label->CenterText();
	//	backgroundElements.insert(MyPair("Label", label));
	//}
}
bool GamePanel::GetIsPanelOpen(){
	return isPanelOpen;
}
void GamePanel::OnButtonEvent(std::string){

}
bool GamePanel::CheckUpdate(){
	return true;
};
std::string GamePanel::GetName(){
	return panelName;
};
sf::Vector2f GamePanel::GetSize(){
	return mySize;
	//return sf::Vector2i(panelBounds.GetHalfDims().x * 2,panelBounds.GetHalfDims().y * 2);
};