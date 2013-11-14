#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "AmbienceObject.h"
#include "LTBL\Light\Light_Point.h"

class LightObject : public AmbienceObject
{
public:
	LightObject(int,int,tmx::MapObject*);
	void Update(sf::RenderTexture&);
	static std::vector<int> tags;
	ltbl::Light_Point* getLight();
private:
	ltbl::Light_Point* myLight;
};

#endif