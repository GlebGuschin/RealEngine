#pragma once

#ifndef __HVB_HPP__
#define __HVB_HPP__


#include "RenderCommon.hpp"


enum VERTEX_TYPE {
	VERTEX_COMMON = 0,
	VERTEX_PARTICLE,
	VERTEX_STATIC_MESH,
	VERTEX_STATIC_DEPTH_MESH,
	VERTEX_SKINNED_MESH,
	VERTEX_TERRAIN,
	VERTEX_MAX
};


struct CommonVertex {
	Vector position;
	Vector normal;	 
	Vector tangent;
	Vector binornal;
	Color color;
};



struct HardwareVertexBufferInfo {
	VERTEX_TYPE type;
	size_t size;
};

class HardwareVertexBuffer : public Referenced {

	HardwareVertexBufferInfo info;	

public:

	HardwareVertexBuffer(const HardwareVertexBufferInfo& info_) : info(info_) {}
	virtual void update( unsigned startVertex, unsigned count, MemoryBuffer* ) {}
	virtual void update( unsigned startVertex, unsigned count, const void* ptr ) {}

};

size_t GetStride( VERTEX_TYPE type);

#endif