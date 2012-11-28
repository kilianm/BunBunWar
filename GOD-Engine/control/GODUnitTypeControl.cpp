#include "GODControl.h"

GODUnitTypeControl::GODUnitTypeControl() {}

GODUnitTypeControl::~GODUnitTypeControl() {
	while ((signed)unitTypes.size() > 0) {
		GODUnitTypeObject* unitType = *(unitTypes.begin());
		unitTypes.erase(unitTypes.begin());
		delete unitType;
	}
}

std::string GODUnitTypeControl::XML_OBJECT_NAME = "unitTypes";

std::string GODUnitTypeControl::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODUnitTypeControl::parseXMLObject(GODXMLObject* object) {
	GODUnitTypeControl* unitTypeControl = new GODUnitTypeControl();
	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		GODUnitTypeObject* parsed = (GODUnitTypeObject*)GODXMLMapping::getInstance()->getXMLMapping(child->getName())->parseXMLObject(child);
		unitTypeControl->addUnitType(parsed);
	}
	return unitTypeControl;
}

void GODUnitTypeControl::addUnitType(GODUnitTypeObject* unitType) {
	unitTypes.push_back(unitType);
}

void GODUnitTypeControl::loadUnitTypes(GODScriptObject* script) {

}

GODUnitTypeObject* GODUnitTypeControl::getUnitType(int location) {
	if (location >= 0 && location < (signed)unitTypes.size()) {
		throw new GODException("ArrayIndexOutOfBoundsGODException","GODUnitTypeControl::getUnitType(int))");
	}
	return unitTypes.at(location);
}

GODUnitTypeObject* GODUnitTypeControl::getUnitTypeWithId(int id) {
	for (int i=0; i<(signed)GODUnitTypeControl::unitTypes.size(); i++) {
		GODUnitTypeObject* unitType = GODUnitTypeControl::unitTypes.at(i);
		if (unitType->getId() == id && unitType->getUpgrade() == 0) {
			return unitType;
		}
	}
	return NULL;
}

GODUnitTypeObject* GODUnitTypeControl::getUnitTypeWithIdAndUpgrade(int id, int upgrade) {
	for (int i=0; i<(signed)GODUnitTypeControl::unitTypes.size(); i++) {
		GODUnitTypeObject* unitType = GODUnitTypeControl::unitTypes.at(i);
		if (unitType->getId() == id && unitType->getUpgrade() == upgrade) {
			return unitType;
		}
	}
	return NULL;
}

GODUnitTypeObject* GODUnitTypeControl::getUnitTypeWithIdAndNextUpgrade(int id, int upgrade) {
	for (int i=0; i<(signed)GODUnitTypeControl::unitTypes.size(); i++) {
		GODUnitTypeObject* unitType = GODUnitTypeControl::unitTypes.at(i);
		if (unitType->getId() == id && unitType->getUpgrade() == upgrade+1) {
			return unitType;
		}
	}
	return NULL;
}

bool GODUnitTypeControl::hasId(int id) {
	for (int i=0; i<(signed)GODUnitTypeControl::unitTypes.size(); i++) {
		GODUnitTypeObject* unitType = GODUnitTypeControl::unitTypes.at(i);
		if (unitType->getId() == id) {
			return true;
		}
	}
	return false;
}
