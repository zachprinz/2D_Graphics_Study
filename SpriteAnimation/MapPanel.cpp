#include "MapPanel.h"
#include "SpritePanel.h"
#include <iostream>
#include "User.h"

MapPanel* MapPanel::instance;

MapPanel::MapPanel(int x,int y) : GamePanel(x,y,"MiniMap"){
	instance = this;
	//createPanelLabel = true;
	GamePanel::SetUp();
	box.setSize(sf::Vector2f(1024,800));
	box.setFillColor(sf::Color(0,0,0,0));
	box.setOutlineColor(sf::Color(255,0,0,255));
	box.setOutlineThickness(7);
	view.reset(sf::FloatRect(0,0,375,300));
	view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
	view.setSize(2048,2048);
	view.setCenter(User::player->GetSprite()->getPosition().x,User::player->GetSprite()->getPosition().y);
	mapRect = GetMapViewRect();
};
MapPanel::MapPanel(){

};
void MapPanel::AddElement(std::string,Drawn*){

};
void MapPanel::UpdateElements(){
	panel.setView(view);
	sf::Vector2f newBoxPosition(User::player->GetSprite()->getPosition().x - 512 + 12,User::player->GetSprite()->getPosition().y - 400 + 12);
	if(!mapRect.contains(newBoxPosition) || !mapRect.contains(sf::Vector2f(newBoxPosition.x + 1024 + 12,newBoxPosition.y + 800 + 12))){
		view.setCenter(sf::Vector2f(view.getCenter().x + (newBoxPosition.x - box.getPosition().x),view.getCenter().y + (newBoxPosition.y - box.getPosition().y)));
		mapRect = GetMapViewRect();
	}
	box.setPosition(newBoxPosition);
	//SpritePanel::instance->ml->Draw(panel);
	panel.draw(box);
	GamePanel::UpdateElements();
};
sf::FloatRect MapPanel::GetMapViewRect(){
	sf::FloatRect mapRect(view.getCenter().x - 1024,view.getCenter().y - 1024,view.getSize().x,view.getSize().y);
	return mapRect;
};
bool MapPanel::CheckUpdate(){
	return true;
};