#pragma once

#ifndef __MESH_MANAGER_HPP__
#define __MESH_MANAGER_HPP__

#include "Mesh.hpp"


class MeshManager : public Referenced {

public:

	virtual Mesh* createMesh(const AssetName&) = 0;
	//virtual Mesh* createMesh(const TextureInfo&) = 0;

};



#endif