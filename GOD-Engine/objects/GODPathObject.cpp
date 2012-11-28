#include "GODObjects.h"

GODPathObject::GODPathObject(Utilities_GridLocation* startLocation, Utilities_GridLocation* endLocation) {
	GODPathObject::startLocation = startLocation;
	GODPathObject::endLocation = endLocation;
	GODPathObject::direction = NULL;
	GODPathObject::previousMove = NULL;
	GODPathObject::lastMovementTime = 0;
}

GODPathObject::~GODPathObject() {
	if (startLocation != NULL) {
		delete startLocation;
		startLocation = NULL;
	}
	if (endLocation != NULL) {
		delete endLocation;
		endLocation = NULL;
	}
	if (direction != NULL) {
		delete direction;
		direction = NULL;
	}
	previousMove = NULL;
	lastMovementTime = 0;
}

void GODPathObject::setStartLocation(Utilities_GridLocation* startLocation) {
	GODPathObject::startLocation = startLocation;
}

Utilities_GridLocation* GODPathObject::getStartLocation() {
	return startLocation;
}

void GODPathObject::setEndLocation(Utilities_GridLocation* endLocation) {
	GODPathObject::endLocation = endLocation;
}

Utilities_GridLocation* GODPathObject::getEndLocation() {
	return endLocation;
}

void GODPathObject::setPreviousMove(Utilities_GridLocation* previousMove) {
	GODPathObject::previousMove = previousMove;
}

Utilities_GridLocation* GODPathObject::getPreviousMove() {
	return previousMove;
}

void GODPathObject::setLastMovementTime(long lastMovementTime) {
	GODPathObject::lastMovementTime = lastMovementTime;
}

long GODPathObject::getLastMovementTime() {
	return lastMovementTime;
}

void GODPathObject::setDirection(Utilities_Direction* direction) {
	GODPathObject::direction = direction;
}

Utilities_Direction* GODPathObject::getDirection() {
	return direction;
}
