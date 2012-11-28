#include "GODObjects.h"

GODUnitObject::GODUnitObject() {
	this->id = 0;
	this->owner = 0;
	this->unitType = NULL;
	this->unitModifier = NULL;
	this->target = NULL;
	this->location = NULL;
	this->GODPath = NULL;
	this->lastAttack = 0;
	this->used = false;
	this->dead = false;
	this->upgrade = true;

	this->xTotal = 0.0f;
	this->xLeft = 0.0f;
	this->yTotal = 0.0f;
	this->yLeft = 0.0f;
	this->timeForMovement = 0.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = 0.0f;
	this->rotate = 0.0f;
	this->finished = false;
	this->timeForDamageSet = 0.0f;
	this->damage = 0;
	this->path = NULL;
}

/**
 * Voor Unit's zonder begin positie
 */
GODUnitObject::GODUnitObject(int id, int owner, GODUnitTypeObject* unitType) {
	this->id = id;
	this->owner = owner;
	this->unitType = unitType;

	this->unitModifier = new GODUnitModifierObject();
	this->target = NULL;
	this->location = NULL;
	this->GODPath = NULL;
	this->lastAttack = 0;
	this->used = false;
	this->dead = false;
	this->upgrade = true;

	this->xTotal = 0.0f;
	this->xLeft = 0.0f;
	this->yTotal = 0.0f;
	this->yLeft = 0.0f;
	this->timeForMovement = 0.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = 0.0f;
	this->rotate = 0.0f;
	this->finished = false;
	this->timeForDamageSet = 0.0f;
	this->damage = 0;
	this->path = NULL;
}

/**
 * Statische Unit's worden hiermee gezet
 */
GODUnitObject::GODUnitObject(int id, int owner, GODUnitTypeObject* unitType, Utilities_GridLocation* location) {
	this->location = location;

	this->id = id;
	this->owner = owner;
	this->unitType = unitType;
	this->unitModifier = new GODUnitModifierObject();
	this->target = NULL;
	this->GODPath = NULL;
	this->lastAttack = 0;
	this->used = false;
	this->dead = false;
	this->upgrade = true;

	this->xTotal = 0.0f;
	this->xLeft = 0.0f;
	this->yTotal = 0.0f;
	this->yLeft = 0.0f;
	this->timeForMovement = 0.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = 0.0f;
	this->rotate = 0.0f;
	this->finished = false;
	this->timeForDamageSet = 0.0f;
	this->damage = 0;
	this->path = NULL;
}

/**
 * Bewegende Unit's worden hiermee gezet
 */
GODUnitObject::GODUnitObject(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* GODPath) {
	this->GODPath = GODPath;
	this->location = GODPath->getStartLocation();

	this->id = id;
	this->owner = owner;
	this->unitType = unitType;
	this->unitModifier = new GODUnitModifierObject();
	this->target = NULL;
	this->lastAttack = 0;
	this->used = false;
	this->dead = false;
	this->upgrade = true;

	this->xTotal = 0.0f;
	this->xLeft = 0.0f;
	this->yTotal = 0.0f;
	this->yLeft = 0.0f;
	this->timeForMovement = 0.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = 0.0f;
	this->rotate = 0.0f;
	this->finished = false;
	this->timeForDamageSet = 0.0f;
	this->damage = 0;
	this->path = NULL;
}

GODUnitObject::~GODUnitObject() {
	if (this->unitModifier) {
		delete this->unitModifier;
		this->unitModifier = NULL;
	}
	if (this->location) {
		delete this->location;
		this->location = NULL;
	}
	if (this->GODPath) {
		delete this->GODPath;
		this->GODPath = NULL;
	}
	if (this->path) {
		delete this->path;
		this->path = NULL;
	}
	this->unitType = NULL;
	this->target = NULL;
	this->owner = 0;
	this->lastAttack = 0;
	this->used = false;
	this->dead = false;
	this->upgrade = true;

	this->xTotal = 0.0f;
	this->xLeft = 0.0f;
	this->yTotal = 0.0f;
	this->yLeft = 0.0f;
	this->timeForMovement = 0.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = 0.0f;
	this->rotate = 0.0f;
	this->timeForDamageSet = 0.0f;
	this->damage = 0;
}

int GODUnitObject::getItemType() {
	return ITEMTYPE_UNIT;
}

int GODUnitObject::getObjectType() { 
	return GODObject::OBJECTTYPE_GODUnitObject; 
}

/**
 * Get the GODUnitTypeObject
 *
 * WARNING: Do not use this type for calculating your own values
 */
GODUnitTypeObject* GODUnitObject::getUnitType() {
	return GODUnitObject::unitType;
}

void GODUnitObject::setUnitType(GODUnitTypeObject* unitType) {
	GODUnitObject::unitType = unitType;
}

/**
 * Get the GODUnitModifierObject
 *
 * WARNING: Do not use this modfier for calculating your own values
 */
GODUnitModifierObject* GODUnitObject::getUnitModifier() {
	return GODUnitObject::unitModifier;
}

void GODUnitObject::setUnitModifier(GODUnitModifierObject* unitModifier) {
	GODUnitObject::unitModifier = unitModifier;
}

int GODUnitObject::getOwner() {
	return GODUnitObject::owner;
}

void GODUnitObject::setOwner(int owner) {
	GODUnitObject::owner = owner;
}

bool GODUnitObject::isDead() {
	return this->dead;
}

long GODUnitObject::getLastAttack() {
	return GODUnitObject::lastAttack;
}

void GODUnitObject::setLastAttack(long lastAttack) {
	GODUnitObject::lastAttack = lastAttack;
}

/**
 * Returns the target of this unit, or, if the target is dead, it will return NULL.
 */
GODUnitObject* GODUnitObject::getTarget() {
	if (GODUnitObject::target == NULL) {
		return NULL;
	}
	if (GODUnitObject::target->isDead()) {
		GODUnitObject::target = NULL;
	}
	return GODUnitObject::target;
}

void GODUnitObject::setTarget(GODUnitObject* target) {
	GODUnitObject::target = target;
}

bool GODUnitObject::canUpgrade() {
	return this->upgrade;
}

void GODUnitObject::setUpgrade(bool upgrade) {
	this->upgrade = upgrade;
}

bool GODUnitObject::isUsed() {
	return GODUnitObject::used;
}

void GODUnitObject::setUsed(bool used) {
	GODUnitObject::used = used;
}

Utilities_GridLocation* GODUnitObject::getLocation() {
	return GODUnitObject::location;
}

void GODUnitObject::setLocation(Utilities_GridLocation* location) {
	GODUnitObject::location = location;
}

GODPathObject* GODUnitObject::getGODPath() {
	return this->GODPath;
}

void GODUnitObject::setGODPath(GODPathObject* GODPath) {
	this->GODPath = GODPath;
}

Utilities_Path* GODUnitObject::getPath() {
	return this->path;
}

void GODUnitObject::setPath(Utilities_Path* path) {
	this->path = path;
}

void GODUnitObject::resetPath() {
	this->path = NULL;
}

void GODUnitObject::moveUnit(Utilities_GridLocation* oldLocation, Utilities_GridLocation* newLocation, int time, long modifier, long xPlaneModifier, long yPlaneModifier) {
	if (GODPath->getPreviousMove() == NULL) {
		this->setRotate(getRotation(oldLocation, newLocation));
	} else {
		int previousTurn = getRotation(GODPath->getPreviousMove(), oldLocation);
		int currentTurn = getRotation(oldLocation, newLocation);
		int finalTurn = currentTurn-previousTurn;
		if (finalTurn > 4) {
			finalTurn = finalTurn - 8;
		}
		if (finalTurn < -4) {
			finalTurn = finalTurn + 8;
		}
		this->setRotate(finalTurn);
	}
	GODPath->setPreviousMove(oldLocation);
	this->finished = false;
	float xNew = (newLocation->getX()*(float)modifier)-(float)xPlaneModifier;
	float xOld = (oldLocation->getX()*(float)modifier)-(float)xPlaneModifier;
	float yNew = (newLocation->getY()*(float)modifier)-(float)yPlaneModifier;
	float yOld = (oldLocation->getY()*(float)modifier)-(float)yPlaneModifier;
	this->xTotal = xNew - xOld;
	this->xLeft = this->xTotal;
	this->yTotal = yNew - yOld;
	this->yLeft = this->yTotal;
	this->timeForMovement = 1.0f/(float)time;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = (float)GetTickCount()/1000.0f;
}

void GODUnitObject::restUnit() {
	this->timeForMovement = 1.0f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = (float)GetTickCount()/1000.0f;
	this->finished = false;
}

void GODUnitObject::setRotate(int rotate) {
	this->rotate = (float)(rotate*45)*(float)-1;
}

float GODUnitObject::getRotate() {
	float rotate = this->rotate / ( this->timeForMovement / this->timeSinceLastMove );
	return rotate;
}

void GODUnitObject::fixTiming(long pause) {
	if (this->timeLastMove != 0.0f) {
		this->timeLastMove += ((float)pause)/1000.0f;
	}
}

void GODUnitObject::addTimeSinceLastMove(float timeLastMove) {
	if (this->timeLastMove == 0.0f) {
		this->timeLastMove = timeLastMove;
	} else {
		this->timeSinceLastMove = timeLastMove-this->timeLastMove;
		this->timeLastMove = timeLastMove;
	}
}

float GODUnitObject::getX() {
	if (this->timeSinceLastMove == 0.0f) {
		return 0.0f;
	}
	float x = this->xTotal / ( this->timeForMovement / this->timeSinceLastMove );
	this->xLeft = this->xLeft - x;
	return x;
}

float GODUnitObject::getY() {
	if (this->timeSinceLastMove == 0.0f) {
		return 0.0f;
	}
	float y = this->yTotal / ( this->timeForMovement / this->timeSinceLastMove );
	this->yLeft = this->yLeft - y;
	return y;
}

bool GODUnitObject::equals(GODUnitObject* unit) {
	return (unit->getId() == getId());
}

void GODUnitObject::setDamage(int damage) {
	this->timeForDamageSet = (float)GetTickCount()/1000.0f;
	this->damage = damage;
}

int GODUnitObject::getDamage() {
	int damage = this->damage;
	this->damage = 0;
	return damage;
}

bool GODUnitObject::hasDamage() {
	if (damage == 0 && this->timeForDamageSet != 0.0f) {
		if (this->timeForDamageSet+1.0f <= timeLastMove) {
			this->timeForDamageSet = 0.0f;
			return false;
		}
		return true;
	} else if (damage != 0) {
		return true;
	}
	return false;
}

bool GODUnitObject::isFinished() {
	if (!this->finished && getOwner() != 1) {
		if (((this->xTotal < 0.0f && this->xLeft >= 0.0f) || (this->xTotal > 0.0f && this->xLeft <= 0.0f) || (this->xLeft == 0)) 
			&& ((this->yTotal < 0.0f && this->yLeft >= 0.0f) || (this->yTotal > 0.0f && this->yLeft <= 0.0f) || (this->yLeft == 0))) {
			this->finished = true;
			this->xTotal = 0.0f;
			this->xLeft = 0.0f;
			this->yTotal = 0.0f;
			this->yLeft = 0.0f;
		}
	}
	return this->finished;
}

/**
 * Use this to modify type attributes
 * 
 * WARNING: Do not attempt to modify your own values directly through
 * GODUnitTypeObject* or GODUnitModifierObject*, this may cause some serious
 * issues in playing the game.
 *
 * @param attribute One of the attributes from a Unit 
 * @param value The value to modify the attribute with
 */
void GODUnitObject::modifyAttribute(int attribute, int value) {
	switch (attribute) {
		case HEALTH: {
			int health = GODUnitObject::unitModifier->getHealth()+value;
			GODUnitObject::unitModifier->setHealth(health);
			if (getAttribute(attribute) <= 0) {
				this->dead = true;
			}
		} break;
		case MOVEMENT: {
			GODUnitObject::unitModifier->setMovement(GODUnitObject::unitModifier->getMovement()+value);
			//TODO Recalculate Movement modifiers
		} break;
		case ATTACKPOWER: {
			GODUnitObject::unitModifier->setAttackPower(GODUnitObject::unitModifier->getAttackPower()+value);
			//TODO Recalculate AttackPower modifiers
		} break;
		case ARMOR: {
			GODUnitObject::unitModifier->setArmor(GODUnitObject::unitModifier->getArmor()+value);
			//TODO Recalculate Armor modifiers
		} break;
		case ATTACKSPEED: {
			GODUnitObject::unitModifier->setAttackSpeed(GODUnitObject::unitModifier->getAttackSpeed()+value);
			//TODO Recalculate AttackSpeed modifiers
		} break;
		case RANGE: {
			GODUnitObject::unitModifier->setRange(GODUnitObject::unitModifier->getRange()+value);
			//TODO Recalculate Range modifiers
		} break;
		case MISSRATE: {
			GODUnitObject::unitModifier->setMissRate(GODUnitObject::unitModifier->getMissRate()+value);
			//TODO Recalculate Miss modifiers
		} break;
		case CRITRATE: {
			GODUnitObject::unitModifier->setCritRate(GODUnitObject::unitModifier->getCritRate()+value);
			//TODO Recalculate Crit modifiers
		} break;
		case PRICE: {
			GODUnitObject::unitModifier->setPrice(GODUnitObject::unitModifier->getPrice()+value);
			//TODO Recalculate Price modifiers
		} break;
		case WIDTH: {
			size->setWidth(value);
		} break;
		case HEIGHT: {
			size->setHeight(value);
		} break;
	}
}

/**
 * Use this to get the attributes of a unit, this will take changes from GODUnitModifierObject
 * and GODUnitType in account
 * 
 * WARNING: You should use this to get attributes, calculating them yourself may cause
 * problems
 *
 * @param attribute One of the attributes from a Unit 
 */
int GODUnitObject::getAttribute(int attribute) {
	int returnValue = 0;
	switch (attribute) {
		case HEALTH: {
			returnValue = GODUnitObject::unitType->getHealth()+GODUnitObject::unitModifier->getHealth();
		} break;
		case MOVEMENT: {
			returnValue = GODUnitObject::unitType->getMovement()+GODUnitObject::unitModifier->getMovement();
		} break;
		case ATTACKPOWER: {
			returnValue = GODUnitObject::unitType->getAttackPower()+GODUnitObject::unitModifier->getAttackPower();
		} break;
		case ARMOR: {
			returnValue = GODUnitObject::unitType->getArmor()+GODUnitObject::unitModifier->getArmor();
		} break;
		case ATTACKSPEED: {
			returnValue = GODUnitObject::unitType->getAttackSpeed()+GODUnitObject::unitModifier->getAttackSpeed();
		} break;
		case RANGE: {
			returnValue = GODUnitObject::unitType->getRange()+GODUnitObject::unitModifier->getRange();
		} break;
		case MISSRATE: {
			returnValue = GODUnitObject::unitType->getMissRate()+GODUnitObject::unitModifier->getMissRate();
		} break;
		case CRITRATE: {
			returnValue = GODUnitObject::unitType->getCritRate()+GODUnitObject::unitModifier->getCritRate();
		} break;
		case WIDTH: {
			returnValue = size->getWidth();
		} break;
		case HEIGHT: {
			returnValue = size->getHeight();
		} break;
		case PRICE: {
			returnValue = GODUnitObject::unitType->getPrice()+GODUnitObject::unitModifier->getPrice();
		} break;
	}
	if (returnValue < 0) {
		return 0;
	}
	return returnValue;
}

int GODUnitObject::getRotation(Utilities_GridLocation* grid1, Utilities_GridLocation* grid2) {
	int directionX = grid2->getX()-grid1->getX();
	int directionY = grid2->getY()-grid1->getY();
	int turn = 0;
	if (directionX == 1) {
		if (directionY < 0) {
			turn = 7;
		} else if (directionY > 0) {
			turn = 1;
		} else {
			turn = 0;
		}
	} else if (directionX == 0) {
		if (directionY < 0) {
			turn = 6;
		} else {
			turn = 2;
		}
	} else {
		if (directionY < 0) {
			turn = 5;
		} else if (directionY > 0) {
			turn = 3;
		} else {
			turn = 4;
		}
	}
	return turn;
}

Utilities_GridLocation* GODUnitObject::getNextLocation() {
	if (this->path) {
		Utilities_PathNode* pathNode = this->path->getPath(this->getLocation());
		if (pathNode && pathNode->getInFrontNode()) {
			return pathNode->getInFrontNode()->getLocation();
		}
	}
    return NULL;
}
