#include "QuadTree.h"
#include "QuadTreeObject.h"
#include "QuadTreeNode.h"
#include <iostream>

QuadTree::QuadTree(AABB bounds){

};
std::vector<QuadTreeObject*> QuadTree::SearchRegion(AABB){

};
void QuadTree::Update(){

};
void QuadTree::AddObject(Light* obj){
	QuadTreeObject* temp = new QuadTreeObject(obj);
	if(!parentNode.Sort(temp)){
		std::cout << "Object was not sorted. Couldn't find an appropriate place for it." << std::endl;
	}
};
void QuadTree::AddObject(Hull* obj){
	QuadTreeObject* temp = new QuadTreeObject(obj);
	if(!parentNode.Sort(temp)){
		std::cout << "Object was not sorted. Couldn't find an appropriate place for it." << std::endl;
	}
};
void QuadTree::RemoveObject(Hull*){

};
void QuadTree::RemoveObject(Hull*){

};
QuadTreeObject* QuadTree::GetObjectFromTag(int tag){

};
void QuadTree::DrawDebug(sf::RenderTexture* panel){

};