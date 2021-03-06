#pragma once

#ifndef __PS_HPP__
#define __PS_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Asset.hpp"
#include "Particle.hpp"

class ParticleSystemManager;


enum PARAM_TYPE {
	PARAM_CONST,
	PARAM_RANDOM_BETWEEN
};

template<class T> struct TimeValue {
	float key;
	T value;
	bool operator<(const TimeValue& other) const { return key < other.key; }
};


template<typename T> class TimeValues {

	//DynamicArray<TimeValue> array;
	std::vector<TimeValue<T>> array;

public:

	const T& getValue(float time) {
	
		check(array.size());

		if (array[0].key >= time) {
			return array[0].value;
		}

		if (array[array.size()-1].key <= time) {
			return array[array.size() - 1].value;
		}


		for (unsigned i = 0; i < array.size(); i++) {
			
			if (array[i].key <= time) {
				if (array.size() == 1) {
					return array[0].value;
				} else {
					const float alpha = (time - array[i].key) / (array[i + 1].key - array[i].key);
					return Lerp<T, float>(array[i].value, array[i+1].value, alpha);
				}
			}
		}

		return 	array[0].value;

	}

	void add(float time, const T& value) {
		
		TimeValue<T> timeValue;
		timeValue.key = time;
		timeValue.value = value;

		array.push_back(timeValue);
		std::sort(array.begin(), array.end());
		
	}

};




template<class T> class ValueParam {

	PARAM_TYPE type;
	T minValue, maxValue, currentValue;

public:

	ValueParam(const T& currentValue_) : currentValue(currentValue_){}
	ValueParam(const T& minValue_, const T& maxValue_) {}

	const T& getMaxValue() const { return maxValue; }

	T getValue(float deltaTime) const {
		
		switch (type) {
		
		};

	}

};

struct ParticleEmitterLifeTimeParam : public ValueParam<float> {};
struct ParticleEmitterCountParam : public ValueParam<float> {};



struct ParticleInfo {};

/*
struct PARTICLE_TYPE {
	PARTICLE_QUAD =0,
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
*/


#define MAX_PARTICLES 64

class ParticleStorage : public Referenced {

	unsigned currentNumParticles;

	Particle particle[MAX_PARTICLES];

public:

	ParticleStorage() : currentNumParticles(0) {}

	unsigned getNumParticles() const { return currentNumParticles; }
	unsigned getMaxNumParticles() const { return MAX_PARTICLES; }

	Particle* getParticle(unsigned index) { return &particle[index]; }
	Particle* spawnParticle() { 
		check(currentNumParticles<MAX_PARTICLES);
		particle[currentNumParticles].reset();
		return &particle[currentNumParticles++]; 
	}

	
	//const Particle& getParticle(unsigned index) const { return particle[index]; }

	void update(float deltaTime) {
	
		unsigned alived = 0;
		for (unsigned i = 0; i < MAX_PARTICLES; i++) {
			particle[i].update(deltaTime);
			alived += particle[i].isAlive() ? 1 : 0;
		}
	
		std::sort(&particle[0], &particle[MAX_PARTICLES], sortParticleByLifeTime);

	}

	void killAllParticles() {}

};


class ParticleEmitter : public Referenced {

	SharedPtr<Material> material;
	float totalTime;
	Vector position, velocity;

protected:

	virtual void onSpawn(Particle*);
	virtual void onReset();
	virtual void onUpdate(float timeDelta);

public:

	ParticleEmitter() : totalTime(0.0f) {}

	Material* getMaterial() const { return material; }

	void reset();
	void update(float deltaTime);

};

class ParticleAffector : public Referenced {

	float timeTotal;

protected:

	virtual void onReset();
	virtual void onUpdate(float timeDelta);

public:

	ParticleAffector() : timeTotal(0.0f) {}

	void reset();
	void update(float timeDelta);

	virtual void applay(ParticleStorage*) {}

};

class ParticleStream : public Referenced {

	SharedPtr<Material> material;
	SharedPtr<ParticleEmitter> emitter;
	DynamicArray<SharedPtr<ParticleAffector>> affectos;

public:

	Material* getMaterial() const { return material; }

	ParticleEmitter* getEmitter()const;


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