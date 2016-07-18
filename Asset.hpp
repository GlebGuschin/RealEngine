#pragma once

#ifndef __ASSET_HPP__
#define __ASSET_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "String.hpp"
#include "MemoryBuffer.hpp"

typedef ResourceName AssetName;

/*
class AssetName {

	String name;
	String path;
	String file;
	String ext;

public:

	AssetName() {}
	AssetName(const String& name_) : name(name) { name.replaceSlash(); }

	const String getString() const { return name; }

	bool operator<(const AssetName& rhs) const { return( name < rhs.name ); }
};
*/

class Asset;

class AssetListener : public Listener {
public:
	virtual void onChanged(Asset*) {}
	virtual void onStartLoading(Asset*) = 0;
	virtual void onStopLoading(Asset*) = 0;
	virtual void onStartUnLoading(Asset*) {}
	virtual void onStopUnLoading(Asset*) {}

};

enum ASSET_STATE {
 ASSET_STATE_EMPTY = 0,
 ASSET_STATE_LOADING = 1,
 ASSET_STATE_FULL = 2,
 ASSET_STATE_UNLOADING = 3
};

class Asset : public Referenced {

	ASSET_STATE state;
	AssetName name;
	SharedPtr<MemoryBuffer> buffer;

	DynamicArray<SharedPtr<AssetListener>> listeners;

protected:

	void setState(ASSET_STATE state_) { state = state_; }

	Asset() : state(ASSET_STATE_EMPTY) {}
	Asset(const AssetName& name_) : name(name_), state(ASSET_STATE_EMPTY) {}
	
	MemoryBuffer* loadFromFile(size_t size=0, size_t offset = 0);

	virtual MemoryBuffer*  getBuffer() const { return buffer; }

public:

	ASSET_STATE getState() const { return state; }
	const AssetName& getName() const { return name; }

	virtual void load();
	virtual void unload();
	virtual void reload();

	void addListener(AssetListener* listener) { listeners.add(listener); }
	void removeListener(AssetListener*  listener)  { listeners.remove(listener); }

protected:

	typedef std::map<AssetName, Asset*> MapType;
	static MapType Map;
	
	static void Remove(Asset* asset);			
	static void Remove(const AssetName& name);		
	//static void Add(const AssetName& name, Asset* asset);
		
public:

	static Asset* Find(const AssetName& name);
	//static MemoryBuffer* Load(const AssetName& name);
	//static Asset* Create(const AssetName& name);

	static void Add(Asset* asset);

protected:

	~Asset() {

		Remove(this);

	}


};








/*
template< typename Key, typename Value>
class AssetStorage {
	std::map<Key, Value*> map;
public:
	void add(const Key& key, const Value& value) {
		std::map<Key, Value*>::iterator it = map.find(key);
		///if ( it ==)
	}
	bool find(const Key& key) { 	
	}
	void remove(const Key& key) {	
	}
};
*/

//class Texture : public Object {};

//typedef Asset<Texture> TextureAsset;






/**

	class MaterialAsset : public Asset {

	//SharedPtr<Material> material;

	MaterialAsset() {}
	~MaterialAsset() {}

public:

	static MaterialAsset* Create(const AssetName& name, bool recreate = false) { return new MaterialAsset; }

};


class MeshAsset : public Asset {

	MeshAsset() {}
	~MeshAsset() {}

public:

	static MeshAsset* Create(const AssetName& name, bool recreate = false) { return new MeshAsset; }

};

class ParticleSystemAsset : public Asset {

	ParticleSystemAsset() {}
	~ParticleSystemAsset() {}

public:

	static ParticleSystemAsset* Create(const AssetName& name, bool recreate = false) { return new ParticleSystemAsset; }

};


class AudioEffectAsset : public Asset {

	AudioEffectAsset() {}
	~AudioEffectAsset() {}

public:

	static AudioEffectAsset* Create(const AssetName& name, bool recreate = false) { return new AudioEffectAsset; }

};

*/



#endif