#include "LightObject.h"
#include "LTBL/Light/Light_Point.h"
#include "LTBL/Constructs/AABB.h"
#include "LTBL/Constructs/Vec2f.h"

std::vector<int> LightObject::tags;

LightObject::LightObject(int x,int y,tmx::MapObject* obj) : AmbienceObject(x,y,obj,true){
	myLight = new ltbl::Light_Point();
	myLight->m_radius = 15.0f;
	myLight->m_center = Vec2f(200.0f,200.0f);
	myLight->m_size = 15.0f;
	myLight->m_spreadAngle = 2.0f * static_cast<float>(3.14159);
	myLight->m_softSpreadAngle = 0.0f;
	myLight->CalculateAABB();
};
void LightObject::Update(sf::RenderTexture& panel){
	AmbienceObject::Update(panel);
};
ltbl::Light_Point* LightObject::getLight(){
	return myLight;
};