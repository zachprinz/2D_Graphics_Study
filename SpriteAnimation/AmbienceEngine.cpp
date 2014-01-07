#include "AmbienceEngine.h"
#include "Thor/Animation.hpp"
#include "Thor/Math/Distributions.hpp"
#include "SpritePanel.h"
#include "Game.h"

AmbienceEngine::AmbienceEngine(AABB size,sf::View* view){
    	lightEngine = new LightEngine(size,*view,sf::Color(47,102,111,150));
        m_particleTexture.loadFromFile("Images/particle.png");
	particleSystem = new thor::ParticleSystem();
	particleSystem->setTexture(m_particleTexture);
	particleSystem->addTextureRect(sf::IntRect(0,0,32,32));
	emitter.setEmissionRate(120.f);
	emitter.setParticleScale(sf::Vector2f(0.5f,0.5f));
	//emitter.setParticlePosition( thor::Distributions::circle(sf::Vector2f(1000,1000), 900) );   // Emit particles in given circle
	//emitter.setParticleVelocity( thor::Distributions::deflect(sf::Vector2f(20,0), 15.f) ); // Emit towards direction with deviation of 15°
	//emitter.setParticleRotation( thor::Distributions::uniform(0.f, 360.f) );
	emitter.setParticleLifetime( thor::Distributions::uniform(sf::seconds(4), sf::seconds(6)) );
	particleSystem->addEmitter(thor::refEmitter(emitter));
	sf::Vector2f acceleration(0.f, 100.f);
	gravityAffector = new thor::ForceAffector(acceleration);
	particleSystem->addAffector(thor::refAffector(*gravityAffector));
	fadeAffector = new thor::FadeAnimation(0.15f, 0.15f);
	particleSystem->addAffector(thor::AnimationAffector(*fadeAffector));
	myView = view;
};

void AmbienceEngine::Update(){
    	lightEngine->UpdateLights();
	lightEngine->SetView(*myView);
	emitter.setParticlePosition(thor::Distributions::rect(myView->getCenter() - sf::Vector2f(0,(Game::resolution.y / 2.0) + 100.0f),sf::Vector2f(Game::resolution.x / 2.0,100)));
	particleSystem->update(particleClock.restart());
};

void AmbienceEngine::DrawAmbience(sf::RenderTexture* panel){
	lightEngine->DrawLights(panel);
        panel->draw(*particleSystem);
};

void AmbienceEngine::SetCondition(Condition condition){

};