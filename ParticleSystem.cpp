#include "stdafx.h"
#include "ParticleSystem.hpp"


void ParticleEmitter::reset() {

}

void ParticleEmitter::update(float timeDelta) {

	timeTotal += timeDelta;

}

void ParticleEmitter::onReset() {
}

void ParticleEmitter::onUpdate(float timeDelta) {

}


void ParticleEffector::reset() {

}

void ParticleEffector::update(float timeDelta) {

	timeTotal += timeDelta;
}

void ParticleEffector::onReset() {
}

void ParticleEffector::onUpdate(float timeDelta) {

}



