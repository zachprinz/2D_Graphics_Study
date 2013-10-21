#include "GroundItemSpawner.h"

GroundItemSpawner::MyPair GroundItemSpawner::CreateItem(int id,int x,int y,Room* room){
	Item tempItem(y);
	GroundItem* temp = new GroundItem(x,y,tempItem);
	temp->SetRoom(room);
	return (MyPair(tempItem.GetName(), temp));
};
