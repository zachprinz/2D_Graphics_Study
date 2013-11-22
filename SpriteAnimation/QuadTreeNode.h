#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ShadowLine.h"
#include "QuadTreeObject.h"

class QuadTree;
class QuadTreeNode{
public:
	QuadTreeNode(AABB bounds);
	QuadTreeNode(AABB bounds, int depthLevel, QuadTreeNode* parent);
	static std::vector<QuadTreeObject*> searchingObjList;
	static std::vector<QuadTreeObject*> returningObjList;
	bool Sort(QuadTreeObject*);
	bool CheckMerge();
	bool CheckEmpty();
	void Merge();
	void Merge(QuadTreeObject*);
	bool Partition(QuadTreeObject*);
	AABB GetBounds();
	void CheckStillContainsOcupants();
	void DrawBounds(sf::RenderTexture* panel);
	void RemoveOcupant();
	std::vector<QuadTreeObject*> SearchRegion(AABB);
	QuadTree* tree;
private:
	bool FindObjects(AABB);
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