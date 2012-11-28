#include "BunBunSceneManager.h"

BunBunFloorEntity* BunBunSceneManager::createBunBunFloorEntity(
                                   const String& entityName,
                                   const String& meshName ) {
	NameValuePairList params;
	params["mesh"] = meshName;
	return static_cast<BunBunFloorEntity*>(
		createMovableObject(entityName, BunBunFloorEntityFactory::FACTORY_TYPE_NAME, 
			&params));
}