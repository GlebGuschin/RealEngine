// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>


struct GpuTexture {};



struct RenderObject {

	int vb, ib;

	int vs, ps;

};

struct RenderQueue {

	void addRenderObject(RenderObject*);

};


struct RenderPass {

	int colorRt, depthStencilRT;
	int projection;
	int clearColor, clearDepthValue;

	void renderQueue();

};

struct Renderer {




	int createTexture();
	void destroyTexture();

	int createShaderProgram();
	void destroyShaderProgram();

	int createComputeProgram();
	void destroyComputeProgram();


	int createQuery();
	void destroyQuery();

	int createPass();
	void destroyPass();

	int createRenderTarget();
	void destroyRenderTarget();

};


struct RenderContext {

	void beginQuery(int query) {}
	void endQuery(int query) {}

};








int f2(int argc, _TCHAR* argv[])
{
		long l = 0;
		while (malloc(1024 * 1024 * 1024)) {
			l += 1024 * 1024 * 1024;
			printf("Memory %ul \n", l);
		}
	return 0;
}

