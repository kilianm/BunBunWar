#include "GODTempUnitObject.h"

GODTempUnitObject::GODTempUnitObject(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* pathObject, Utilities_Size* size) {
	this->id = id;
	this->owner = owner;
	this->unitType = unitType;
	this->pathObject = pathObject;
	this->size = size;
}

GODTempUnitObject::~GODTempUnitObject() {
	id = 0;
	owner = 0;
	unitType = NULL;
	pathObject = NULL;
	size = NULL;
}

int GODTempUnitObject::getId() {
	return this->id;
}

int GODTempUnitObject::getObjectType() {
	return GODObject::OBJECTTYPE_GODUnitTempObject;
}

int GODTempUnitObject::getOwner() {
	return this->owner;
}

GODUnitTypeObject* GODTempUnitObject::getUnitType() {
	return this->unitType;
}

GODPathObject* GODTempUnitObject::getPathObject() {
	return this->pathObject;
}

Utilities_Size* GODTempUnitObject::getSize() {
	return this->size;
}