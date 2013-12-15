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
bool RoomTile::ContainsOcupant(int oc){
	for(int x = 0; x < ocupants.size(); x++){
		if(ocupants[x] == oc)
			return true;
	};
	return false;
};
std::vector<int> RoomTile::GetOcupantsBut(int tag){
	std::vector<int> returnOcupants;
	for(int x = 0; x < ocupants.size(); x++){
		if(ocupants[x] != tag)
			returnOcupants.push_back(ocupants[x]);
	}
	return returnOcupants;
};
std::vector<int> RoomTile::GetOcupantsBut(std::vector<int> tags){
	std::vector<int> returnOcupants;
	for(int x = 0; x < ocupants.size(); x++){
		bool temp = false;
		for(int y = 0; y < tags.size(); y++){
			if(ocupants[x] == tags[y]){
				temp = true;
			}
		}
		if(!temp)
			returnOcupants.push_back(ocupants[x]);
	}
	return returnOcupants;
};