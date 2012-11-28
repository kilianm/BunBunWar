#include <bunbunwar/OgreGODEngine.h>

OgreUnitType::OgreUnitType(): GODUnitTypeObject() {}
OgreUnitType::~OgreUnitType() {}

void OgreUnitType::setMeshName(std::string meshName) {
	this->meshName = meshName;
}

std::string OgreUnitType::getMeshName() {
	return this->meshName;
}