#pragma once

#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Material.hpp"



enum PARTICLE_TYPE {
		PARTICLE_QUAD = 0,
		PARTICLE_BEAM = 1
};

class Particle {

	Vector position, velocity;
	float currentLifeTime, maxLifeTime;
	bool dead : 1;
	Color color;

public:

	Particle() { reset(); }

	bool operator<(const Particle& particle) const { return currentLifeTime < particle.currentLifeTime; }

	void reset() {}
	void setMaxLifeTime(float maxLifeTime_) { maxLifeTime = maxLifeTime_; }
	bool isAlive() const { return !dead; }
	bool isDead() const { return dead; }
	void kill() {}
	float getCurrentLifeTime() const { return currentLifeTime; }

	void setColor(const Color& color_) { color = color_; }
	const Color& getColor() const { return color; }
	void applyColor(const Color& color_) { color = color_; }

	const Vector& getPosition() const { return position; }
	void setPosition(const Vector&position_) { position = position_; }
	void applyPosition(const Vector&position_) { position = position + position_; }

	void update(float deltaTime) {
		currentLifeTime += deltaTime;
		dead = currentLifeTime >= maxLifeTime;
		position = position + velocity * deltaTime;
	}

};

inline bool sortParticleByLifeTime(const Particle& p1, const Particle& p2) { return p1.getCurrentLifeTime() < p2.getCurrentLifeTime(); }





#endif