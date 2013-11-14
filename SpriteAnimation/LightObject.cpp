#define _USE_MATH_DEFINES
#include "LightObject.h"
#include "LTBL/Light/Light_Point.h"
#include "LTBL/Constructs/AABB.h"
#include "LTBL/Constructs/Vec2f.h"
#include "SpritePanel.h"
#include <cmath>
#include <math.h>

std::vector<int> LightObject::tags;

LightObject::LightObject(int x,int y,tmx::MapObject* obj) : AmbienceObject(x,y,obj,true){
	myLight = new ltbl::Light_Point();
	myLight->m_radius = 300.0f;
	myLight->m_center = Vec2f(x*32,y*32);
	myLight->m_size = 30.0f;
	myLight->m_spreadAngle = 2.0f * static_cast<float>(M_PI);
	myLight->m_softSpreadAngle = 0.0f;
	myLight->m_intensity = 8.0f;
    myLight->m_bleed = 0;
    myLight->m_color =  Color3f(1, 0.95, 0.40);
	myLight->CalculateAABB();
	SpritePanel::instance->AddLightSource(this);
	myLight->SetAlwaysUpdate(true);
	myLight->RenderLightSoftPortion();
	myLight->RenderLightSolidPortion();
};
void LightObject::Update(sf::RenderTexture& panel){
	AmbienceObject::Update(panel);
	myLight->TreeUpdate();
};
ltbl::Light_Point* LightObject::getLight(){
	return myLight;
};