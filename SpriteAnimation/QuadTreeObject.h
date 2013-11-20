#ifndef QUADTREEOBJECT_H
#define QUADTREEOBJECT_H

#include "Light.h"
#include "Hull.h"
#include "AABB.h"
#include "QuadTreeNode.h"

class QuadTreeObject{
public:
	QuadTreeObject(Light*);
	QuadTreeObject(Hull*);
	Hull* myHull;
	Light* myLight;
	AABB bounds;
	AABB GetBounds();
	QuadTreeNode* housing;
};

#endif