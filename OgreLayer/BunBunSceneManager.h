#ifndef BUNBUNSCENEMANAGER_H
#define BUNBUNSCENEMANAGER_H

#include <ogre/Ogre.h>
#include "BunBunFloorEntityFactory.h"

using namespace Ogre;

class BunBunSceneManager : public SceneManager {
public:
	BunBunFloorEntity* createBunBunFloorEntity(const String& entityName, const String& meshName );
};

#endif