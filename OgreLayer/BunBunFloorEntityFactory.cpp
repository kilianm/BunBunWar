#include "BunBunFloorEntityFactory.h"

String BunBunFloorEntityFactory::FACTORY_TYPE_NAME = "BunBunFloorEntity";

const String& BunBunFloorEntityFactory::getType(void) const {
	return FACTORY_TYPE_NAME;
}

MovableObject* BunBunFloorEntityFactory::createInstanceImpl( const String& name,
	const NameValuePairList* params) {
	// must have mesh parameter
	MeshPtr pMesh;
	if (params != 0) {
		NameValuePairList::const_iterator ni = params->find("mesh");
		if (ni != params->end()) {
			// Get mesh (load if required)
			pMesh = MeshManager::getSingleton().load(
				ni->second,
				// autodetect group location
				ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME );
		}
	}
	if (pMesh.isNull()) {
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"'mesh' parameter required when constructing an Entity.",
			"EntityFactory::createInstance");
	}

	return new BunBunFloorEntity(name, pMesh);
}

void BunBunFloorEntityFactory::destroyInstance( MovableObject* obj) {
	delete obj;
}