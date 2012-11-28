#include "GODObjects.h"

GODLandscapeObject::GODLandscapeObject(Utilities_GridLocation* location) {
	GODLandscapeObject::location = location;
	GODLandscapeObject::gridKind = LANDSCAPE_EMPTY;
	GODLandscapeObject::punishment = 0;
	GODLandscapeObject::item = NULL;
	GODLandscapeObject::locked = false;
}

GODLandscapeObject::GODLandscapeObject(Utilities_GridLocation* location, GODItemObject* item) {
	GODLandscapeObject::location = location;
	GODLandscapeObject::gridKind = LANDSCAPE_BLOCKED;
	GODLandscapeObject::punishment = 0;
	GODLandscapeObject::item = item;
	GODLandscapeObject::locked = false;
}

GODLandscapeObject::~GODLandscapeObject() {
	delete GODLandscapeObject::location;
	this->punishment = 0;
	this->item = NULL;
	this->gridKind = LANDSCAPE_EMPTY;
	this->locked = false;
	this->unitRange.clear();
}

Utilities_GridLocation* GODLandscapeObject::getLocation() {
	return GODLandscapeObject::location;
}

void GODLandscapeObject::setLocation(Utilities_GridLocation* location) {
	GODLandscapeObject::location = location;
}

int GODLandscapeObject::getGridKind() {
	return GODLandscapeObject::gridKind;
}

void GODLandscapeObject::setGridKind(int gridKind) {
	GODLandscapeObject::gridKind = gridKind;
}

GODItemObject* GODLandscapeObject::getItem() {
	return GODLandscapeObject::item;
}

void GODLandscapeObject::setItem(GODItemObject* item) {
	GODLandscapeObject::item = item;
}

bool GODLandscapeObject::isLocked() {
	return locked;
}

void GODLandscapeObject::setLocked(bool locked) {
	GODLandscapeObject::locked = locked;
}

void GODLandscapeObject::addUnitRange(GODUnitObject* unit) {
	for (int i=0; i<(signed)unitRange.size(); i++) {
		GODUnitObject* iterUnit = unitRange.at(i);
		if (iterUnit->getId() == unit->getId()) {
			return;
		}
	}
	unitRange.push_back(unit);
}

void GODLandscapeObject::removeUnitRange(GODUnitObject* unit) {
	std::vector<GODUnitObject*>::iterator iter;
	for (iter=unitRange.begin(); iter!=unitRange.end(); iter++) {
		GODUnitObject* iterUnit = (GODUnitObject*)*iter;
		if (iterUnit->getId() == unit->getId()) {
			unitRange.erase(iter, iter+1);
			return;
		}
	}
}

std::vector<GODUnitObject*> GODLandscapeObject::getUnitRange() {
	return unitRange;
}

void GODLandscapeObject::increasePunishment() {
	punishment++;
}

void GODLandscapeObject::decreasePunishment() {
	if (punishment > 0) {
		punishment--;
	}
}

int GODLandscapeObject::getPunishment() {
	return punishment;
}
