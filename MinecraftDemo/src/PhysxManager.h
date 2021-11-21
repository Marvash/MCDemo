#pragma once

#include "coreInclude.h"
#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}


using namespace physx;

class PhysxManager
{
public:
	static PhysxManager* instance();
	void initPhysics();
	bool advancePhysics(PxReal dt);
	void cleanupPhysics();
	PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
	PxRigidStatic* createStatic(const PxTransform& t, const PxGeometry& geometry);

private:
	PhysxManager();
	static PhysxManager* singleton;

	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;

	PxFoundation* gFoundation = nullptr;
	PxPhysics* gPhysics = nullptr;

	PxDefaultCpuDispatcher* gDispatcher = nullptr;
	PxScene* gScene = nullptr;

	PxMaterial* gMaterial = nullptr;

	PxReal stackZ = 10.0f;

	PxReal mAccumulator = 0.0f;

	PxReal mStepSize = 1.0f / 120.0f;

	static PxFilterFlags ccdFilterShader(
		PxFilterObjectAttributes attributes0,
		PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,
		PxFilterData filterData1,
		PxPairFlags& pairFlags,
		const void* constantBlock,
		PxU32 constantBlockSize);
};

