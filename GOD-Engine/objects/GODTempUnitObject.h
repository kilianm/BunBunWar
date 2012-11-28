#ifndef GODTEMPUNITOBJECT_H
#define GODTEMPUNITOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "GODObjects.h"

class DLLEXPORT GODTempUnitObject : public GODObject {
public:
	GODTempUnitObject(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* pathObject, Utilities_Size* size);
	~GODTempUnitObject();

	int getId();
	int getObjectType();
	int getOwner();
	GODUnitTypeObject* getUnitType();
	GODPathObject* getPathObject();
	Utilities_Size* getSize();
private:
	int id;
	int owner;
	GODUnitTypeObject* unitType;
	GODPathObject* pathObject;
	Utilities_Size* size;
};

#endif