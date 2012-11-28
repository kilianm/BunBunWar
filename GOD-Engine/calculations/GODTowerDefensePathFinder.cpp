#include "GODCalculations.h"

GODTowerDefensePathFinder::GODTowerDefensePathFinder() {
	baselinePath = NULL;
}

GODTowerDefensePathFinder::~GODTowerDefensePathFinder() {
	delete baselinePath;
}

void GODTowerDefensePathFinder::setLandscapeControl(GODLandscapeControl* landscapeControl) {
	this->landscapeControl = landscapeControl;
	initBaseline();
}

void GODTowerDefensePathFinder::initBaseline() {
	int x = (int)landscapeControl->getWidth()/2;
	this->baselinePath = new Utilities_Path(new Utilities_GridLocation(x, 0), landscapeControl->getWidth(), landscapeControl->getHeight());
	for (int y = 1; y <= landscapeControl->getHeight(); y++) {
		this->baselinePath->addStep(new Utilities_GridLocation(x,y));
	}
	calculateBaseline();
}

void GODTowerDefensePathFinder::calculateBaseline() {
	for (int x = 0; x < landscapeControl->getWidth(); x++) {
		for (int y = 0; y < landscapeControl->getHeight(); y++) {
			Utilities_GridLocation* location = new Utilities_GridLocation(x,y);
			if (baselinePath->inPath(location) && !landscapeControl->isEmpty(location)) {
				baselinePath->createIntersect(location);
				if (!fixBaseline(location))
					throw new GODException("GODTowerDefensePathFinderCannotCreateBaseline","GODTowerDefensePathFinder::calculateBaseline()");
			}
		}
	}
}

bool GODTowerDefensePathFinder::createLandscapeObject(Utilities_GridLocation* location) {
	return this->placeUnit(location);
}

bool GODTowerDefensePathFinder::placeUnit(Utilities_GridLocation* location) {
	if (baselinePath->inPath(location) && !landscapeControl->isEmpty(location)) {
		baselinePath->createIntersect(location);
		return fixBaseline(location);
	} 
	return true;
}

bool GODTowerDefensePathFinder::removeUnit(Utilities_GridLocation* location) {
	if (baselinePath->inPath(location)) {
		baselinePath->createIntersect(location);
		return fixBaseline(location);
	} 
	return true;
}

bool GODTowerDefensePathFinder::fixBaseline(Utilities_GridLocation* intersectionPoint) {
	if (!baselinePath->isBroken())
		return true;

	int direction;
	if (intersectionPoint)
		direction = getLocationDirection(baselinePath->findFirstEnd(), intersectionPoint);
	else
		direction = getLocationDirection(baselinePath->findFirstEndNode()->getBehindNode()->getLocation(), baselinePath->findFirstEnd());
		
	Utilities_Path* gluePath = fixIntersectedPath(baselinePath->findFirstEnd(), baselinePath->findLastEnd(), direction);
	if (gluePath && baselinePath->findLastEnd()->equals(gluePath->getLastStep())) {
		this->baselinePath->addPathFix(gluePath);
	}

	if (baselinePath->isBroken())
		return false;
	else
		return true;
}

Utilities_Path* GODTowerDefensePathFinder::fixIntersectedPath(Utilities_GridLocation* startPoint, Utilities_GridLocation* endPoint, int intersectDirection) {
	Utilities_Path* clockPath = new Utilities_Path(startPoint, baselinePath->getWidth(), baselinePath->getHeight());
	Utilities_Path* counterClockPath = new Utilities_Path(startPoint, baselinePath->getWidth(), baselinePath->getHeight());
	Utilities_Path* workingPath = NULL;
	int favoredDirectionClock = getNextDirection(intersectDirection, false, 2);
	int favoredDirectionCounterClock = getNextDirection(intersectDirection, true, 2);
	int maxTries = landscapeControl->getWidth()*landscapeControl->getHeight();
	for (int i = 0; i <= maxTries; i++) {
		if (endPoint->equals(clockPath->getLastStep())) {
			workingPath = clockPath;
			delete counterClockPath;
			break;
		} else {
			Utilities_GridLocation* nextStep = findNextStep(clockPath, &favoredDirectionClock, true);
			if (nextStep)
				clockPath->addStep(nextStep);
		}
		if (endPoint->equals(counterClockPath->getLastStep())) {
			workingPath = counterClockPath;
			delete clockPath;
			break;
		} else {
			Utilities_GridLocation* nextStep = findNextStep(counterClockPath, &favoredDirectionCounterClock, false);
			if (nextStep)
				counterClockPath->addStep(nextStep);
		}
	}
	return workingPath;
}

Utilities_GridLocation* GODTowerDefensePathFinder::findNextStep(Utilities_Path* path, int* favoredDirection, bool clockWise) {
	Utilities_GridLocation* nextStep = NULL;
	Utilities_GridLocation* lastStep = path->getLastStep();
	if (!lastStep)
		lastStep = path->getFirstStep();

	*favoredDirection = getNextDirection(*favoredDirection,clockWise, 2);
	int direction = *favoredDirection;
	clockWise = !clockWise;

	bool keepTrying = true;
	while(keepTrying){
		Utilities_GridLocation* nextPossibleStep = getDirectionLocation(lastStep, direction);
		if (nextPossibleStep && isValidMove(lastStep, nextPossibleStep, false, false)) {
			nextStep = nextPossibleStep;
			keepTrying = false;
		} 
        direction = getNextDirection(direction, clockWise);
		if (direction == *favoredDirection)
			keepTrying = false;
	}
	if (nextStep){
		*favoredDirection = getLocationDirection(lastStep, nextStep);
	}
	return nextStep;
}

int GODTowerDefensePathFinder::getNextDirection(int direction, bool clockWise, int steps) {
	if (clockWise) {
		if (direction >= 8)
			direction = 1;
		else 
			direction++;
	} else {
		if (direction <= 1)
			direction = 8;
		else 
			direction--;
	}
	if (steps > 1)
		direction = getNextDirection(direction, clockWise, --steps);
	return direction;
}

bool GODTowerDefensePathFinder::moveUnit(GODUnitObject* unit) {
	bool pathBlocked = this->baselinePath->isBroken();

	if (unit->getOwner() == 1) {
		if (!pathBlocked) {
			unit->restUnit();
			GODEvents::getInstance()->addGODObject(unit);
		}
		return !pathBlocked;
	}

	if (!pathBlocked && !this->baselinePath->inPath(unit->getLocation(), GODTowerDefensePathFinder::SAFEZONE_OFFSET)) {
		if (!moveLostUnit(unit)) {
			pathBlocked = true;
			moveBaselineUnit(unit);
		}
	} else {
		unit->resetPath();
		if (!moveBaselineUnit(unit))
			pathBlocked = true;
	}
	return !pathBlocked;
}

bool GODTowerDefensePathFinder::moveBaselineUnit(GODUnitObject* unit) {
	int defaultDirection = getClosestBaselineDirection(unit);
	Utilities_GridLocation* newPos = calculateUnitMove(unit, defaultDirection, true);
	if (newPos) {
		moveUnit(unit, newPos);
		return true;
	}
	return false;
}

bool GODTowerDefensePathFinder::moveLostUnit(GODUnitObject* unit) {
	Utilities_GridLocation* nextPosition = unit->getNextLocation();
	if (!nextPosition) {
		Utilities_GridLocation* unitLocation = unit->getLocation();
		Utilities_Path* unitPath = new Utilities_Path(unitLocation, baselinePath->getWidth(), baselinePath->getHeight());
		Utilities_GridLocation* baselineLocation = NULL;
		int baselineOffset = 0;
		do {
			Utilities_GridLocation* westLoc = new Utilities_GridLocation(unitLocation->getX()-baselineOffset, unitLocation->getY()+baselineOffset);
			Utilities_GridLocation* eastLoc = new Utilities_GridLocation(unitLocation->getX()+baselineOffset, unitLocation->getY()+baselineOffset);
			if (baselinePath->inPath(westLoc))
				baselineLocation = westLoc;
			if (baselinePath->inPath(eastLoc))
				baselineLocation = eastLoc;
			baselineOffset++;
		} while (!baselineLocation);
		bool gotIntersection = false;
		int baselineDistance = unitLocation->getX() - baselineLocation->getX();
		int offsetX = 0;
		int offsetY = 0;
		Utilities_GridLocation* firstIntersectPos = NULL;
		do {
			if (baselineDistance > 0)
				offsetX--;
			else if (baselineDistance < 0)
				offsetX++;
			offsetY++;
			Utilities_PathNode* lastStepNode = unitPath->getLastStepNode();
			if (!lastStepNode)
				lastStepNode = unitPath->getFirstStepNode();
			Utilities_GridLocation* tryPos = new Utilities_GridLocation(unitLocation->getX()+offsetX, unitLocation->getY()+offsetY);
			if (!gotIntersection) {
				if (this->isValidMove(lastStepNode->getLocation(), tryPos, false, false))
				{
					unitPath->addStep(tryPos);
					unit->setPath(unitPath);
				} else {
					if (!firstIntersectPos)
						firstIntersectPos = tryPos;
					gotIntersection = true;
				}
			}
			if (gotIntersection && this->isValidMove(tryPos, false)) {
				Utilities_Path* fixPath = fixIntersectedPath(lastStepNode->getLocation(), tryPos, getLocationDirection(lastStepNode->getLocation(), firstIntersectPos));
				unitPath->addPath(fixPath);
				unit->setPath(unitPath);
				gotIntersection = false;
			}
			nextPosition = unit->getNextLocation();
		} while(!unitPath->getLastStep() || !this->baselinePath->inPath(unitPath->getLastStep(), GODTowerDefensePathFinder::SAFEZONE_OFFSET));
	}
	if (nextPosition) {
		moveUnit(unit, nextPosition);
		return true;
	}
	return false;
}

int GODTowerDefensePathFinder::getClosestBaselineDirection(GODUnitObject* unit) {
	Utilities_PathNode* closestNode = this->baselinePath->getClosestNode(unit->getLocation());
	Utilities_PathNode* nextNode = closestNode->getInFrontNode();
	int firstBaselineDirection = 0;
	int secondBaselineDirection = 0;
	int thirdBaselineDirection = 0;
	if (closestNode->getBehindNode())
		firstBaselineDirection = getLocationDirection(closestNode->getBehindNode()->getLocation(), closestNode->getLocation());
	if (nextNode) {
		secondBaselineDirection = getLocationDirection(closestNode->getLocation(), nextNode->getLocation());
		if (nextNode->getInFrontNode())
			thirdBaselineDirection = getLocationDirection(nextNode->getLocation(), nextNode->getInFrontNode()->getLocation());
	}
	int baselineDirection = 0;
	if (thirdBaselineDirection != 0)
		baselineDirection = thirdBaselineDirection;
	else if (secondBaselineDirection != 0)
		baselineDirection = secondBaselineDirection;
	else
		baselineDirection = firstBaselineDirection;
	if (firstBaselineDirection != secondBaselineDirection && secondBaselineDirection != 0)
		baselineDirection = secondBaselineDirection-((secondBaselineDirection-firstBaselineDirection)/2);
	if (thirdBaselineDirection != secondBaselineDirection && secondBaselineDirection != 0)
		baselineDirection = secondBaselineDirection-((secondBaselineDirection-thirdBaselineDirection)/2);
	return baselineDirection;
}

int GODTowerDefensePathFinder::getRandomDirection(int baseDirection, int discloseDir1, int discloseDir2) {
	int result = baseDirection;
	if (baseDirection == discloseDir1 || baseDirection == discloseDir2) {
		int random = ((rand()%2)*2) - 1;
		result = baseDirection + random;
		if (result == discloseDir1 || result == discloseDir2) {
			if (random = 1)
				return result - 2;
			if (random = -1)
				return result + 2;
		}
	}
	if (baseDirection-1 == discloseDir1 || baseDirection-1 == discloseDir2) {
		return baseDirection;
	}
	return baseDirection + (rand()%3)-1;
}

Utilities_GridLocation* GODTowerDefensePathFinder::calculateUnitMove(GODUnitObject* unit, int defaultDirection, bool checkNextMove) {
	int discloseDir1 = 0;
	int discloseDir2 = 0;
	for (int i = 0; i < 20; i++) {
		int direction = getRandomDirection(defaultDirection, discloseDir1, discloseDir2);
		Utilities_GridLocation* newPos = getDirectionLocation(unit->getLocation(), direction);
		if (newPos && isValidMove(unit->getLocation(), newPos, checkNextMove, false)) {
			return newPos;
		} else {
			bool clockWise = ((rand()%2)>0);
			if (newPos) {
				if (!baselinePath->inPath(new Utilities_GridLocation(newPos->getX()-(GODTowerDefensePathFinder::SAFEZONE_OFFSET+1), newPos->getY())))
					clockWise = true;
				if (!baselinePath->inPath(new Utilities_GridLocation(newPos->getX()+(GODTowerDefensePathFinder::SAFEZONE_OFFSET+1), newPos->getY())))
					clockWise = false;
			}
			if (discloseDir1 == 0)
				discloseDir1 = direction;
			else if (discloseDir2 == 0)
				discloseDir2 = direction;
			else {
				discloseDir1 = getNextDirection(defaultDirection, clockWise);
				discloseDir2 = 0;
				defaultDirection = getNextDirection(discloseDir1,clockWise);
			}
		}
	}
	return NULL;
}

bool GODTowerDefensePathFinder::isValidMove(Utilities_GridLocation* newPos, bool checkBaseLineOffset) {
	if (checkBaseLineOffset && !baselinePath->inPath(newPos, GODTowerDefensePathFinder::SAFEZONE_OFFSET))
		return false;
	return (landscapeControl->isOnField(newPos) && landscapeControl->isEmpty(newPos, new Utilities_Size(1,1), 0, 1, true));
}

bool GODTowerDefensePathFinder::isValidMove(Utilities_GridLocation* oldPos, Utilities_GridLocation* newPos, bool checkBaseLineOffset, bool allowDiagonal) {
	int direction = getLocationDirection(oldPos, newPos);
	if (allowDiagonal || !isDiagonal(direction))
		return isValidMove(newPos, checkBaseLineOffset);
	Utilities_GridLocation* loc1 = getDirectionLocation(oldPos, getNextDirection(direction, true));
	Utilities_GridLocation* loc2 = getDirectionLocation(oldPos, getNextDirection(direction, false));
	return (isValidMove(loc1, checkBaseLineOffset) && isValidMove(loc2, checkBaseLineOffset));
}

void GODTowerDefensePathFinder::moveUnit(GODUnitObject* unit, Utilities_GridLocation* newPos) {
	GODLandscapeObject* landscapeObject = landscapeControl->getLandscapeObject(newPos);
	unit->moveUnit(unit->getLocation(), newPos, unit->getAttribute(GODUnitObject::MOVEMENT), landscapeControl->getModifier(), landscapeControl->getXPlaneModifier(), landscapeControl->getYPlaneModifier());
	landscapeObject->setLocked(true);
	landscapeControl->placeUnit(unit, newPos);
	GODEvents::getInstance()->addGODObject(unit);
	landscapeObject->setLocked(false);
}

Utilities_GridLocation* GODTowerDefensePathFinder::getDirectionLocation(Utilities_GridLocation* oldPos, int direction) {
	int x = oldPos->getX();
	int y = oldPos->getY();
	Utilities_GridLocation* newPos = NULL;
	if (direction == GODTowerDefensePathFinder::pathDirection_N)
		newPos = new Utilities_GridLocation(x, y-1);
	if (direction == GODTowerDefensePathFinder::pathDirection_S)
		newPos = new Utilities_GridLocation(x, y+1);
	if (direction == GODTowerDefensePathFinder::pathDirection_W)
		newPos = new Utilities_GridLocation(x-1, y);
	if (direction == GODTowerDefensePathFinder::pathDirection_E)
		newPos = new Utilities_GridLocation(x+1, y);
	if (direction == GODTowerDefensePathFinder::pathDirection_NW)
		newPos = new Utilities_GridLocation(x-1, y-1);
	if (direction == GODTowerDefensePathFinder::pathDirection_NE)
		newPos = new Utilities_GridLocation(x+1, y-1);
	if (direction == GODTowerDefensePathFinder::pathDirection_SW)
		newPos = new Utilities_GridLocation(x-1, y+1);
	if (direction == GODTowerDefensePathFinder::pathDirection_SE)
		newPos = new Utilities_GridLocation(x+1, y+1);
	return newPos;
}

bool GODTowerDefensePathFinder::isDiagonal(int direction){
	if (direction == GODTowerDefensePathFinder::pathDirection_N ||
		direction == GODTowerDefensePathFinder::pathDirection_W || 
		direction == GODTowerDefensePathFinder::pathDirection_E || 
		direction == GODTowerDefensePathFinder::pathDirection_S)
		return false;
	return true;
}

int GODTowerDefensePathFinder::getLocationDirection(Utilities_GridLocation* fromPos, Utilities_GridLocation* toPos) {
	int x = toPos->getX() - fromPos->getX();
	int y = toPos->getY() - fromPos->getY();

	int direction = 0;
	if (x == 0 && y == -1)
		direction = GODTowerDefensePathFinder::pathDirection_N;
	if (x == 0 && y == +1)
		direction = GODTowerDefensePathFinder::pathDirection_S;
	if (x == -1 && y == 0)
		direction = GODTowerDefensePathFinder::pathDirection_W;
	if (x == 1 && y == 0)
		direction = GODTowerDefensePathFinder::pathDirection_E;
	if (x == -1 && y == -1)
		direction = GODTowerDefensePathFinder::pathDirection_NW;
	if (x == 1 && y == -1)
		direction = GODTowerDefensePathFinder::pathDirection_NE;
	if (x == -1 && y == 1)
		direction = GODTowerDefensePathFinder::pathDirection_SW;
	if (x == 1 && y == 1)
		direction = GODTowerDefensePathFinder::pathDirection_SE;
	return direction;
}