#pragma once

#ifndef __MODULE_HPP__
#define __MODULE_HPP__

#include "Referenced.hpp"
#include "String.hpp"

class ModuleManager;

class ModuleListener : public Listener {

public:

	virtual void onStart() = 0;
	virtual void onStop() = 0;

};

class Module : public Referenced {

	virtual bool isLoading() const { return false; }

public:
	
};

/*
class ModuleManager : public Referenced {
public:
	Module* loadModule(const String&) { return NULL; }
	void unloadModule(Module*) {  }
};
*/

ModuleManager* CreateModuleManager();

#endif