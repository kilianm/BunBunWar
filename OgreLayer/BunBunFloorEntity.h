#ifndef BUNBUNFLOORENTITY_H
#define BUNBUNFLOORENTITY_H

#include <ogre/Ogre.h>
#include <bunbunwar/Utilities.h>

using namespace Ogre; 

class BunBunFloorEntity : public Entity {
public:
	BunBunFloorEntity(const String& name, MeshPtr& mesh);
	virtual ~BunBunFloorEntity();
	void setGridLocation(Utilities_GridLocation* grid);
	Utilities_GridLocation* getGridLocation();
private:
	Utilities_GridLocation* grid;
};

#endif