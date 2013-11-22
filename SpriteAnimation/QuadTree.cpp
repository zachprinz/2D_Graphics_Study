#include "QuadTree.h"
#include "QuadTreeObject.h"
#include "QuadTreeNode.h"
#include <iostream>

QuadTree::QuadTree(AABB bounds){
	this->bounds = bounds;
	bounds.CalculateBounds();
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
	parentNode = new QuadTreeNode(bounds);
};
QuadTree::QuadTree(){

};
std::vector<QuadTreeObject*> QuadTree::SearchRegion(AABB reg){
	return parentNode->SearchRegion(reg);
};
void QuadTree::Update(){
	parentNode->CheckStillContainsOcupants();
};
void QuadTree::AddObject(Light* obj){
	QuadTreeObject* temp = new QuadTreeObject(obj);
	if(!parentNode->Sort(temp)){
		std::cout << "Object was not sorted. Couldn't find an appropriate place for it." << std::endl;
	}
	ocupants.push_back(temp);
};
void QuadTree::AddObject(Hull* obj){
	std::cout << "Adding Object" << std::endl;
	QuadTreeObject* temp = new QuadTreeObject(obj);
	if(!parentNode->Sort(temp)){
		std::cout << "Object was not sorted. Couldn't find an appropriate place for it." << std::endl;
	}
	ocupants.push_back(temp);
};
void QuadTree::RemoveObject(Hull* obj){
	for(int x = 0; x < ocupants.size(); x++){
		if(ocupants[x]->myHull == obj)
			ocupants[x]->housing->RemoveOcupant();
	}
};
void QuadTree::RemoveObject(Light* obj){
	for(int x = 0; x < ocupants.size(); x++){
		if(ocupants[x]->myLight == obj)
			ocupants[x]->housing->RemoveOcupant();
	}
};
void QuadTree::DrawDebug(sf::RenderTexture* panel){
	parentNode->DrawBounds(panel);
};