#include "QuadTreeNode.h"

std::vector<QuadTreeObject*> QuadTreeNode::searchingObjList;

QuadTreeNode::QuadTreeNode(AABB bounds){
	this->bounds = bounds;
	this->depthLevel = 0;
	hasChildren = false;
	hasOcupant = false;
	parent = NULL;
	isRoot = true;
};
QuadTreeNode::QuadTreeNode(AABB bounds, int depthLevel, QuadTreeNode* parent){
	this->bounds = bounds;
	this->depthLevel = depthLevel;
	hasChildren = false;
	hasOcupant = false;
	this->parent = parent;
	isRoot = false;
};
bool QuadTreeNode::Sort(QuadTreeObject* obj){
	if(bounds.Contains(obj->GetBounds())){
		if(!hasChildren){
			if(!hasOcupant){
				ocupant = obj;
				obj->housing = this;
				return true;
			}
			else{
				if(Partition(obj))
					return true;
				else
					return false;
			}
		}
		else{
			if(hasChildren){
				for(int x = 0; x < children.size(); x++){
					if(children[x]->Sort(obj))
						return true;
				}
			}
			return false;
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
	for(int y = 0; y < 2; y++){
		for(int x = 0; x < 2; x++){
			children.push_back(new QuadTreeNode(AABB(Vec2f(bounds.GetUpperBound().x + (y*(bounds.GetCenter().x - bounds.GetLowerBound().x)),
														   bounds.GetLowerBound().y + (x*(bounds.GetCenter().y - bounds.GetUpperBound().y))),
													 Vec2f(bounds.GetUpperBound().x + (2*(y*(bounds.GetCenter().x - bounds.GetLowerBound().x))),
														   bounds.GetLowerBound().y + (2*(x*(bounds.GetCenter().y - bounds.GetUpperBound().y))))),
													 (depthLevel+1)));
			Sort(ocupant);
			ocupant = NULL;
			hasOcupant = false;
			Sort(obj);
		}
	}
};
AABB QuadTreeNode::GetBounds(){
	return bounds;
};
void QuadTreeNode::CheckStillContainsOcupants(){
	if(hasOcupant){
		if(!bounds.Contains(ocupant->GetBounds())){
			parent->Sort(ocupant);
			ocupant = NULL;
			hasOcupant = false;
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
	rect.setOutlineColor(sf::Color(50,50,50,255));
	rect.setFillColor(sf::Color(0,0,0,0));
	rect.setPosition(bounds.GetUpperBound().x,bounds.GetUpperBound().y));
	panel->draw(rect);
};