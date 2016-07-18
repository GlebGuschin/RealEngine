#pragma once

#ifndef __TERRAIN_RENDER_SCENE_OBJECT_HPP__
#define __TERRAIN_RENDER_SCENE_OBJECT_HPP__

#include "RenderSceneObject.hpp"


class TerrainSector : public Referenced {



};


class Terrain : public Referenced {

	unsigned width, height;

public:

	TerrainSector* getSector(unsigned width, unsigned height) const { return NULL;  }

};



class TerrainRenderSceneObject : public RenderSceneObject {

	SharedPtr<Terrain> terrain;

public:

	TerrainRenderSceneObject()  { }

	void setTerrain(Terrain* terrain_) {}

};




#endif