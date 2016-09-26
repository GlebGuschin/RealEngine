#include "stdafx.h"
#include "ParticleSystem.hpp"


void ParticleEmitter::onSpawn(Particle*) {
	
}

void ParticleEmitter::onReset() {

}

void ParticleEmitter::onUpdate(float timeDelta) {

}

void ParticleEmitter::reset() {

	totalTime = 0.0f;
	onReset();

}

void ParticleEmitter::update(float deltaTime) {

	totalTime += deltaTime;
	onUpdate(deltaTime);

}


