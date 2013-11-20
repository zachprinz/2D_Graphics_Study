#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"
#include "ShadowLine.h"
#include "QuadTreeObject.h"
#include "Hull.h"
#include "Light.h"

class QuadTreeNode{
public:
	QuadTreeNode(AABB bounds, int depthLevel);
	void Sort(QuadTreeNode*);
	void CheckMerge();
	void Merge();
	void Partition();
	void Remove(int tag);
	void Remove(QuadTreeNode*);
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
};

#endif