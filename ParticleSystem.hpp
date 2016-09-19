#pragma once

#ifndef __PS_HPP__
#define __PS_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Asset.hpp"

class ParticleSystemManager;


struct ParticleInfo {


};


struct Particle {


};

class ParticleStorage : public Referenced {

};


class ParticleEmitter : public Referenced {

	SharedPtr<Material> material;
	float timeTotal;

protected:

	virtual void onReset();
	virtual void onUpdate(float timeDelta);

public:

	ParticleEmitter() : timeTotal(0.0f) {}

	Material* getMaterial() const { return material; }

	void reset();
	void update(float timeDelta);

};

class ParticleEffector : public Referenced {

	float timeTotal;

protected:

	virtual void onReset();
	virtual void onUpdate(float timeDelta);

public:

	ParticleEffector() : timeTotal(0.0f) {}

	void reset();
	void update(float timeDelta);

};

class ParticleStream : public Referenced {
	SharedPtr<Material> material;
public:
	Material* getMaterial() const { return material; }
};



class ParticleSystemAsset : public Asset {

	DynamicArray<SharedPtr<ParticleStream>> streams;

public:

	ParticleSystemAsset() {}
	ParticleSystemAsset(const AssetName& assetName) : Asset(assetName) {}

	unsigned getNumStreams() const { return (unsigned)streams.size(); }
	ParticleStream* getStream(unsigned streamIndex) const { return streams[streamIndex]; }
	void addStream(ParticleStream* particleStream) { streams.add(particleStream); }
	void removeStream(ParticleStream*particleStream) { streams.remove(particleStream); }

	void load() {}
	void unload() {}
	void reload() {}

};



class ParticleSystem : public Referenced {

protected:

	SharedPtr<ParticleSystemAsset> asset;
	DynamicArray<SharedPtr<ParticleStream>> streams;

public:

	ParticleSystem() {}
	ParticleSystem(ParticleSystemAsset* asset_) : asset(asset_) {}


	ParticleSystemAsset* getAsset() const { return asset; }

	virtual unsigned getNumStreams() const { return (unsigned)streams.size(); }
	virtual ParticleStream* getStream(unsigned index) const { return streams[index]; };
	virtual void addStream(ParticleStream* stream) { return streams.add(stream); };
	virtual void removeStream(ParticleStream* stream) { return streams.remove(stream); };
	
	virtual ParticleSystemManager* getManager() const { return NULL; }

	virtual void refreshFromAsset() {
	
		streams.clear();

		if (asset) {
			for (unsigned i = 0; i < asset->getNumStreams(); i++) {
				addStream(asset->getStream(i));
			}
		}
	
	
	}

};

/*
class ParticleSystemManager : public Referenced {

public:

	virtual ParticleSystem* createParticleSystem(const AssetName&) = 0;
	virtual ParticleSystem* createParticleSystem() = 0;
	virtual void releaseParticleSystem(ParticleSystem*) = 0;	

};
*/




#endif