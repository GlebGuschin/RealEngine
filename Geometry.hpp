#pragma once

#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include "RenderCommon.hpp"
#include "HardwareVertexBuffer.hpp"
#include "HardwareIndexBuffer.hpp"

#include "Animation.hpp"


struct VertexBufferInfo {
	VERTEX_TYPE type;
	unsigned offset, size;
};

class VertexBuffer : public Referenced {

	VertexBufferInfo info;	
	SharedPtr<HardwareVertexBuffer> hardwareVertexBuffer;

public:

	VertexBuffer(const VertexBufferInfo& info_, HardwareVertexBuffer* hardwareVertexBuffer_) : info(info_), hardwareVertexBuffer(hardwareVertexBuffer_) {}

	virtual void write(unsigned start, unsigned count, MemoryBuffer*) {}
	virtual void read(unsigned start, unsigned count, MemoryBuffer*) {}

};

struct IndexBufferInfo {
	INDEX_TYPE type;
	unsigned offset, size;
};

class IndexBuffer : public Referenced {
	IndexBufferInfo info;	
	SharedPtr<HardwareIndexBuffer> hardwareIndexBuffer;
public:
	IndexBuffer(const IndexBufferInfo& info_, HardwareIndexBuffer* hardwareIndexBuffer_) : info(info_), hardwareIndexBuffer(hardwareIndexBuffer_) {}
};



//typedef unsigned VertexFormat;
//struct VertexFormatInfo {int i;};
//class  VertexFormat : public Referenced {};

enum GEOMETRY_ITEM_TYPE  { 
	GEOMETRY_ITEM_NONE = 0,
	GEOMETRY_ITEM_ARRAY, 
	GEOMETRY_ITEM_INDEX 
};

struct GeometryItem {

	GEOMETRY_ITEM_TYPE type;
	unsigned baseVertex, vertexCount;
	int startIndex;
	unsigned	minIndex, numVertices, primitiveCount;

	GeometryItem() : 
		type(GEOMETRY_ITEM_NONE), baseVertex(0), vertexCount(0), startIndex(0), minIndex(0), numVertices(0), primitiveCount(0) {}

	GeometryItem(unsigned startVertex_, unsigned vertexCount_) :
		type(GEOMETRY_ITEM_ARRAY), baseVertex(startVertex_), vertexCount(vertexCount_) {}

	GeometryItem(int baseIndex_, unsigned minIndex, unsigned numVertices_, unsigned startIndex, unsigned primitiveCount) :
		type(GEOMETRY_ITEM_INDEX) {}

};


class Primitive {

};




#define MAX_GEOMETRY_ITEM 16 

class Geometry : public Referenced {

	PRIMITIVE_TYPE primitiveType;
	SharedPtr<VertexBuffer> vertexBuffer;
	SharedPtr<IndexBuffer> indexBuffer;

	//DynamicArray<GeometryItem> items;
	unsigned size;
	GeometryItem items[MAX_GEOMETRY_ITEM];


	bool homo;

	SharedPtr<MatrixPalette> animationPalette;

public:

	 Geometry() : size(0), primitiveType(PRIMITIVE_NONE), homo(true) {}
	 Geometry(PRIMITIVE_TYPE primitiveType_) : size(0), primitiveType(primitiveType_), homo(true) {}
	 //Geometry(PRIMITIVE_TYPE primitiveType_, VertexBuffer* vertexBuffer_, IndexBuffer* indexBuffer_ ) : size(0), primitiveType(primitiveType_), homo(true) {}
	 Geometry(PRIMITIVE_TYPE primitiveType_, VertexBuffer* vertexBuffer_, IndexBuffer* indexBuffer_ = NULL) : 
			size(0), primitiveType(primitiveType_), homo(true), vertexBuffer(vertexBuffer_), indexBuffer(indexBuffer_) {}


	 VertexBuffer* getVertexBuffer() const { return vertexBuffer; }
	 IndexBuffer* getIndexBuffer() const { return indexBuffer; }

	 VERTEX_TYPE getVertexType() const { return VERTEX_COMMON; }
	 PRIMITIVE_TYPE getPrimitiveType() const { return primitiveType; }


	 MatrixPalette* getAnimationPalette() const  { return NULL; }
	 bool isSkinned() const { return false; }
	 bool isTesselated() const { return false; }
	 bool canInstanced() const { return false; }
	 bool isHomo() const { return homo; }

	 unsigned getNumItems() const { return size; }
	 void clearItems() { size = 0; }
	 void addItem(const GeometryItem& item) { 
		 assert(size < MAX_GEOMETRY_ITEM);
		 for (unsigned i = 0; i < size; i++) {
			 if (items[i].type != item.type) {
				 homo = false; break;
			 }
		 }
		 items[size++] = item;
	 }

	 const GeometryItem& getItem(unsigned index) const {
		 assert(size < MAX_GEOMETRY_ITEM);
		 return items[index];
	 }

};

Geometry* CreateGeometry();

#endif