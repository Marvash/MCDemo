#include "PhysxManager.h"

PhysxManager* PhysxManager::singleton;

PhysxManager::PhysxManager() {

}

PxFilterFlags PhysxManager::ccdFilterShader(
	PxFilterObjectAttributes attributes0,
	PxFilterData filterData0,
	PxFilterObjectAttributes attributes1,
	PxFilterData filterData1,
	PxPairFlags& pairFlags,
	const void* constantBlock,
	PxU32 constantBlockSize)
{
	pairFlags = PxPairFlag::eSOLVE_CONTACT;
	pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;
	pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;
	return PxFilterFlags();
}

void PhysxManager::initPhysics() {
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = ccdFilterShader;
	sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
	//sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.3f);
}

void PhysxManager::cleanupPhysics() {
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	PX_RELEASE(gFoundation);

	std::cout << "Physx cleanup complete" << std::endl;
}

bool PhysxManager::advancePhysics(PxReal dt) {
	mAccumulator += dt;
	if (mAccumulator < mStepSize)
		return false;

	mAccumulator -= mStepSize;

	gScene->simulate(mStepSize);
	gScene->fetchResults(true);
	return true;
}

PxRigidDynamic* PhysxManager::createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity)
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
	dynamic->setAngularDamping(0.05f);
	dynamic->setLinearVelocity(velocity);
	PxRigidBodyExt::setMassAndUpdateInertia(*dynamic, PxReal(1.0f));
	gScene->addActor(*dynamic);
	return dynamic;
}

PxRigidStatic* PhysxManager::createStatic(const PxTransform& t, const PxGeometry& geometry)
{
	PxRigidStatic* staticObj = PxCreateStatic(*gPhysics, t, geometry, *gMaterial);
	gScene->addActor(*staticObj);
	return staticObj;
}

PhysxManager* PhysxManager::instance() {
	if (singleton == nullptr) {
		singleton = new PhysxManager();
	}
	return singleton;
}