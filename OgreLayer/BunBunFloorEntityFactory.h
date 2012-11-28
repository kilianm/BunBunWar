#ifndef BUNBUNFLOORENTITYFACTORY_H
#define BUNBUNFLOORENTITYFACTORY_H

#include <ogre/Ogre.h>
#include "BunBunFloorEntity.h"

using namespace Ogre;

class BunBunFloorEntityFactory : public MovableObjectFactory {
protected:
	MovableObject* createInstanceImpl( const String& name, const NameValuePairList* params);
public:
	BunBunFloorEntityFactory() {}
	~BunBunFloorEntityFactory() {}

	static String FACTORY_TYPE_NAME;

	const String& getType(void) const;
	void destroyInstance( MovableObject* obj);
};

#endif