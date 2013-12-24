#include "GamePanel.h"
#include <iostream>
#include "User.h"
#include "RClickMenu.h"
#include "Label.h"
#include "SlicedSprite.h"
#include "SpritePanel.h"
#include "Game.h"

GamePanel* GamePanel::currentMousePanel;
Drawn* GamePanel::currentMouseElement;
Drawn* GamePanel::currentPressedElement;

GamePanel::GamePanel(int x, int y, std::string name){
	mySize = sf::Vector2f(x,y);
	isPanelOpen = true;
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
		UpdateElements();
	}
};
void GamePanel::InitiateElements(){

};
void GamePanel::UpdateElements(){
	//for(MyPair x: backgroundElements){
		//((SlicedSprite*)x.second)->Update(this);
	//}
	for(MyPair x: staticElements){
		x.second->Update(this);
	}
	for(MyPair x: dynamicElements){
		x.second->Update(this);
	}
	if(RClickMenu::currentPanel == this){
		RClickMenu::Update(this);
	}
};
void GamePanel::Open(){
	isPanelOpen = true;
};
void GamePanel::Close(){
	isPanelOpen = false;
};
sf::Vector2f GamePanel::GetViewLowerBound(){
	return sf::Vector2f(panel.getView().getCenter() - sf::Vector2f(panel.getView().getSize().x / 2, panel.getView().getSize().y / 2.0));
}
void GamePanel::SetPosition(int x, int y){
	panelSprite.setPosition(x + 8,y + 8);
	backgroundPanelSprite.setPosition(x,y);
	panelBounds = AABB(Vec2f(x,y),Vec2f(x + GetSize().x,y + GetSize().y));
}
void GamePanel::OnMousePress(sf::Vector2i point){
	for(MyPair x: dynamicElements){
		if(x.second->GetBounds(panel.getView()).Contains(point.x - GetPosition().x,point.y - GetPosition().y)){
			x.second->OnMousePress();
			currentPressedElement = x.second;
			Game::mouseIsPressed = true;
		}
	}
}
void GamePanel::OnRClick(sf::Vector2i point){
	std::cout << "Right Click" << std::endl;
	for(MyPair x: dynamicElements){
		if(((RClickable*)(x.second))->GetRClickEnabled() && x.second->GetBounds().Contains(point.x - GetPosition().x,point.y - GetPosition().y)){
			((RClickable*)(x.second))->OnRClick(sf::Vector2i(point.x - GetPosition().x,point.y - GetPosition().y),this);
		}
		else if(((RClickable*)(x.second))->GetRClickEnabled()){
			std::cout << "RClickEnabled on this one." << std::endl;
		}
	}
}
void GamePanel::OnHover(sf::Vector2i point){
	for(MyPair x: dynamicElements){
		if(x.second->GetBounds(panel.getView()).Contains(point.x - GetPosition().x,point.y - GetPosition().y)){
			if(GamePanel::currentMouseElement != x.second){
				if(currentMouseElement != NULL)
					currentMouseElement->OnHover(false);
				currentMouseElement = x.second;
				(x.second)->OnHover(true);
			}
			break;
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
	SlicedSprite* background = new SlicedSprite(-8,-8,panel.getSize().x + 16,panel.getSize().y + 16,SlicedSprite::Pixel);
	backgroundElements.insert(MyPair("Background", background));
}
bool GamePanel::GetIsPanelOpen(){
	return isPanelOpen;
}
void GamePanel::OnButtonEvent(std::string){

}
std::string GamePanel::GetName(){
	return panelName;
};
sf::Vector2f GamePanel::GetSize(){
	return mySize;
};