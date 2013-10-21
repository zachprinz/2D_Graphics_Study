#include "RoomTile.h"
#include <iostream>

RoomTile::RoomTile(int x,int y){
	position.x = x;
	position.y = y;
	visual.setPosition(x + 1,y + 1);
	ocupied = false;
	visual.setSize(sf::Vector2f(30,30));
}
sf::RectangleShape RoomTile::getVisual(){
	visual.setFillColor(sf::Color(255,255,255,40));
	if(ocupied)
		visual.setFillColor(sf::Color(225,1,1,128));
	return visual;
}
bool RoomTile::GetOcupied(){
	return ocupied;
};
void RoomTile::AddOcupant(int tag){
	TryRemoveOcupant(tag);
	ocupants.push_back(tag);
	ocupied = true;
};
void RoomTile::SetBlocked(){
	ocupied = true;
}
void RoomTile::TryRemoveOcupant(int tag){
	if(ocupants.size() == 0)
		ocupied = false;
	else{
		for(int x = 0; x < ocupants.size(); x++){
			if(ocupants[x] == tag)
				ocupants.erase(ocupants.begin() + x);
		}
	}
	if(ocupants.size() == 0){
		ocupied = false;
	}
};
void RoomTile::TileAttacked(){
	
};
