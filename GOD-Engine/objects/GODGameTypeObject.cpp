#include "GODGameTypeObject.h"

GODGameTypeObject::GODGameTypeObject() {
	pathFinder = NULL;
	alwaysAttack = false;
	attackOnBlock = false;
	disappear = false;
}

GODGameTypeObject::~GODGameTypeObject() {
	delete pathFinder;
	alwaysAttack = false;
	attackOnBlock = false;
	disappear = false;
	name.clear();
}

std::string GODGameTypeObject::XML_OBJECT_NAME = "gametype";

std::string GODGameTypeObject::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODGameTypeObject::parseXMLObject(GODXMLObject* object) {
	GODGameTypeObject* gameType = new GODGameTypeObject();
	GODAttributes* attributes = object->getAttributes();
	while (attributes != NULL && attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "name") {
			gameType->setName(attribute->getValue());
		} else if (attribute->getName() == "pathfinder") {
			if (attribute->getValue() == "Assault") {
				gameType->setPathFinder(new GODAssaultPathFinder());
			} else if (attribute->getValue() == "TowerDefense") {
				gameType->setPathFinder(new GODTowerDefensePathFinder());
			}
		} else if (attribute->getName() == "alwaysOnAttack") {
			gameType->setAlwaysAttack((attribute->getValue() == "true") ? true : false);
		} else if (attribute->getName() == "attackOnBlock") {
			gameType->setAttackOnBlock((attribute->getValue() == "true") ? true : false);
		} else if (attribute->getName() == "disappearOnFinish") {
			gameType->setDisapearOnFinish((attribute->getValue() == "true") ? true : false);
		}
	}
	return gameType;
}

GODPathFinder* GODGameTypeObject::getPathFinder() {
	return this->pathFinder;
}

void GODGameTypeObject::setPathFinder(GODPathFinder* pathFinder) {
	this->pathFinder = pathFinder;
}

bool GODGameTypeObject::isAlwaysAttack() {
	return this->alwaysAttack;
}

void GODGameTypeObject::setAlwaysAttack(bool alwaysAttack) {
	this->alwaysAttack = alwaysAttack;
}

bool GODGameTypeObject::isAttackOnBlock() {
	return this->attackOnBlock;
}

void GODGameTypeObject::setAttackOnBlock(bool attackOnBlock) {
	this->attackOnBlock = attackOnBlock;
}

std::string GODGameTypeObject::getName() {
	return this->name;
}

void GODGameTypeObject::setName(std::string name) {
	this->name = name;
}

bool GODGameTypeObject::disappearOnFinish() {
	return disappear;
}
void GODGameTypeObject::setDisapearOnFinish(bool disappear) {
	this->disappear = disappear;
}
