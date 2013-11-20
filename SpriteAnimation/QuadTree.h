#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"
#include "ShadowLine.h"
#include "QuadTreeNode.h"
#include "QuadTreeObject.h"
#include "Hull.h"
#include "Light.h"

class QuadTree{
public:
	QuadTree(AABB bounds);
	std::vector<QuadTreeObject*> SearchRegion(AABB);
	void Update();
	void AddObject(Light*);
	void AddObject(Hull*);
	void RemoveObject(Hull*);
	void RemoveObject(Hull*);
	QuadTreeObject* GetObjectFromTag(int tag);
	void DrawDebug(sf::RenderTexture* panel);
private:
	QuadTreeNode parentNode;
	int depth;
	AABB bounds;
};
#endif