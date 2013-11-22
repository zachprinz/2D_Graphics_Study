#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "AmbienceObject.h"
#include "Light.h"

class LightObject : public AmbienceObject
{
public:
	LightObject(int,int,tmx::MapObject*);
	void Update(sf::RenderTexture&);
	static std::vector<int> tags;
	Light* getLight();
	Light* myLight;
private:
};

#endif