#include "stdafx.h"
#include "RenderUtils.hpp"


/*
#include "Common.hpp"
#include "World.hpp"

#include "HardwareTexture.hpp"
#include "RenderModule.hpp"
#include "RenderScene.hpp"
#include "Canvas.hpp"
#include "Logger.hpp"
#include "Geometry.hpp"


extern RenderScene* CreateRenderScene();
extern MemoryBuffer* CreateMemoryBuffer(size_t size, unsigned flags);

#define Cast dynamic_cast

void test() {	

	SharedPtr<Geometry> geometry;
	geometry->getVertexFormat();

	MaterialManager* materialManager = NULL;

	SharedPtr<Material> material = materialManager->create();
	//material->

	Material* mat = material;

	//dynamic_cast<Material>(mat);

	SharedPtr<Canvas> canvas =  NULL;
	
	canvas->drawRectangle(0,0, 100,200, Color::PINK);	


}

void RenderTest1()
{

	SharedPtr<MemoryBuffer> mb = CreateMemoryBuffer(1024,0);
	int* intPtr = (int*)mb->lock();
	intPtr[ 0 ] = 0xFFFF;
	intPtr[ 2 ] = 0xDEAD;
	mb->unlock();
	mb=NULL;
	
	ResourceName texture1( "textures/particles/fire.dds");
	
	SharedPtr<Logger> logger = CreateLogger();
	logger->start("MyLoh.txt");
	logger->error("Render", "Hello!");
	logger->stop();


	SharedPtr<RenderScene> rs = CreateRenderScene();
	SharedPtr<LightRenderSceneObject> light = new LightRenderSceneObject;
	SharedPtr<ParticleSystemRenderSceneObject> ps = new ParticleSystemRenderSceneObject;
	
	rs->addSceneObject(light);
	rs->addSceneObject(ps);

	ps->setTransform(Transform());
	light->setTransform(Transform());

	

	rs->removeSceneObject(light);
	rs->removeSceneObject(ps);

}
*/



/*
enum TEXEL_FORMAT {

	TEXEL_NONE = 0,
	TEXEL_RGBA8 = 1,
	TEXEL_RGB8 = 2,

	TEXEL_DXT1 = 10,
	TEXEL_DXT3 = 13,
	TEXEL_DXT5 = 15,

	TEXEL_D24S8 = 103,

};
*/

size_t GetTextureSurfaceSize(TEXEL_FORMAT type, unsigned width, unsigned height) {

	switch(type) {

		case TEXEL_RGBA8: 
			return 4 * width * height; 
			break;

		case TEXEL_RGB8: 
			return 3* width * height; 
			break;
		
		case TEXEL_DXT1: 
			return width / 4 * height / 4 * 8;

		case TEXEL_DXT5:
			return width / 4 * height / 4 * 16;

		case TEXEL_RGBA16F:
			return 4 * 2 * width * height;
			break;

		case TEXEL_RGBA32F:
			return 4 * 4 * width * height;
			break;

		
	};

	return 0;

}

/*
enum VERTEX_TYPE {
	VERTEX_COMMON = 0,
	VERTEX_PARTICLE = 1,
	VERTEX_STATIC_MESH,
	VERTEX_SKINNED_MESH
};
*/


size_t GetStride( VERTEX_TYPE type) {

	const static size_t array[VERTEX_MAX] = { 32, 16, 16, 16 };
	return array[ type ];

}



Skeleton* CreateTestSkeleton() {

	Skeleton* skeleton = new Skeleton;
	SharedPtr<Bone> bone = new Bone("Pelvis");
	skeleton->addBone(bone);
	skeleton->addBone(new Bone("Spine"), bone);

	skeleton->addBone(new Bone("LeftShoulder"), skeleton->findBone("Spine"));
	skeleton->addBone(new Bone("RightShoulder"), skeleton->findBone("Spine"));

	skeleton->addBone(new Bone("LeftArm"), skeleton->findBone("LeftShoulder"));
	skeleton->addBone(new Bone("RightArm"), skeleton->findBone("RightShoulder"));

	skeleton->addBone(new Bone("LeftHand"), skeleton->findBone("LeftArm"));
	skeleton->addBone(new Bone("RightHand"), skeleton->findBone("RightArm"));

	skeleton->addBone(new Bone("LeftLeg"), skeleton->findBone("Spine"));
	skeleton->addBone(new Bone("RightLeg"), skeleton->findBone("Spine"));

	skeleton->addBone(new Bone("LeftFoot"), skeleton->findBone("LeftLeg"));
	skeleton->addBone(new Bone("RightFoot"), skeleton->findBone("RightLeg"));

	skeleton->addBone(new Bone("Neck"), skeleton->findBone("Spine"));
	skeleton->addBone(new Bone("Head"), skeleton->findBone("Neck"));

	bone = skeleton->findBone("RightArm");
	skeleton->dump();

	unsigned boneIndex1 = skeleton->findBoneIndex("Root");
	unsigned boneIndex2 = skeleton->findBoneIndex("Spine");
	unsigned boneIndex3 = skeleton->findBoneIndex("LeftArm");
	unsigned boneIndex4 = skeleton->findBoneIndex("RightArm");
	unsigned boneIndex5 = skeleton->findBoneIndex("Pelvis");
	unsigned boneIndex6 = skeleton->findBoneIndex("Head");

	//skeleton = NULL;
	const static Name name1("RightArm");
	const static Name name2("RightArm");
	const static Name name3("RightArm");
	const static Name name4("RightArm");
	const static Name name5("RightArm");

	return skeleton;

}


const Name&  GetName(MATERIAL_TEXTURE_TYPE type) {

	const static Name array[MATERIAL_TEXTURE_MAX] = { "DiffuseMap", "NormalMap", "SpecularMap", "EmissionMap", "DetailMap", "NormalDetailMap", "EnvMap" };

	return array[type];

	/*
	switch (type) {

		//case MATERIAL_TEXTURE_DEFAULT:
		case MATERIAL_TEXTURE_DEFFUSE:
			return Name("DiffuseMap");
			break;

		case MATERIAL_TEXTURE_NORMAL:
			return Name("NormalMap");
			break;

			
			MATERIAL_TEXTURE_SPECULAR,
			MATERIAL_TEXTURE_EMISSION,
			MATERIAL_TEXTURE_DETAIL,
			MATERIAL_TEXTURE_NORMAL_DETAIL,
			MATERIAL_TEXTURE_ENV,
			MATERIAL_TEXTURE_MAX
		
	};

	return Name("DiffuseMap");
	*/

};


