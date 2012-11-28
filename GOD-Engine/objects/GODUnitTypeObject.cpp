#include "GODObjects.h"

GODUnitTypeObject::GODUnitTypeObject() {
	id = 0;
	health = 0;
	movement = 0;
	attackPower = 0;
	armor = 0;
	attackSpeed = 0;
	range = 0;
	missRate = 0;
	critRate = 0;
	price = 0;
	upgrade = 0;
}

GODUnitTypeObject::~GODUnitTypeObject() {
	id = 0;
	health = 0;
	movement = 0;
	attackPower = 0;
	armor = 0;
	attackSpeed = 0;
	range = 0;
	missRate = 0;
	critRate = 0;
	price = 0;
	upgrade = 0;
}

int GODUnitTypeObject::getId() {
	return this->id;
}
void GODUnitTypeObject::setId(int id) {
	this->id = id;
}

int GODUnitTypeObject::getHealth() {
	return this->health;
}

void GODUnitTypeObject::setHealth(int health) {
	this->health = health;
}

int GODUnitTypeObject::getMovement() {
	return this->movement;
}

void GODUnitTypeObject::setMovement(int movement) {
	this->movement = movement;
}

int GODUnitTypeObject::getAttackPower() {
	return this->attackPower;
}

void GODUnitTypeObject::setAttackPower(int attackPower) {
	this->attackPower = attackPower;
}

int GODUnitTypeObject::getArmor() {
	return this->armor;
}

void GODUnitTypeObject::setArmor(int armor) {
	this->armor = armor;
}

int GODUnitTypeObject::getAttackSpeed() {
	return this->attackSpeed;
}

void GODUnitTypeObject::setAttackSpeed(int attackSpeed) {
	this->attackSpeed = attackSpeed;
}

int GODUnitTypeObject::getRange() {
	return this->range;
}

void GODUnitTypeObject::setRange(int range) {
	this->range = range;
}

int GODUnitTypeObject::getMissRate() {
	return this->missRate;
}

void GODUnitTypeObject::setMissRate(int missRate) {
	this->missRate = missRate;
}

int GODUnitTypeObject::getCritRate() {
	return this->critRate;
}

void GODUnitTypeObject::setCritRate(int critRate) {
	this->critRate = critRate;
}

int GODUnitTypeObject::getPrice() {
	return this->price;
}

void GODUnitTypeObject::setPrice(int price) {
	this->price = price;
}

int GODUnitTypeObject::getUpgrade() {
	return this->upgrade;
}

void GODUnitTypeObject::setUpgrade(int upgrade) {
	this->upgrade = upgrade;
}

std::string GODUnitTypeObject::getMeshName() {
	return this->meshName;
}

void GODUnitTypeObject::setMeshName(std::string meshName) {
	this->meshName = meshName;
}

std::string GODUnitTypeObject::XML_OBJECT_NAME = "unitType";

std::string GODUnitTypeObject::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODUnitTypeObject::parseXMLObject(GODXMLObject* object) {
	GODUnitTypeObject* unitTypeObject = new GODUnitTypeObject();

	GODAttributes* attributes = object->getAttributes();
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "id") {
			unitTypeObject->setId(atoi(attribute->getValue().c_str()));
		}
	}

	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		GODAttributes* attributes = child->getAttributes();
		while (attributes->hasNext()) {
			GODAttribute* attribute = attributes->next();
			if (attribute->getName() == "health") {
				unitTypeObject->setHealth(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "movement") {
				unitTypeObject->setMovement(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "attackpower") {
				unitTypeObject->setAttackPower(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "armor") {
				unitTypeObject->setArmor(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "attackspeed") {
				unitTypeObject->setAttackSpeed(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "range") {
				unitTypeObject->setRange(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "missrate") {
				unitTypeObject->setMissRate(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "critrate") {
				unitTypeObject->setCritRate(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "price") {
				unitTypeObject->setPrice(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "upgrade") {
				unitTypeObject->setUpgrade(atoi(attribute->getValue().c_str()));
			} else if (attribute->getName() == "meshName") {
				unitTypeObject->setMeshName(attribute->getValue());
			}
		}
	}
	return unitTypeObject;
}
