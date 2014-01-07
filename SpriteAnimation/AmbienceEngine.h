#ifndef AMBIENCEENGINE_H
#define AMBIENCEENGINE_H

#include"SFML\Graphics.hpp"
#include <iostream>
#include "AABB.h"
#include "GamePanel.h"
#include "LightEngine.h"
#include "Thor\Particles.hpp"
#include "Thor\Math.hpp"
#include "Thor\Animation.hpp"
#include "Clock.h"

class AmbienceEngine {
public:
    enum Condition {sun,rain,overcast,snow};
    AmbienceEngine(AABB,sf::View*);
    void Update();
    void DrawAmbience(sf::RenderTexture* panel);
    void SetCondition(Condition);
    LightEngine* lightEngine;
    thor::ParticleSystem* particleSystem;
    thor::UniversalEmitter emitter;
    thor::ForceAffector* gravityAffector;
    thor::FadeAnimation* fadeAffector;
    sf::Clock particleClock;
private:
	sf::View* myView;
       sf::Texture m_particleTexture;
};
#endif