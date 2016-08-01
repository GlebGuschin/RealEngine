#pragma once 

#ifndef __RENDER_COMMON_HPP__
#define __RENDER_COMMON_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Color.hpp"

#include "Math.hpp"
#include "MemoryBuffer.hpp"


enum { MAX_RENDER_TARGETS = 8 };
enum { MAX_VERTEX_ATTRIBS = 16 };
enum { MAX_MIPMAPS = 12 };
enum { MAX_TEXTURE_SIZE = ( 2 << MAX_MIPMAPS) };
enum { MAX_LAYERS = 6 };
enum { MAX_FACES = 6 };

#define MAX_TEXTURES 4
#define MAX_TEXCOORDS 8

#define MAX_INSTANCES 32

enum COMPARE_FUNC_TYPE {
	COMPARE_FUNC_NEVER,
	COMPARE_FUNC_ALWAYS,
	COMPARE_FUNC_LESS
};



enum PRIMITIVE_TYPE {
	PRIMITIVE_NONE = 0,
	PRIMITIVE_POINTS,
	PRIMITIVE_LINES,
	PRIMITIVE_TRIANGLES,
	PRIMITIVE_TRIANGLE_STRIP,
	PRIMITIVE_PATCH_3,
	PRIMITIVE_PATCH_16
};

inline bool IsTesselation(PRIMITIVE_TYPE type ) { return type == PRIMITIVE_PATCH_3 || type == PRIMITIVE_PATCH_16; }


enum DRAW_TYPE {
	DRAW_NONE =0,
	DRAW_ARRAY, 
	DRAW_INDEXED	
};


struct Rect {
	int x1, y1;
	int x2, y2;
};


struct Viewport {
	int x, y;
	int width, height;
};

struct Msaa {
	uint16 samples;
	Msaa() : samples(1) {}
};


enum CLEAR_TYPE{ CLEAR_COLOR = 1, CLEAR_DEPTH = 2, CLEAR_STENCIL = 4 };

struct ClearInfo {
	Color color;
	ClearInfo( const Color& color_ ) : color( color_ ) {}
};

enum PROJECTION_TYPE { PROJECTION_ORTHO, PROJECTION_PERSPECTIVE };
/*
struct ProjectionInfo {
		PROJECTION_TYPE type;
		float zNear, zFar, fov;
};
*/

struct Projection {

	PROJECTION_TYPE type;

	void setOrtho(uint32 w, uint32 h, float zn, float zf) {
	
		type = PROJECTION_ORTHO;
	}

	void setPerpective(float fov, float zn, float zf) {

		type = PROJECTION_PERSPECTIVE;
	}

};




enum DEPTH_SORT_TYPE { DEPTH_SORT_F2B, DEPTH_SORT_B2F };


struct DepthStencilState {
	COMPARE_FUNC_TYPE depthFunc;
	bool depthTest, depthMask;
	void reset() {
		depthTest = true;
		depthFunc = COMPARE_FUNC_LESS;
		depthMask = true;
	}
	DepthStencilState() { reset(); }


	bool operator==(const DepthStencilState& other) const {
		return depthFunc == other.depthFunc && depthTest == other.depthTest && depthMask == other.depthMask;
	}

};

enum FILL_TYPE { FILL_SOLID, FILL_WIREFRAME };
enum CULL_TYPE { CULL_NONE, CULL_FRONT, CULL_BACK };

struct RasterizerState {
	FILL_TYPE fillType;
	CULL_TYPE cullType;
	//BOOL            FrontCounterClockwise;
	//INT             DepthBias;
	//FLOAT           DepthBiasClamp;
	//FLOAT           SlopeScaledDepthBias;
	//BOOL            DepthClipEnable;
	//BOOL            ScissorEnable;
	//BOOL            MultisampleEnable;
	//BOOL            AntialiasedLineEnable;

	bool scissorEnable;
	bool multisampleEnable;

	void reset() { 
		fillType = FILL_SOLID; 
		cullType = CULL_NONE;
		scissorEnable = multisampleEnable = false;	
	}

	RasterizerState() { reset();  }

	inline bool operator==(const RasterizerState& other) const { 
		return fillType == other.fillType && 
			cullType == other.cullType &&
			scissorEnable == other.scissorEnable && 
			multisampleEnable == other.multisampleEnable;
			;
	}
};


enum BLEND_OP_TYPE { BLEND_OP_ADD, BLEND_OP_SUB, BLEND_OP_REV_SUB, BLEND_OP_MIN, BLEND_OP_MAX };
enum BLEND_FUNC_TYPE { 
	BLEND_FUNC_ZERO = 0, 	
	BLEND_FUNC_ONE = 1,
	BLEND_FUNC_SRC_COLOR = 3,
	BLEND_FUNC_ONE_MINUS_SRC_COLOR = 4,
	BLEND_FUNC_SRC_ALPHA = 5,
	BLEND_FUNC_ONE_MINUS_SRC_ALPHA = 6

	//D3D11_BLEND_DEST_ALPHA = 7,
	//D3D11_BLEND_INV_DEST_ALPHA = 8,
	//D3D11_BLEND_DEST_COLOR = 9,
	//D3D11_BLEND_INV_DEST_COLOR = 10,
	//D3D11_BLEND_SRC_ALPHA_SAT = 11,
};

struct BlendState {

	bool enable;
	void reset() { 
		opType = BLEND_OP_ADD;
		enable = false;
		srcFunc = BLEND_FUNC_ONE; 
		dstFunc = BLEND_FUNC_ONE; 
	}
	BLEND_FUNC_TYPE srcFunc, dstFunc;
	BLEND_OP_TYPE opType;

	BlendState() { reset(); }

	inline bool operator==(const BlendState& other) const {

		return enable == other.enable && 
			opType == other.opType && 
			srcFunc == other.srcFunc &&
			dstFunc == other.dstFunc;

	}

};


class RenderStates {

	BlendState blendState;
	DepthStencilState depthStencilState;
	RasterizerState rasterizerState;

public:

	RenderStates() { reset(); }

	void reset() { 
		blendState.reset(); 
		depthStencilState.reset(); 
	}

	const BlendState& getBlendState() const { return blendState; }
	const DepthStencilState& getDepthStencilState() const { return depthStencilState; }
	const RasterizerState&  getRasterizerState() const { return rasterizerState; }

	
	void setBlending( bool value ) { blendState.enable = value; }
	void setBlendFunc(BLEND_FUNC_TYPE srcFunc_, BLEND_FUNC_TYPE dstFunc_) { blendState.srcFunc = srcFunc_; blendState.dstFunc = dstFunc_; }
	void setBlendOp(BLEND_OP_TYPE opType) { blendState.opType = opType; }
	

	void setDepthFunc(COMPARE_FUNC_TYPE depthFunc) { depthStencilState.depthFunc = depthFunc; }
	void setDepthTest(bool) {}
	void setDepthWrite(bool) {}
	void setDepthBoundTest(bool) {}
	void setDepthBound(float zn, float zf) {}

	void setScissor(bool) {}

	void setCullType(CULL_TYPE cullType) { rasterizerState.cullType = cullType; }
	void setFillType(FILL_TYPE fillType) { rasterizerState.fillType = fillType; }

	inline bool operator==(const RenderStates& other) const {			
		return blendState == other.blendState && depthStencilState == other.depthStencilState;
		return false;	
	}

};



enum TEXTURE_USAGE_TYPE {
	TEXTURE_USAGE_RENDER_TARGET = 1,
	TEXTURE_USAGE_DEPTH_STENCIL = 2,
	TEXTURE_USAGE_TOTAL
};



enum TEXTURE_FILTER_TYPE {
	TEXTURE_FILTER_NONE,
	TEXTURE_FILTER_NEAREST,
	TEXTURE_FILTER_LINEAR,
	TEXTURE_FILTER_TOTAL
};

enum TEXTURE_WRAP_TYPE {
	TEXTURE_WRAP_REPEAT,
	TEXTURE_WRAP_CLAMP,
	TEXTURE_WRAP_TOTAL
};



class RenderSystem;
class RenderContext;
class RenderContextManager;
class Material;
class MaterialManager;
class Mesh;
//class Geometry;
class Shader;
class Font;
class FontManager;
class Canvas;








void RenderLog(const char* formatString...);

enum BLEND_TYPE {
	BLEND_OPAQUE = 0,
	BLEND_MASKED = 1,
	BLEND_TRANSPARENT = 2
};


#endif
