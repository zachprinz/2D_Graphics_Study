#ifndef QUADTREEOBJECT_H
#define QUADTREEOBJECT_H

class QuadTreeObject{
public:
	QuadTreeObject(Light*);
	QuadTreeObject(Hull*);
	Hull* myHulll;
	Light* myLight;
};

#endif