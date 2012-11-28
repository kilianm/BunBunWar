#include "GODControl.h"

GODUnitControl::GODUnitControl() {
	highestId = 0;
}

GODUnitControl::~GODUnitControl() {
	highestId = 0;
	while ((signed)units.size() > 0) {
		GODUnitObject* unit = *(units.begin());
		units.erase(units.begin());
		delete unit;
	}
}

void GODUnitControl::addUnit(GODUnitObject* unit) {
	units.push_back(unit);
	if (unit->getId() >= highestId) {
		highestId = unit->getId()+1;
	}
}

GODUnitObject* GODUnitControl::createUnit(int id, int owner, GODUnitTypeObject* unitType) {
	if (hasId(id)) {
		throw new GODException("IDAlreadyExistGODException", "GODUnitControl::createUnit(int, int, GODUnitTypeObject*)");
	}
	GODUnitObject* unit = new GODUnitObject(id, owner, unitType);
	units.push_back(unit);
	return unit;
}

GODUnitObject* GODUnitControl::getUnit(int location) {
	if (location >= 0 && location < (signed)units.size()) {
		throw new GODException("ArrayIndexOutOfBoundsGODException","GODUnitControl::getUnit(int))");
	}
	return units.at(location);
}

GODUnitObject* GODUnitControl::getUnitWithId(int id) {
	for (int i=0; i<(signed)GODUnitControl::units.size(); i++) {
		GODUnitObject* unit = GODUnitControl::units.at(i);
		if (unit->getId() == id) {
			return unit;
		}
	}
	return NULL;
}

bool GODUnitControl::hasId(int id) {
	for (int i=0; i<(signed)GODUnitControl::units.size(); i++) {
		GODUnitObject* unit = GODUnitControl::units.at(i);
		if (unit->getId() == id) {
			return true;
		}
	}
	return false;
}

int GODUnitControl::nextId() {
	highestId += 1;
	return highestId;
}

std::vector<GODUnitObject*> GODUnitControl::getUnits(int owner) {
	std::vector<GODUnitObject*> units;
	for (int i=0; i<(signed)GODUnitControl::units.size(); i++) {
		GODUnitObject* unit = GODUnitControl::units.at(i);
		if (unit->getOwner() == owner) {
			units.push_back(unit);
		}
	}
	return units;
}

std::vector<GODUnitObject*> GODUnitControl::getAliveUnits(int owner) {
	std::vector<GODUnitObject*> units;
	for (int i=0; i<(signed)GODUnitControl::units.size(); i++) {
		GODUnitObject* unit = GODUnitControl::units.at(i);
		if (unit->getOwner() == owner && !unit->isDead()) {
			units.push_back(unit);
		}
	}
	return units;
}
