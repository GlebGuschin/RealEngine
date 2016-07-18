#pragma once

#ifndef __PS_M_HPP__
#define __PS_M_HPP__

#include "ParticleSystem.hpp"

class ParticleSystemManager : public Referenced {

public:

	virtual ParticleSystem* createParticleSystem(const AssetName&) = 0;
	virtual ParticleSystem* createParticleSystem() = 0;
	virtual void releaseParticleSystem(ParticleSystem*) = 0;

};

ParticleSystemManager* CreateParticleSystemManager();

#endif