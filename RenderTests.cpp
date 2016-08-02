#include "stdafx.h"

#include "Common.hpp"
#include "World.hpp"

#include "HardwareTexture.hpp"
#include "RenderModule.hpp"
#include "RenderScene.hpp"
#include "Canvas.hpp"
#include "Logger.hpp"
#include "Geometry.hpp"
#include "TextureManager.hpp"

#include "File.hpp"
#include "Mesh.hpp"

#include "RenderSceneObject.hpp"

#include "MeshManager.hpp"
#include "Skeleton.hpp"
#include "ParticleSystemManager.hpp"



Skeleton* CreateTestSkeleton();
void CustomParamTest();


enum RENDER_PROFILE_TYPE {
	RENDER_PROFILE_NONE = 0,
	RENDER_PROFILE_SHADOW = 1,
	RENDER_PROFILE_POSTPROCESS = 3,
	RENDER_PROFILE_MATERIAL = 3
};

struct SurfaceProfile {
	unsigned tesselation : 2;
	unsigned skinning : 3;
	unsigned alphaTest : 1;
};


struct MaterialProfile {
	unsigned shading : 3;
	unsigned diffuseMap : 1;
	unsigned normalMap : 1;
	unsigned detailMap : 1;
	unsigned normalDetailMap : 1;
	unsigned specularMap : 1;
	unsigned emissionMap : 1;	
};


struct QualityProfile {
	unsigned quality : 2;
};

struct PostProcessProfile {
	unsigned msaa : 4;
	unsigned dof : 4;
	unsigned hdr : 4;
	unsigned hdr2 : 4;
};

struct RenderProfile {

	union {
		QualityProfile quality;
	};

	union {
	
		unsigned long long  field;	
		MaterialProfile material;
		SurfaceProfile surface;
		PostProcessProfile postProcess;
	
	};

	bool operator<(const RenderProfile& rhs) const { return field < rhs.field; }

};



extern RenderScene* CreateRenderScene();


#define Cast dynamic_cast


class ShaderDefines {

	LinearMap<String,String> linearMap;

public:

	void clear() { linearMap.clear(); }
	void addDefine(const String& key ) { linearMap.add(key, String("")); }
	void addDefine(const String& key, const String& value ) { linearMap.add(key, value);}
	void addDefine(const String& key, int value ) { 
		String tmp = String::Format("%i", value);
		linearMap.add(key, tmp);
	}


	String getString() {
		String string;		

		for(size_t i = 0; i < linearMap.size(); i++) {
			
			if(i > 0 )string += ";";
			string += linearMap[ i ].key;
			if( linearMap[ i ].value != String::Empty ) {
					string += "=";
					string += linearMap[ i ].value;
			}
			
		}

		return string;
	}


	String getDefines() {

		String string;		

		const String define("#define ");

		for(size_t i = 0; i < linearMap.size(); i++) {
			
			if(i > 0 )string += "\n";
			string += define;
			string += linearMap[ i ].key;
			if( linearMap[ i ].value != String::Empty ) {
					string += " ";
					string += linearMap[ i ].value;
			}
			
		}

		return string;
	}

};

struct CommonVertexShaderParams {

	unsigned instancing:1;	
	unsigned skinning:1;	
	unsigned bones:2;

};

struct CommonFragmentShaderParams {

	/*
	union {
		unsigned field;
	};
	*/
	unsigned diffuseMap:1;
	unsigned specularMap:1;
	unsigned emissionMap:1;
	unsigned detailMap:1;
	unsigned normalMap:1;
	unsigned alphaTest:1;

};

void collectDefines(const CommonVertexShaderParams& shaderParams, ShaderDefines& shaderDefines ) {

	shaderDefines.clear();

	if( shaderParams.skinning ) {	
			shaderDefines.addDefine("USE_SKINNING");
			shaderDefines.addDefine("NUM_BONES", shaderParams.bones + 1);
	}

	if( shaderParams.instancing ) {	
			shaderDefines.addDefine("USE_INSTANSING");
	}	
	
}

void collectDefines(const CommonFragmentShaderParams& shaderParams, ShaderDefines& shaderDefines) {

	shaderDefines.clear();

	if( shaderParams.diffuseMap ) {
			shaderDefines.addDefine("USE_DIFFUSE_MAP");
	}
	if( shaderParams.detailMap ) {
			shaderDefines.addDefine("USE_DETAIL_MAP");
	}	
	if( shaderParams.normalMap ) {
			shaderDefines.addDefine("USE_NORMAL_MAP");
	}
	if( shaderParams.specularMap ) {
			shaderDefines.addDefine("USE_SPECULAR_MAP");
	}	
	if( shaderParams.emissionMap ) {
			shaderDefines.addDefine("USE_EMISSION_MAP");
	}	
	if( shaderParams.alphaTest ) {
			shaderDefines.addDefine("USE_ALPHA_TEST");
	}

}



















#define cast(x) dynamic_cast<x*>

void RenderTest2() {		

	SharedPtr<Geometry> geometry;
	//geometry->getVertexFormat();

	RenderModule* renderModule = NULL;
	MaterialManager* materialManager = NULL;

	MaterialInfo matInfo;
	SharedPtr<Material> material = renderModule->getMaterialManager()->createMaterial(matInfo);
	SharedPtr<Texture> texture = renderModule->getTextureManager()->createTexture("fire.dds");
	//SharedPtr<Mesh> mesh = renderModule->getMeshManager()->createMesh("fire.mesh");

	//material->

	Material* mat = material;

	material->setColor(Color::YELLOW, MATERIAL_COLOR_DIFFUSE);
	material->setColor(Color::RED, MATERIAL_COLOR_SPECULAR );


	dynamic_cast<Material*>(mat);
	//cast<Material>(mat);

	SharedPtr<Canvas> canvas =  NULL;
	
	canvas->drawRectangle(0,0, 100,200, Color::PINK);	
	canvas->drawLine(0, 0, 100, 200, Color::BLUE);


}

typedef std::map<RenderProfile, void*> Map;

SharedPtr<TextureManager> gTextureManager;
SharedPtr<MaterialManager> gMaterialManager;


extern TextureManager* CreateTextureManager();


class Foo111 : public AssetListener {

public:

	void onStartLoading(Asset* asset) {
		int i = 0;
	}

	void onStopLoading(Asset* asset) {
		int i = 0;
	}


};


void RenderParticleTest();

void RenderTest1()
{

	RenderParticleTest();

	/*
	SharedPtr<File> file = CreateFile();
	file->open( String("D:\\test.txt"), FILE_MODE_READ, FILE_TEXT);
	char buffer[1024];
	size_t size = file->read( 5, &buffer[0] );
	file->close();	
	*/

	SharedPtr<Foo111> foo = new Foo111;
	SharedPtr<Asset> asset;


	//asset->addListe
	asset = new TextureAsset("Content/tree_foliage.dds");
	asset->load();
	asset = new TextureAsset("Content/lizard_diff.dds");
	asset->load();
	//asset = new TextureAsset("Content/lizard_norm.dds");
	asset = new TextureAsset("Content/TerrainDiffuseArray.dds");
	asset->load();
	asset = new TextureAsset("Content/TerrainNormalArray.dds");

	//asset = new TextureAsset("Content/Terrain.dds");
	//asset = new TextureAsset("Content/Wood.dds");

	asset->addListener(foo);

	asset->load();

	asset->removeListener(foo);


	AssetName a1("DisciplesIII");
	SharedPtr<Skeleton> skeleton = CreateTestSkeleton();

	unsigned numBones = skeleton->getNumBones();

	TextureInfo info;
	gTextureManager = CreateTextureManager();
	SharedPtr<Texture> texture1 = gTextureManager->createTexture(info);
	SharedPtr<Texture> texture2 = gTextureManager->createTexture(AssetName("textures/fire.dds"));

	MaterialInfo materialInfo;
	SharedPtr<Material> material = GetMaterialManager()->createMaterial(materialInfo);

	material->setTexture(texture1, MATERIAL_TEXTURE_DEFFUSE);


	texture1 = NULL;
	texture2 = NULL;

	

	

	SharedPtr<Geometry> geometry = new Geometry;
	geometry->addItem(GeometryItem(3,0));
	geometry->addItem(GeometryItem(3,3));
	geometry->addItem(GeometryItem(3,6));

	geometry->addItem(GeometryItem(0,6,3,4,5));

	//geometry->set



	


	

	size_t s = sizeof(RenderProfile);
	Map map;
	for (int i = 0; i < 10000000; i++) {
		RenderProfile rf;
		rf.field = rand();
		rf.surface.skinning = 2;
		rf.postProcess.msaa = 4;
		rf.postProcess.dof = 2;
		//map.insert(Map::value_type(rf, NULL));
	}

	printf("Passed...\n");

	SharedPtr<Logger> logger = CreateLogger();
	logger->start("MyLog.log");
	logger->error("Render", "Hello!");	

	ShaderDefines  shaderDefines;
	shaderDefines.addDefine("USE_EMISSION_MAP");
	shaderDefines.addDefine("USE_DIFFUSE_MAP");
	shaderDefines.addDefine("USE_SPECULAR_MAP");
	shaderDefines.addDefine("USE_NORMAL_MAP");
	shaderDefines.addDefine("USE_DETAIL_MAP");
	shaderDefines.addDefine("USE_FOG");
	shaderDefines.addDefine("USE_3DC");
	shaderDefines.addDefine("NUM_SAMPLES",8);
	  
	String string = shaderDefines.getString();
	String defines = shaderDefines.getDefines();

	logger->info("Render", string);
	logger->info("Render", defines);

	logger->stop();




	SharedPtr<MemoryBuffer> mb = CreateMemoryBuffer(0xFFFF0000);
	if( mb ) {
			int* intPtr = (int*)mb->lock();
			intPtr[0] = 0xFFFF;
			intPtr[0] = 0xDEAD;
			mb->unlock();
	}
	mb=NULL;
	
	ResourceName texture3( "textures/particles/fire.dds");
	
	
	SharedPtr<RenderScene> rs = CreateRenderScene();
	SharedPtr<LightRenderSceneObject> sunLight = new LightRenderSceneObject;
	SharedPtr<ParticleSystemRenderSceneObject> particleSystemRenderSceneObject = new ParticleSystemRenderSceneObject;
	SharedPtr<TerrainRenderSceneObject> ts = new TerrainRenderSceneObject;
	SharedPtr<TextRenderSceneObject> textSceneObject = new TextRenderSceneObject;
	SharedPtr<MeshRenderSceneObject> meshSceneObject = new MeshRenderSceneObject;
	
	SharedPtr<LightRenderSceneObject> omniLights1 = new LightRenderSceneObject;
	SharedPtr<LightRenderSceneObject> omniLights2 = new LightRenderSceneObject;
	SharedPtr<LightRenderSceneObject> omniLights3 = new LightRenderSceneObject;


	//rs->
	SharedPtr<ParticleSystemManager> particleSystemManager = CreateParticleSystemManager();
	SharedPtr<ParticleSystem> particleSystem1 = particleSystemManager->createParticleSystem();
	SharedPtr<ParticleSystem> particleSystem2 = particleSystemManager->createParticleSystem();

	particleSystem1->addStream( new ParticleStream );
	particleSystem1->addStream( new ParticleStream );
		
	particleSystemRenderSceneObject->setParticleSystem(particleSystem1);

	particleSystem1 = NULL;
	particleSystem2 = NULL;


	rs->addLight(sunLight);

	LightInfo omniLightInfo;
	omniLightInfo.type = LIGHT_OMNI;
	omniLights1->setInfo(omniLightInfo);
	omniLights2->setInfo(omniLightInfo);
	omniLights3->setInfo(omniLightInfo);

	omniLights1->setColor(Color::RED, LIGHT_COLOR_DIFFUSE);

	rs->addLight(omniLights1);
	rs->addLight(omniLights2);
	rs->addLight(omniLights3);

	DynamicArray<SharedPtr<LightRenderSceneObject>> lights;
	rs->getLights(lights);


	rs->addMesh(meshSceneObject);
	//rs->addSceneObject(ps);
	//rs->addSceneObject(textSceneObject);

	textSceneObject->setText("Hello,world!");

	particleSystemRenderSceneObject->setTransform(Transform());


	rs->removeMesh(meshSceneObject);



	sunLight->setTransform(Transform());
	//light->


	rs->removeLight(omniLights1);
	rs->removeLight(omniLights2);
	rs->removeLight(omniLights3);

	rs->removeLight(sunLight);
	//rs->removeSceneObject(ps);


	 /*
	HardwareTexture* htexture = NULL;

	SharedPtr<TextureSurface> surface[10];
	for(unsigned mipLevel =0; mipLevel < 10; mipLevel++) {
		htexture->update(mipLevel, surface[mipLevel] );		
	}


	SharedPtr<TextureVolume> volume[10];
	for (unsigned mipLevel = 0; mipLevel < 10; mipLevel++) {
		//htexture->update(mipLevel, surface[mipLevel]);
		htexture->update(mipLevel, volume[mipLevel]);
	}
	*/


}

/*
#include "Renderer.hpp"
class BaseRenderer : public Renderer {
};
void foo1() {
}
*/

#include "TextureFile.hpp"


void updateTexture() {

	TextureFile* tf=NULL;

	HardwareTexture* htexture=NULL;

	if( tf->isVolume() ) {	
		for(unsigned mipLevel = 0; mipLevel < tf->getMipLevels(); mipLevel++) {
			htexture->update(mipLevel, tf->getVolume(mipLevel) );
		}
	}

	if( tf->isCube() ) {	
		for(unsigned face = 0; face < 6; face++) {		
			for(unsigned mipLevel = 0; mipLevel < tf->getMipLevels(); mipLevel++) {					 
					htexture->update( (FACE_TYPE)face, mipLevel, tf->getSurface( (FACE_TYPE)face, mipLevel ) );
			}
		}
	}

	if( tf->isArray() ) {	
		for(unsigned layer = 0; layer < tf->getDepth(); layer++) {		
			for(unsigned mipLevel = 0; mipLevel < tf->getMipLevels(); mipLevel++) {					 
					htexture->update( layer, mipLevel, tf->getSurface( layer, mipLevel ) );
			}
		}
	}

}

struct PerSceneConstantBuffer {
	Matrix projectionMatrix;
	Color		fogColor;
	Vector  fogParams;
	Color		ambientColor;
};


struct PerObjectConstantBuffer {
	Matrix4x4 mvp;
	
};

void meshTest() {

	Material* material2 = NULL;
	SharedPtr<Mesh> mesh = NULL;
	/*
	for(unsigned itemIndex=0; itemIndex < mesh->getNumItems(); itemIndex++) {
		mesh->getItem( 0, 0 )->setMaterial(material2);
	}
	*/

	//RenderSceneObject* rso[100];
	RenderSceneObject* rso = NULL;

	Transform transform = rso->getTransform();
	//rso->

	RenderObject ro;

	Material* material = ro.getSurface().getMaterial();
	Geometry* geometry = ro.getSurface().getGeometry();

}

void meshTest2() {

	Material* material2 = NULL;
	SharedPtr<Mesh> mesh = NULL;

	SharedPtr<MeshManager> meshManager = NULL;

	mesh = meshManager->createMesh("meshes/batman.mesh");


	/*
	for (unsigned itemIndex = 0; itemIndex < mesh->getNumItems(); itemIndex++) {
		mesh->getItem(0, 0)->setMaterial(material2);
	}
	*/
			
}



void RenderParticleTest() {

	RenderStates renderStates;




	/*
	SharedPtr<ParticleSystem

	SharedPtr<ParticleSystemAsset> particleSystemAsset = new ParticleSystemAsset;
	particleSystemAsset->addStream(new ParticleStream);
	particleSystemAsset->addStream(new ParticleStream);
	particleSystemAsset->addStream(new ParticleStream);

	for (unsigned i = 0; i < particleSystemAsset->getNumStreams(); i++) {
			ParticleStream* stream = particleSystemAsset->getStream(i);
	}
	*/

	CustomParamTest();

	SharedPtr<ParticleSystemManager> particleSystemManager = CreateParticleSystemManager();
	SharedPtr<ParticleSystem> particleSystem1 = particleSystemManager->createParticleSystem();
	SharedPtr<ParticleSystem> particleSystem2 = particleSystemManager->createParticleSystem();
	SharedPtr<ParticleSystem> particleSystem3 = particleSystemManager->createParticleSystem("particles/fire/ps");


	particleSystem1->addStream(new ParticleStream);
	particleSystem1->addStream(new ParticleStream);

}




enum  CUSTOM_PARAM_TYPE {
	CUSTOM_PARAM_NONE = 0,
	CUSTOM_PARAM_COLOR = 1,
	CUSTOM_PARAM_VEC4 = 2,
	CUSTOM_PARAM_INT = 3,
	CUSTOM_PARAM_FLOAT = 4,
	CUSTOM_PARAM_BOOL = 5,
	CUSTOM_PARAM_MATRIX = 6
};

class CustomParam {

	CUSTOM_PARAM_TYPE type;
	Name name;

	union {

		float float_value;
		int int_value;
		bool bool_value;

	};

	Vector4 vec4_value;
	Color color_value;
	Matrix4x4 matrix_value;

public:

	CustomParam() :type(CUSTOM_PARAM_NONE) {}
	CustomParam(const Name& name_, const Vector4& value) : name(name_), type(CUSTOM_PARAM_VEC4), vec4_value(value){}
	CustomParam(const Name& name_, const Color& value) : name(name_), type(CUSTOM_PARAM_COLOR), color_value(value){}
	CustomParam(const Name& name_, float value) : name(name_), type(CUSTOM_PARAM_FLOAT), float_value(value) {}
	CustomParam(const Name& name_, bool value) : name(name_), type(CUSTOM_PARAM_BOOL), bool_value(value) {}
	CustomParam(const Name& name_, int value) : name(name_), type(CUSTOM_PARAM_INT), int_value(value) {}
	CustomParam(const Name& name_, const Matrix4x4& value) : name(name_), type(CUSTOM_PARAM_MATRIX), matrix_value(value) {}

	CUSTOM_PARAM_TYPE getType() const { return type; }
	const Name& getName() const { return name; }

	bool getValue(Vector4& value) const {
		if (type == CUSTOM_PARAM_VEC4) {
			value = vec4_value;
			return true;
		}
		return false;
	}

	bool getValue(Color& value) const {
		if (type == CUSTOM_PARAM_COLOR) {
			value = color_value;
			return true;
		}
		return false;
	}

};




class CustomParams {
	std::vector<CustomParam> params;
public:

	void addParam(const CustomParam& param) {

		for (size_t i = 0; i < params.size(); i++) {

			if (params[i].getName() == param.getName()) {
				params[i] = param;
				return;
			}
		}
		params.push_back(param);

	}
	unsigned getNumParams() const { return (unsigned)params.size(); }
	const CustomParam& operator[](unsigned index) { return params[index]; }
	void clear() { params.clear(); }

};


void CustomParamTest() {

	CustomParams customParams;
	customParams.addParam(CustomParam("FogColor", Color::BLUE));
	customParams.addParam(CustomParam("AmbientColor", Color::RED));
	customParams.addParam(CustomParam("CropMatrix", Matrix()));
	customParams.addParam(CustomParam("UseTexture", true));
	customParams.addParam(CustomParam("FogDistance", 100.0f));
	customParams.addParam(CustomParam("NumLights", 16));

	int i = 0;
}


