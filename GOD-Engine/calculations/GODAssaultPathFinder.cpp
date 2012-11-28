#include "GODCalculations.h"

GODAssaultPathFinder::GODAssaultPathFinder() {
}

GODAssaultPathFinder::~GODAssaultPathFinder() {
}

bool GODAssaultPathFinder::createLandscapeObject(Utilities_GridLocation* location) {
	return true;
}

bool GODAssaultPathFinder::placeUnit(Utilities_GridLocation* location) {
	return true;
}

bool GODAssaultPathFinder::removeUnit(Utilities_GridLocation* location) {
	return true;
}

/**
 * Op dit moment heeft deze code weinig slims, hij kan hiermee vrij gemakkelijk vast
 * komen te zitten, moet nog even nadenken over hoe het beter kan.
 *
 * Hij is al wel thread safe :)
 */
bool GODAssaultPathFinder::moveUnit(GODUnitObject* unit) {
	if (unit->getOwner() == 1) {
		unit->restUnit();
		GODEvents::getInstance()->addGODObject(unit);
		return true;
	}

	GODPathObject* pathObject = unit->getGODPath();
	Utilities_GridLocation* currentGrid = unit->getLocation();
	GODLandscapeObject* start = landscapeControl->getLandscapeObject(currentGrid);
	Utilities_Direction* direction = pathObject->getDirection();
	if (direction == NULL) {
		int distanceX = calculateSingleValue(currentGrid->getX(), pathObject->getEndLocation()->getX());
		int distanceY = calculateSingleValue(currentGrid->getY(), pathObject->getEndLocation()->getY());
		int directionX = 0;
		int directionY = 0;
		if (distanceX > distanceY) {
			directionX = (currentGrid->getX()-pathObject->getEndLocation()->getX() > 0)? -1 : 1;
		} else if (distanceX < distanceY) {
			directionY = (currentGrid->getY()-pathObject->getEndLocation()->getY() > 0)? -1 : 1;
		} else {
			directionX = (currentGrid->getX()-pathObject->getEndLocation()->getX() > 0)? -1 : 1;
			directionY = (currentGrid->getY()-pathObject->getEndLocation()->getY() > 0)? -1 : 1;
		}
		direction = new Utilities_Direction(directionX, directionY);
		pathObject->setDirection(direction);
	}
	int shortestValue = -1;
	Utilities_GridLocation* lowestSide = NULL;
	int count = 0;
	int directionSwitcher = 0;
	bool clockWise = true;
	bool hasSwitched = false;
	int clockWiseMod = 0;
	while (shortestValue < 0 && count < 9) {
		lowestSide = calculateBestMove(unit, start, direction, 0, pathObject->getEndLocation(), &shortestValue);
		if (pathObject->getPreviousMove() != NULL && pathObject->getPreviousMove()->equals(lowestSide)) {
			shortestValue = -1;
		}
		if (shortestValue < 0) {
			if (!hasSwitched) {
				int counterTestX = currentGrid->getX()+1;
				int counterTestY = currentGrid->getY()+1;
				if (counterTestX < landscapeControl->getWidth() && counterTestY < landscapeControl->getHeight()) {
					int distanceX = calculateSingleValue(currentGrid->getX(), pathObject->getEndLocation()->getX());
					int distanceY = calculateSingleValue(currentGrid->getY(), pathObject->getEndLocation()->getY());
					int testDistanceX = calculateSingleValue(counterTestX, pathObject->getEndLocation()->getX());
					int testDistanceY = calculateSingleValue(counterTestX, pathObject->getEndLocation()->getY());
					if ((testDistanceX > distanceX && testDistanceY > distanceY) ||
						(distanceY > distanceX && testDistanceY > distanceY) || 
						(testDistanceX > distanceX && distanceX > distanceY)){
						clockWiseMod = 1;
					}
				}
				hasSwitched = true;
			}
			directionSwitcher++;
			clockWise = (directionSwitcher%2==clockWiseMod);
			for (int i=0; i<directionSwitcher; i++) {
				if (clockWise) {
					direction->switchDirectionClockwise();
				} else {
					direction->switchDirectionCounterClockwise();
				}
			}
		}
		count++;
	}

	if (lowestSide == NULL) {
		return false;
	}

	GODLandscapeObject* landscapeObject = landscapeControl->getLandscapeObject(lowestSide);
	// Corner Check
	if (landscapeObject->getPunishment() > 0) {
		landscapeControl->getLandscapeObject(unit->getLocation())->increasePunishment();
		if (pathObject->getPreviousMove() != NULL) {
			landscapeControl->getLandscapeObject(pathObject->getPreviousMove())->increasePunishment();
		}
	} else {
		Utilities_Direction* cornerCheck = new Utilities_Direction(0,1);
		Utilities_Size* cornerCheckSize = new Utilities_Size(1,1);
		int sideCheck = 0;
		bool isCorner = false;
		for (int i=0; i<8; i++) {
			Utilities_GridLocation* newGrid = direction->getRecalculatedGridLocation(lowestSide);
			if (landscapeControl->isOnField(newGrid)) {
				if (!landscapeControl->isEmpty(newGrid, cornerCheckSize, unit->getOwner(), 1, true) || landscapeControl->getLandscapeObject(newGrid)->getPunishment() > 0) {
					if (sideCheck > 0 || cornerCheck->isVertical() || cornerCheck->isHorizontal()) {
						if (sideCheck > 0 && (cornerCheck->isHorizontal() || cornerCheck->isVertical())) {
							isCorner = true;
							i = 8;
							continue;
						}
						sideCheck++;
					}
				} else if (sideCheck > 0) {
					sideCheck = 0;
				}
			}
			cornerCheck->switchDirectionClockwise();
		}
		if (isCorner) {
			landscapeObject->increasePunishment();
		}
	}
	if (pathObject->getPreviousMove() != NULL && calculateRouteValue(pathObject->getPreviousMove(), pathObject->getEndLocation()) < calculateRouteValue(lowestSide, pathObject->getEndLocation())) {
		bool switchCounter = true;
		direction->switchDirectionCounterClockwise();
		Utilities_GridLocation* gridTestCounter = new Utilities_GridLocation(unit->getLocation()->getX()+direction->getX(), unit->getLocation()->getX()+direction->getY());
		if (!landscapeControl->isOnField(gridTestCounter)) {
			switchCounter = false;
		} else {
			direction->switchDirectionClockwise();
			direction->switchDirectionClockwise();
			Utilities_GridLocation* gridTestClock = new Utilities_GridLocation(unit->getLocation()->getX()+direction->getX(), unit->getLocation()->getX()+direction->getY());
			if (landscapeControl->isOnField(gridTestCounter)) {
				switchCounter = (calculateRouteValue(gridTestCounter, pathObject->getEndLocation()) < calculateRouteValue(gridTestClock, pathObject->getEndLocation()));
			}
		}
		if (switchCounter) {
			direction->switchDirectionCounterClockwise();
			direction->switchDirectionCounterClockwise();
		}
	}
	if (landscapeControl->isEmpty(lowestSide, unit->getSize(), unit->getOwner(), 1, true)) { // isEmpty is duurder als de verplaats kost
		unit->moveUnit(unit->getLocation(), lowestSide, unit->getAttribute(GODUnitObject::MOVEMENT), landscapeControl->getModifier(), landscapeControl->getXPlaneModifier(), landscapeControl->getYPlaneModifier());
		landscapeObject->setLocked(true);
		landscapeControl->placeUnit(unit, lowestSide);
		GODEvents::getInstance()->addGODObject(unit);
		landscapeObject->setLocked(false);
	}
	return true;
}

Utilities_GridLocation* GODAssaultPathFinder::calculateBestMove(GODUnitObject* unit, GODLandscapeObject* start, Utilities_Direction* direction, int level, Utilities_GridLocation* endLocation, int* value) {
	int lowestIterationCost = -1;
	Utilities_GridLocation* lowestSide = NULL;
	for (int i=0; i<3; i++) {
		int x = start->getLocation()->getX()+direction->getX();
		int y = start->getLocation()->getY()+direction->getY();
		if (direction->isDiagonal() && i == 0) {
			if (direction->getY() == direction->getX()) {
				y += -1*direction->getY();
			} else {
				x += -1*direction->getX();	
			}
		} else if (direction->isDiagonal() && i == 2) {
			if (direction->getY() == direction->getX()) {
				x += -1*direction->getX();
			} else {
				y += -1*direction->getY();	
			}
		} else if (direction->isHorizontal()) {
			if (direction->getX() < 0) {
				y += (i-1)*-1;
			} else {
				y += i-1;
			}
		} else if (direction->isVertical()) {
			if (direction->getY() > 0) {
				x += (i-1)*-1;
			} else {
				x += i-1;
			}
		}
		GODLandscapeObject* nextMove = landscapeControl->getLandscapeObject(new Utilities_GridLocation(x, y));
		if (nextMove != NULL && landscapeControl->isEmpty(nextMove->getLocation(), unit->getSize(), unit->getOwner(), 1, true)) {
			int currentIterationCost = 0;
			if (level == 0) {
				calculateBestMove(unit, nextMove, direction, 1, endLocation, &currentIterationCost);
			}
			int subTotalIterationCost = calculateRouteValue(nextMove, endLocation);
			if (currentIterationCost >= 0) {
				currentIterationCost = currentIterationCost+subTotalIterationCost;
			}
			if (lowestIterationCost == -1 || currentIterationCost < lowestIterationCost) {
				lowestIterationCost = currentIterationCost;
				lowestSide = nextMove->getLocation();
			}
		} else if (level == 1 && nextMove == NULL) {
			lowestIterationCost = -2;
		}
	}
	*value = lowestIterationCost;
	return lowestSide;
}

int GODAssaultPathFinder::calculateRouteValue(Utilities_GridLocation* grid, Utilities_GridLocation* endLocation) {
	int distanceX = calculateSingleValue(grid->getX(),endLocation->getX());
	int distanceY = calculateSingleValue(grid->getY(),endLocation->getY());
	return distanceX+distanceY;
}

int GODAssaultPathFinder::calculateRouteValue(GODLandscapeObject* lanscapeObject, Utilities_GridLocation* endLocation) {
	return calculateRouteValue(lanscapeObject->getLocation(), endLocation)+lanscapeObject->getPunishment();
}

int GODAssaultPathFinder::calculateSingleValue(int current, int final) {
	int distance = current-final;
	if (distance < 0) {
		distance = distance*-1;
	}
	return distance;
}
