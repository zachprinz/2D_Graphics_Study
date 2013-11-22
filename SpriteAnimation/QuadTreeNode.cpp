#include "QuadTreeNode.h"

std::vector<QuadTreeObject*> QuadTreeNode::searchingObjList;
std::vector<QuadTreeObject*> QuadTreeNode::returningObjList;


QuadTreeNode::QuadTreeNode(AABB bounds){
	this->bounds = bounds;
	bounds.CalculateBounds();
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
	this->depthLevel = 0;
	hasChildren = false;
	hasOcupant = false;
	parent = NULL;
	isRoot = true;
};
QuadTreeNode::QuadTreeNode(AABB bounds, int depthLevel, QuadTreeNode* parent){
	this->bounds = bounds;
	bounds.CalculateBounds();
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
	this->depthLevel = depthLevel;
	hasChildren = false;
	hasOcupant = false;
	this->parent = parent;
	isRoot = false;
};
std::vector<QuadTreeObject*> QuadTreeNode::SearchRegion(AABB reg){
	FindObjects(reg);
	return returningObjList;
	returningObjList.clear();
};
bool QuadTreeNode::FindObjects(AABB reg){
	if(reg.Contains(bounds)){
		if(hasOcupant){
			if(reg.Contains(ocupant->GetBounds())){
				returningObjList.push_back(ocupant);
				return true;
			}
		}
		if(hasChildren){
			for(int x = 0; x < children.size(); x++){
				children[x]->FindObjects(reg);
			}
		}
	}
	return true;
};
bool QuadTreeNode::Sort(QuadTreeObject* obj){
	std::cout << "Sorting..." << std::endl;
	if(bounds.Contains(obj->GetBounds())){
		if(!hasChildren){
			if(!hasOcupant){
				std::cout << "Found Home" << std::endl;
				ocupant = obj;
				obj->housing = this;
				hasOcupant = true;
				return true;
			}
			else{
				if(Partition(obj))
					return true;
				return false;
			}
		}
		for(int x = 0; x < children.size(); x++){
			if(children[x]->Sort(obj))
				return true;
		}
	}
	return false;
};
bool QuadTreeNode::CheckMerge(){
	CheckEmpty();
	if(searchingObjList.size() > 1)
		return false;
	if(searchingObjList.size() == 1)
		Merge(searchingObjList[0]);
	if(searchingObjList.size() == 0)
		parent->CheckMerge();
	searchingObjList.clear();
};
bool QuadTreeNode::CheckEmpty(){
	if(hasOcupant){
		QuadTreeNode::searchingObjList.push_back(ocupant);
		if(searchingObjList.size() > 1){
			return false;
		}
	}
	if(hasChildren){
		for(int x = 0; x < children.size(); x++){
			if(!children[x]->CheckEmpty())
				break;
		}
	}
	return false;
};
void QuadTreeNode::Merge(){
	if(hasChildren){
		children.clear();
		hasChildren = false;
	}
};
void QuadTreeNode::Merge(QuadTreeObject* obj){
	Merge();
	Sort(obj);
};
bool QuadTreeNode::Partition(QuadTreeObject* obj){
	if(bounds.GetDims().x > 1 && bounds.GetDims().y > 1){
	std::cout << "Partitioning" << std::endl;
	for(int y = 0; y < 2; y++){
		for(int x = 0; x < 2; x++){
			children.push_back(new QuadTreeNode(AABB(Vec2f(bounds.GetLowerBound().x + (y*(bounds.GetDims().x/2.0f)),
														   bounds.GetLowerBound().y + (x*(bounds.GetDims().y/2.0f))),
													 Vec2f(bounds.GetLowerBound().x + ((y+1)*(bounds.GetDims().x/2.0f)),
														   bounds.GetLowerBound().y + ((x+1)*(bounds.GetDims().y/2.0f)))),
													 (depthLevel+1),this));
		}
	}
	hasOcupant = false;
	hasChildren = true;
	for(int x = 0; x < children.size(); x++){
			if(children[x]->Sort(ocupant)){
				for(int y = 0; y < children.size(); y++){
					if(children[x]->Sort(obj))
						ocupant = NULL;
						return true;
				}
				ocupant = NULL;
				return false;
			}
	}
	ocupant = NULL;
	return false;
	}
	return false;
};
AABB QuadTreeNode::GetBounds(){
	return bounds;
};
void QuadTreeNode::CheckStillContainsOcupants(){
	if(hasOcupant){
		if(!bounds.Contains(ocupant->GetBounds())){
			ocupant = NULL;
			hasOcupant = false;
			if(!isRoot)
				parent->Sort(ocupant);
		}
	}
	if(hasChildren){
		for(int x = 0; x < children.size(); x++){
			children[x]->CheckStillContainsOcupants();
		}
	}
};
void QuadTreeNode::DrawBounds(sf::RenderTexture* panel){
	sf::RectangleShape rect(sf::Vector2f(bounds.GetDims().x,bounds.GetDims().y));
	rect.setOutlineColor(sf::Color(0 + (2*depthLevel),250 - (2*depthLevel),0,255));
	rect.setOutlineThickness(3.0f);
	rect.setFillColor(sf::Color(255,0 + (2*depthLevel),0,70));
	rect.setPosition(bounds.GetUpperBound().x,bounds.GetUpperBound().y);
	panel->draw(rect);
	if(hasChildren){
		for(int x = 0; x < children.size(); x++){
			children[x]->DrawBounds(panel);
		}
	}
};
void QuadTreeNode::RemoveOcupant(){
	ocupant = NULL;
	hasOcupant = false;
	parent->CheckMerge();
};