#include "stdafx.h"
#include "ParticleSystemManager.hpp"


class BaseParticleSystem;

class BaseParticleSystemManager : public ParticleSystemManager {

	DynamicArray<BaseParticleSystem*> particlesSystems;

public:

	ParticleSystem* createParticleSystem(const AssetName&);
	ParticleSystem* createParticleSystem();
	void releaseParticleSystem(ParticleSystem*);

};


class BaseParticleSystem : public ParticleSystem {

	SharedPtr<BaseParticleSystemManager> manager;

public:

	BaseParticleSystem(BaseParticleSystemManager* manager_) : manager(manager_) {}
	BaseParticleSystem(ParticleSystemAsset* asset_, BaseParticleSystemManager* manager_) : manager(manager_), ParticleSystem(asset_) {}
	~BaseParticleSystem() { manager->releaseParticleSystem(this); }

};

ParticleSystem* BaseParticleSystemManager::createParticleSystem(const AssetName& assetName) {

	BaseParticleSystem* ps = NULL;

	ParticleSystemAsset* particleSystemAsset = new ParticleSystemAsset(assetName);
	particleSystemAsset->addStream(new ParticleStream);
	particleSystemAsset->addStream(new ParticleStream);
	particleSystemAsset->addStream(new ParticleStream);

	ps = new BaseParticleSystem(particleSystemAsset, this);

	return ps;
}

ParticleSystem* BaseParticleSystemManager::createParticleSystem() {

	BaseParticleSystem* ps = new BaseParticleSystem(this);
	particlesSystems.add(ps);

	return ps;
}

void BaseParticleSystemManager::releaseParticleSystem(ParticleSystem* ps) {

	particlesSystems.remove((BaseParticleSystem*)ps);

}


ParticleSystemManager* CreateParticleSystemManager() { return new BaseParticleSystemManager; }
