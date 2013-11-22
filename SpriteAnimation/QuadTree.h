#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "QuadTreeNode.h"


class QuadTree{
public:
	QuadTree(AABB bounds);
	QuadTree();
	std::vector<QuadTreeObject*> SearchRegion(AABB);
	std::vector<QuadTreeObject*> ocupants;
	void Update();
	void AddObject(Light*);
	void AddObject(Hull*);
	void RemoveObject(Hull*);
	void RemoveObject(Light*);
	void DrawDebug(sf::RenderTexture* panel);
private:
	QuadTreeNode* parentNode;
	int depth;
	AABB bounds;
};
#endif