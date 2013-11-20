#include "QuadTreeObject.h"

QuadTreeObject::QuadTreeObject(Light* light){
	bounds = light->GetBounds();
	myLight = light;
};

QuadTreeObject::QuadTreeObject(Hull* hull){
	bounds = hull->GetBounds();
	myHull = hull;
};
AABB QuadTreeObject::GetBounds(){
	return bounds;
};