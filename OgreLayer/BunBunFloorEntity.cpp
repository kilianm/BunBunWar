#include "BunBunFloorEntity.h"

BunBunFloorEntity::BunBunFloorEntity(const String& name, MeshPtr& mesh) : Ogre::Entity(name, mesh) {
	grid = NULL;
}

BunBunFloorEntity::~BunBunFloorEntity() {
	if (this->grid)
		delete this->grid;
}

void BunBunFloorEntity::setGridLocation(Utilities_GridLocation* grid) {
	this->grid = grid;
}

Utilities_GridLocation* BunBunFloorEntity::getGridLocation() {
	return this->grid;
}
