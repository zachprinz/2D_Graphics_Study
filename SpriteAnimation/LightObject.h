#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include "AmbienceObject.h"

class LightObject : public AmbienceObject
{
public:
	LightObject(int,int,tmx::MapObject*);
	void Update(sf::RenderTexture&);
	static std::vector<int> tags;
	//Light* getLight();
private:
};

#endif