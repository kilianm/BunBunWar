#ifndef GODUNITCONTROL_H
#define GODUNITCONTROL_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../objects/GODObjects.h"

class DLLEXPORT GODUnitControl {
public:
	GODUnitControl();
	~GODUnitControl();

	void addUnit(GODUnitObject* unit);
	GODUnitObject* createUnit(int id, int owner, GODUnitTypeObject* unitType);

	bool hasId(int id);
	int nextId();
	GODUnitObject* getUnit(int location);
	GODUnitObject* getUnitWithId(int id);
	std::vector<GODUnitObject*> getUnits(int owner);
	std::vector<GODUnitObject*> getAliveUnits(int owner);
private: 
	std::vector<GODUnitObject*> units;
	int highestId;
};

#endif