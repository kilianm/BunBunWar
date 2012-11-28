#include "GODWaveObject.h"

GODWaveObject::GODWaveObject() {
	this->number = 0;
	this->reward = 0;
	this->unitType = NULL;
	this->amount = 0;
}

GODWaveObject::~GODWaveObject() {
	this->number = 0;
	this->reward = 0;
	this->unitType = NULL;
	this->amount = 0;
}

int GODWaveObject::getNumber() {
	return this->number;
}

void GODWaveObject::setNumber(int number) {
	this->number = number;
}

int GODWaveObject::getReward() {
	return this->reward;
}

void GODWaveObject::setReward(int reward) {
	this->reward = reward;
}

int GODWaveObject::getUnitType() {
	return this->unitType;
}

void GODWaveObject::setUnitType(int unitType) {
	this->unitType = unitType;
}

int GODWaveObject::getUpgrade() {
	return this->upgrade;
}

void GODWaveObject::setUpgrade(int upgrade) {
	this->upgrade = upgrade;
}

int GODWaveObject::getAmount() {
	return this->amount;
}

void GODWaveObject::setAmount(int amount) {
	this->amount = amount;
}

std::string GODWaveObject::XML_OBJECT_NAME = "wave";

std::string GODWaveObject::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODWaveObject::parseXMLObject(GODXMLObject* object) {
	GODWaveObject* waveObject = new GODWaveObject();
	GODAttributes* attributes = object->getAttributes();
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		int value = atoi(attribute->getValue().c_str());
		if (attribute->getName() == "number") {
			waveObject->setNumber(value);
		} else if (attribute->getName() == "reward") {
			waveObject->setReward(value);
		} else if (attribute->getName() == "unitType") {
			waveObject->setUnitType(value);
		} else if (attribute->getName() == "upgrade") {
			waveObject->setUpgrade(value);
		} else if (attribute->getName() == "amount") {
			waveObject->setAmount(value);
		}
	}
	return waveObject;
}
