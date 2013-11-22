#include "QuadTreeObject.h"

QuadTreeObject::QuadTreeObject(Light* light){
	isHull = false;
	bounds = light->GetBounds();
	myLight = light;
};

QuadTreeObject::QuadTreeObject(Hull* hull){
	isHull = true;
	bounds = hull->GetBounds();
	myHull = hull;
};
AABB QuadTreeObject::GetBounds(){
	if(isHull)
		return myHull->GetBounds();
	else
		return myLight->GetBounds();
};