#include "stdafx.h"
#include "Asset.hpp"
#include "Logger.hpp"
#include "MemoryBuffer.hpp"


Asset::MapType Asset::Map;

void Asset::Remove(Asset* asset) {

	for (MapType::iterator it = Map.begin(); it != Map.end(); it++)  {

		if (it->second == asset) {
			Map.erase(it);
			//delete asset;				
			return;
		}
	}

	//assert(0);		
}

void Asset::Remove(const AssetName& name) {

	MapType::iterator it = Map.find(name);
	if (it == Map.end()) {
		assert(0);
	}

	Map.erase(it);

}

void Asset::Add(Asset* asset) {

	//assert(!Find(name));
	//Logger::Notify("Resource", "Asset added");
	//Map.insert(MapType::value_type(name, asset));

}

Asset* Asset::Find(const AssetName& name) {

		Asset* asset = NULL;
		MapType::iterator it = Map.find(name);
		if (it != Map.end()) return it->second;
		return asset;

}

/*
MemoryBuffer* Asset::Load(const AssetName& name) {
	
	HANDLE hFile;

	hFile = CreateFileW(name.getString().w_str(),
	GENERIC_READ,
	NULL,
	NULL,
	OPEN_EXISTING,
	NULL,
	NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) {	
		assert(0);
	}

	DWORD fileSize = GetFileSize(hFile, NULL);

	MemoryBuffer *buffer = MemoryBuffer::Create(fileSize);
	void *data = (void*)buffer->lock();

	DWORD length;

	ReadFile(hFile,
	(LPVOID)data,
	fileSize,
	&length,
	NULL);

	buffer->unlock();

	if (length != fileSize) {
		assert(0);
	}

	CloseHandle(hFile);

	return(buffer);
	
	return NULL;

}
*/

/*
MemoryBuffer* MemoryBuffer::CreateFromFile(const wchar_t *fileName) {


	HANDLE hFile;

	hFile = CreateFileW(fileName,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
		);

	if (hFile == INVALID_HANDLE_VALUE) {
		//throw( "cant open file " );
		assert(0);
	}

	DWORD fileSize = GetFileSize(hFile, NULL);

	MemoryBuffer *buffer = new  MemoryBuffer(fileSize);
	void *data = (void*)buffer->lock();

	DWORD length;

	ReadFile(hFile,
		(LPVOID)data,
		fileSize,
		&length,
		NULL);

	buffer->unlock();

	if (length != fileSize) {
		assert(0);
	}

	CloseHandle(hFile);

*/

MemoryBuffer* Asset::loadFromFile(size_t size, size_t offset) {

	MemoryBuffer* buffer = NULL;

	HANDLE hFile;

	hFile = CreateFileW(name.getName().w_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		assert(0);
	}

	DWORD fileSize = GetFileSize(hFile, NULL);

	assert(offset+size < fileSize);
	DWORD bytesToRead = (DWORD)size ? (DWORD)size : fileSize;
	//SetFilePointer();

	buffer = CreateMemoryBuffer(fileSize);
	assert(buffer);
	void *data = (void*)buffer->lock();

	DWORD length;

	ReadFile(hFile, (LPVOID)data, fileSize, &length, NULL);

	buffer->unlock();

	if (length != fileSize) {
		assert(0);
	}

	CloseHandle(hFile);

	//printf();

	return buffer;

}
 
 //ASSET_STATE_UNLOADING = 3

void Asset::load() {

	setState(ASSET_STATE_LOADING);
	for(size_t i=0; i < listeners.size(); i++ ) { 	
		 listeners[i]->onStartLoading(this);
	}

	buffer = loadFromFile();

	setState(ASSET_STATE_FULL);
	for(size_t i=0; i < listeners.size(); i++ ) { 	
		 listeners[i]->onStopLoading(this);
	}

}

void  Asset::unload() {
	
	setState(ASSET_STATE_UNLOADING);
	for(size_t i=0; i < listeners.size(); i++ ) { 	
		 listeners[i]->onStartUnLoading(this);
	}

	setState(ASSET_STATE_EMPTY);
	for(size_t i=0; i < listeners.size(); i++ ) { 	
		 listeners[i]->onStopUnLoading(this);
	}


}

void  Asset::reload() {

}



/*

	orderedCollection := OrderedCollection new: 10.

	1 to: 10 do: [ :each | Transcript show: each printString ].

	object at: #name put: 'Peterson'.
	object at: #key put: 'Mason'.

	void foo1( Integer a, CardMaster card) {
	
	}



*/
