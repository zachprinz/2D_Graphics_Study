#include "QuadTreeNode.h"
#include "QuadTree.h"

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
	tree = parent->tree;
};
std::vector<QuadTreeObject*> QuadTreeNode::SearchRegion(AABB reg){
	FindObjects(reg);
	return returningObjList;
	returningObjList.clear();
};
bool QuadTreeNode::FindObjects(AABB reg){
	if(reg.Contains(bounds)){
		if(hasOcupant){
			if(reg.Contains(ocupants[0]->GetBounds())){
				returningObjList.push_back(ocupants[0]);
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
	if(bounds.Contains(obj->GetPoint())){
		if(!hasChildren){
			if(!hasOcupant){
				std::cout << "Found Home" << std::endl;
				if(ocupants.size() >= 1)
					ocupants[0] = obj;
				else
					ocupants.push_back(obj);
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
	searchingObjList.clear();
	std::cout << "Checking Merge" << std::endl;
	CheckEmpty();
	int numOcupants = searchingObjList.size();
	std::cout << "Size: " << std::to_string(numOcupants) << std::endl;
	if(numOcupants > 1)
		return false;
	if(numOcupants == 1)
		Merge(searchingObjList[0]);
	if(numOcupants < 1){
		Merge();
	}
	searchingObjList.clear();
};
bool QuadTreeNode::CheckEmpty(){
	if(hasOcupant){
		searchingObjList.push_back(ocupants[0]);
	}
	else
		if(hasChildren){
			for(int x = 0; x < children.size(); x++){
				children[x]->CheckEmpty();
			}
		}
	return true;
};
void QuadTreeNode::Merge(){
	std::cout << "Merging" << std::endl;
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
	if(tree->parentNode->Sort(obj) && tree->parentNode->Sort(ocupants[0])){
		ocupants[0] == NULL;
		return true;
	}
	/*
	for(int x = 0; x < children.size(); x++){
			if(children[x]->Sort(ocupants[0])){
				for(int y = 0; y < children.size(); y++){
					if(children[y]->Sort(obj))
						ocupants[0] = NULL;
						return true;
				}
				if(tree->parentNode->Sort(obj))
					return true;
				ocupants[0] = NULL;
				return false;
			}
	}
	for(int y = 0; y < children.size(); y++){
		if(children[y]->Sort(obj)){
			if(tree->parentNode->Sort(ocupants[0]))
				return true;
			else{
				ocupants[0] == NULL;
				return false;
			}
		}
	}
	ocupants[0] = NULL;
	return false;
	}
	*/
	}
	return false;
};
AABB QuadTreeNode::GetBounds(){
	return bounds;
};
void QuadTreeNode::CheckStillContainsOcupants(){
	if(hasOcupant){
		if(!bounds.Contains(ocupants[0]->GetPoint())){
			std::cout << "Re-Evaluating" << std::endl;
			hasOcupant = false;
			if(!isRoot){
				if(!parent->Sort(ocupants[0])){
					tree->parentNode->Sort(ocupants[0]);
				}
				ocupants[0] = NULL;
				parent->CheckMerge();
			}
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
	if(hasOcupant)
		rect.setFillColor(sf::Color(255,0,0,70));
	else
		rect.setFillColor(sf::Color(255,0,0,0));
	rect.setPosition(bounds.GetLowerBound().x,bounds.GetLowerBound().y);
	panel->draw(rect);
	if(hasChildren){
		for(int x = 0; x < children.size(); x++){
			children[x]->DrawBounds(panel);
		}
	}
};
void QuadTreeNode::RemoveOcupant(){
	ocupants[0] = NULL;
	hasOcupant = false;
	parent->CheckMerge();
};