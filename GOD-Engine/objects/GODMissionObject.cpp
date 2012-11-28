#include "GODMissionObject.h"

GODMissionObject::GODMissionObject() {
	unitControl = NULL;
	landscapeControl = NULL;
	unitTypeControl = NULL;
	name = "";
	currentMoney = 0;
	totalMoney = 0;
	lives = 0;
}

GODMissionObject::~GODMissionObject() {
	if (unitControl) {
		delete unitControl;
		unitControl = NULL;
	}
	if (landscapeControl) {
		delete landscapeControl;
		landscapeControl = NULL;
	}
	if (unitTypeControl) {
		delete unitTypeControl;
		unitTypeControl = NULL;
	}
	name.clear();
	currentMoney = 0;
	totalMoney = 0;
	lives = 0;
}


std::string GODMissionObject::XML_OBJECT_NAME = "mission";

std::string GODMissionObject::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODMissionObject::parseXMLObject(GODXMLObject* object) {
	GODMissionObject* missionObject = new GODMissionObject();
	GODAttributes* attributes = object->getAttributes();
	while (attributes != NULL && attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "name") {
			missionObject->setName(attribute->getValue());
		} else if (attribute->getName() == "money") {
			missionObject->setTotalMoney(atoi(attribute->getValue().c_str()));
			missionObject->setCurrentMoney(atoi(attribute->getValue().c_str()));
		} else if (attribute->getName() == "lives") {
			missionObject->setLives(atoi(attribute->getValue().c_str()));
		}
	}

	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		if (GODXMLMapping::getInstance()->getXMLMapping(child->getName())) {
			GODXMLObjectParser* returnObject = (GODXMLObjectParser*)GODXMLMapping::getInstance()->getXMLMapping(child->getName())->parseXMLObject(child);
			if (child->getName() == "landscape") {
				missionObject->setLandscapeControl((GODLandscapeControl*)returnObject);
			} else if (child->getName() == "unitTypes") {
				missionObject->setUnitTypeControl((GODUnitTypeControl*)returnObject);
			}
		}
	}
	return missionObject;
}

GODUnitControl* GODMissionObject::getUnitControl() {
	return this->unitControl;
}

void GODMissionObject::setUnitControl(GODUnitControl* unitControl) {
	this->unitControl = unitControl;
}

GODLandscapeControl* GODMissionObject::getLandscapeControl() {
	return this->landscapeControl;
}

void GODMissionObject::setLandscapeControl(GODLandscapeControl* landscapeControl) {
	this->landscapeControl = landscapeControl;
}

GODUnitTypeControl* GODMissionObject::getUnitTypeControl() {
	return this->unitTypeControl;
}

void GODMissionObject::setUnitTypeControl(GODUnitTypeControl* unitTypeControl) {
	this->unitTypeControl = unitTypeControl;
}

std::string GODMissionObject::getName() {
	return this->name;
}

void GODMissionObject::setName(std::string name) {
	this->name = name;
}

int GODMissionObject::getCurrentMoney() {
	return this->currentMoney;
}

void GODMissionObject::setCurrentMoney(int currentMoney) {
	this->currentMoney = currentMoney;
}

int GODMissionObject::getTotalMoney() {
	return this->totalMoney;
}

void GODMissionObject::setTotalMoney(int totalMoney) {
	this->totalMoney = totalMoney;
}

int GODMissionObject::getLives() {
	return this->lives;
}

void GODMissionObject::setLives(int lives) {
	this->lives = lives;
}
