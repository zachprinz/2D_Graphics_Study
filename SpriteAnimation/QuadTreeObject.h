#ifndef QUADTREEOBJECT_H
#define QUADTREEOBJECT_H

#include "Light.h"
#include "Hull.h"
#include "AABB.h"

class QuadTreeNode;
class QuadTreeObject
{
public:
	QuadTreeObject(Light*);
	QuadTreeObject(Hull*);
	Hull* myHull;
	Light* myLight;
	AABB bounds;
	AABB GetBounds();
	bool isHull;
	QuadTreeNode* housing;
};
#endif