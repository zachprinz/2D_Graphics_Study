#include "Room.h"
#include "GameSprite.h"
#include <iostream>

Room::Room(){
	for(int x = 0; x < 128; x++){ // How many tiles tall is the map? Yes I know it says X.
		std::vector<RoomTile> tempRow;
		for(int y = 0; y < 128; y++){ // How many tiles wide, just incase you couldn't guess.
			tempRow.push_back(RoomTile(y * 32, x * 32));
		}
		roomTiles.push_back(tempRow);
	}
	for(int x = 0; x < 128; x++){
		for(int y = 0; y < 128; y++){
			grid.push_back(&roomTiles[x][y]);
		}
	}
};
void Room::DrawTiles(sf::RenderTexture &windowA){ // Super lag.
	for(int x = 0; x < 128; x++){
		for(int y = 0; y < 128; y++){
			windowA.draw(roomTiles[x][y].getVisual());
		}
	}
};
void Room::DrawOcupants(sf::RenderTexture &windowA){ // Super lag.
	for(int x = 0; x < 128; x++){
		for(int y = 0; y < 128; y++){
			//windowA.draw(roomTiles[x][y].getOcupantVisual());
		}
	}
};
void Room::AddOcupant(GameSprite* gameSpriteRef){
	ocupantMap.insert(MyPair(gameSpriteRef->GetTag(), gameSpriteRef));
};
GameSprite* Room::GetOcupant(int tag){
	if(ocupantMap.find(tag) != ocupantMap.end())
		return ocupantMap[tag];
};
RoomTile* Room::GetRoomTile(int x,int y){
	return &(roomTiles[y][x]);
};
void Room::RemoveOcupant(int key){
			ocupantMap.erase(key);
};
std::vector<RoomTile*> Room::GetPathTo(sf::Vector2i currentPos, sf::Vector2i targetPos){ // switching x and y and what not.
	std::vector<RoomTile*> path;
	int currentGCost = 0;
	int targetAddress = GetGridAddress(targetPos);
	int currentAddress = GetGridAddress(currentPos);
	while(true){
		openList.clear();
		std::vector<int> tempVec = GetSurroundingTiles(currentAddress);
		for(int b = 0; b < tempVec.size(); b++){
			if(!grid[tempVec[b]]->GetOcupied()){
				grid[tempVec[b]]->hValue = GetHValue(tempVec[b],targetAddress);
				grid[tempVec[b]]->fValue = grid[tempVec[b]]->hValue;
				grid[tempVec[b]]->gValue = 1;
				grid[tempVec[b]]->parent = currentAddress;
				openList.push_back(tempVec[b]);
			}
		}
		currentAddress = openList[0];
		closedList.push_back(currentAddress);
		path.push_back(grid[currentAddress]);
		if(grid[currentAddress]->hValue == 1)
			break;
	}
	return path;
};
sf::Vector2i Room::GetNextTileTo(sf::Vector2i currentPos,sf::Vector2i targetPos){
	int targetAddress = GetGridAddress(targetPos);
	int currentAddress = GetGridAddress(currentPos);
	int lowestH = -1;
	openList.clear();
	std::vector<int> tempVec = GetSurroundingTiles(currentAddress);
	for(int b = 0; b < tempVec.size(); b++){
		if(!grid[tempVec[b]]->GetOcupied()){
			grid[tempVec[b]]->hValue = GetHValue(tempVec[b],targetAddress);
			grid[tempVec[b]]->fValue = grid[tempVec[b]]->hValue;
			grid[tempVec[b]]->gValue = 1;
			grid[tempVec[b]]->parent = currentAddress;
			if(lowestH == -1)
				lowestH = tempVec[b];
			else if(grid[tempVec[b]]->hValue < grid[lowestH]->hValue)
					lowestH = tempVec[b];
		}
	}
	return GetArrayAddress(lowestH);
};
int Room::GetGridAddress(sf::Vector2i address){
	return (address.x + (address.y * roomTiles.size()));
};
sf::Vector2i Room::GetArrayAddress(int x){
	int rowSize = roomTiles[0].size();
	return sf::Vector2i(x % rowSize,x / rowSize);
};
std::vector<int> Room::GetSurroundingTiles(int x){ // I'll optimise it later, promise.
	std::vector<int> tempVec;
	int rowSize = 128;//roomTiles[0].size();
	tempVec.push_back(x - 1);
	tempVec.push_back(x - rowSize);
	tempVec.push_back(x + 1);
	tempVec.push_back(x + rowSize);
	return tempVec;
};
int Room::GetHValue(int start,int end){
	int rowSize = 128;//roomTiles[0].size();
	return ((abs((end % rowSize) - (start % rowSize))) + (abs((end / rowSize) - (start / rowSize)))); 
};
void Room::InsertToOpenList(int a){
	if(openList.size() == 0){
		openList.push_back(a);
	}
	else{
		for(int x = 0; x < openList.size(); x++){
			if(grid[x]->fValue > grid[a]->fValue){// || x == openList.size() - 1){
				openList.insert(openList.begin() + (x - 1),a);
				break;
			}
		}
	}
};

