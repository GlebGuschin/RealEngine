#pragma once

#ifndef __MODULE_HPP__
#define __MODULE_HPP__

#include "Referenced.hpp"
#include "String.hpp"



class ModuleListener : public Listener {

public:

	virtual void onStart() = 0;
	virtual void onStop() = 0;

};

class Module : public Referenced {

	virtual bool isLoading() const { return false; }

public:

	static Module* LoadModule( const String& ) { return NULL; }

};


class ModuleManager : public Referenced {

public:


};



#endif