#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"
#include "ShadowLine.h"
#include "QuadTree.h"
#include "QuadTreeObject.h"
#include "Hull.h"
#include "Light.h"

class QuadTreeNode{
public:
	QuadTreeNode(AABB bounds);
	QuadTreeNode(AABB bounds, int depthLevel, QuadTreeNode* parent);
	static std::vector<QuadTreeObject*> searchingObjList;
	bool Sort(QuadTreeObject*);
	bool CheckMerge();
	bool CheckEmpty();
	void Merge();
	void Merge(QuadTreeObject*);
	bool Partition(QuadTreeObject*);
	AABB GetBounds();
	void CheckStillContainsOcupants();
	void DrawBounds(sf::RenderTexture* panel);
private:
	std::vector<QuadTreeObject*> childOccupants;
	QuadTreeObject* ocupant;
	std::vector<int> occupantsTags;
	int depthLevel;
	AABB bounds;
	bool hasChildren;
	bool hasOcupant;
	QuadTreeNode* parent;
	std::vector<QuadTreeNode*> children;
	bool isRoot;
};

#endif