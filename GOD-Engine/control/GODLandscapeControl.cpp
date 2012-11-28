#include "GODControl.h"

GODLandscapeControl::GODLandscapeControl() {
}

/**
 * Creates a new LandscapeControl with a landscape size
 *
 * @param width Width of the landscape
 * @param height Height of the landscape
 */
GODLandscapeControl::GODLandscapeControl(int width, int height) {
	GODLandscapeControl::width = width;
	GODLandscapeControl::height = height;
	loadLandscape();
	x_plane_modifier = 0;
	y_plane_modifier = 0;
	modifier = 0;
	start = NULL;
	finish = NULL;
}

/**
 * Destroy the landscape
 */
GODLandscapeControl::~GODLandscapeControl() {
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			delete landscape[i][j];
			landscape[i][j] = NULL;
		}
		delete [] landscape[i];
		landscape[i] = NULL;
	}
	delete [] landscape;
	landscape = NULL;
	x_plane_modifier = 0;
	y_plane_modifier = 0;
	modifier = 0;
	
	if (start) {
		delete start;
		start = NULL;
	}
	if (finish) {
		delete finish;
		finish = NULL;
	}
}

void GODLandscapeControl::printMapToSystem() {
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			if (landscape[i][j]->getGridKind() == GODLandscapeObject::LANDSCAPE_BLOCKED) {
				printf("x");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

std::string GODLandscapeControl::XML_OBJECT_NAME = "landscape";

std::string GODLandscapeControl::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODLandscapeControl::parseXMLObject(GODXMLObject* object) {
	GODAttributes* attributes = object->getAttributes();
	int width = 0;
	int height = 0;
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "width") {
			width = atoi(attribute->getValue().c_str());
		} else if (attribute->getName() == "height") {
			height = atoi(attribute->getValue().c_str());
		}
	}
	GODLandscapeControl* landscape = new GODLandscapeControl(width, height);
	
	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		GODLandscapeAreaObject* parsed = (GODLandscapeAreaObject*)GODXMLMapping::getInstance()->getXMLMapping(child->getName())->parseXMLObject(child);
			
		if (parsed->getArea() == "blocked") {
			GODItemObject* item = new GODItemObject();
			item->setSize(parsed->getSize());
			landscape->createLandscapeObject(parsed->getGrid(),item);
		} else if (parsed->getArea() == "start") {
			landscape->setStart(parsed);
		} else if (parsed->getArea() == "finish") {
			landscape->setFinish(parsed);
		}
	}
	return landscape;
}

void GODLandscapeControl::loadLandscape() {
	GODLandscapeControl::landscape = new GODLandscapeObject**[width];
	for (int i=0; i<width; i++) {
		landscape[i] = new GODLandscapeObject*[height];
	}
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			landscape[i][j] = new GODLandscapeObject(new Utilities_GridLocation(i,j));
		}
	}
}

int GODLandscapeControl::getWidth() {
	return width;
}

int GODLandscapeControl::getHeight() {
	return height;
}

GODLandscapeAreaObject* GODLandscapeControl::getStart() {
	return this->start;
}

void GODLandscapeControl::setStart(GODLandscapeAreaObject* start) {
	this->start = start;
}

GODLandscapeAreaObject* GODLandscapeControl::getFinish() {
	return this->finish;
}

void GODLandscapeControl::setFinish(GODLandscapeAreaObject* finish) {
	this->finish = finish;
}

void GODLandscapeControl::setModifier(int modifier) {
	this->modifier = modifier;
	this->x_plane_modifier = (this->getWidth()*modifier/2)-modifier/2;
	this->y_plane_modifier = (this->getHeight()*modifier/2)-modifier/2;
}

int GODLandscapeControl::getModifier() {
	return this->modifier;
}

int GODLandscapeControl::getXPlaneModifier() {
	return this->x_plane_modifier;
}

int GODLandscapeControl::getYPlaneModifier() {
	return this->y_plane_modifier;
}

GODLandscapeObject* GODLandscapeControl::getLandscapeObject(int x, int y) {
	Utilities_GridLocation* grid = new Utilities_GridLocation(x,y);
	GODLandscapeObject* obj = getLandscapeObject(grid);
	if (grid) {
		delete grid;
		grid = NULL;
	}
	return obj;
}

GODLandscapeObject* GODLandscapeControl::getLandscapeObject(Utilities_GridLocation* grid) {
	if (!grid) {
		return NULL;
	}
	if (grid->getX() < 0 || grid->getX() >= width || grid->getY() < 0 || grid->getY() >= height) {
		return NULL;
	}
	return landscape[grid->getX()][grid->getY()];
}

/**
 * Override for existing objects, no check of existence
 */
void GODLandscapeControl::createLandscapeObject(Utilities_GridLocation* grid, GODItemObject* object) {
	if (grid->getX() >= width || grid->getY() >= height) {
		throw new GODException("ArrayIndexOutOfBoundsGODException","GODLandscapeControl::createLandscapeObject(Utilities_GridLocation* grid, GODItemObject* object)");
	}
	for (int i=0; i<(object->getSize()->getHeight()*object->getSize()->getWidth()); i++) {
		int x = (i/object->getSize()->getHeight());
		int y = (i%object->getSize()->getHeight());
		delete landscape[grid->getX()+x][grid->getY()+y];
		Utilities_GridLocation* currentGrid = new Utilities_GridLocation(grid->getX()+x, grid->getY()+y);
		landscape[grid->getX()+x][grid->getY()+y] = new GODLandscapeObject(currentGrid, object);
		if (GODMissionControl::getInstance()->isLoaded() && !GODMissionControl::getInstance()->getPathFinder()->createLandscapeObject(currentGrid))
			throw new GODException("LandscapeBlockingForPathFinder","GODLandscapeControl::createLandscapeObject(Utilities_GridLocation* grid, GODItemObject* object)");
	}
}

bool GODLandscapeControl::isOnField(Utilities_GridLocation* grid) {
	return !(grid->getX() >= width || grid->getY() >= height || grid->getX() < 0 || grid->getY() < 0);
}

bool GODLandscapeControl::isEmpty(int x, int y) {
	return isEmpty(new Utilities_GridLocation(x,y));
}

bool GODLandscapeControl::isEmpty(Utilities_GridLocation* grid, Utilities_Size* size, int ownerId, int boundary, bool waitOnLock) {
	if (!size)
		size = new Utilities_Size(1,1);
	if (!isOnField(grid)) {
		throw new GODException("ArrayIndexOutOfBoundsGODException","GODLandscapeControl::isEmpty(Utilities_GridLocation*, Utilities_Size*, int)");
	}
	for (int i=grid->getX(); i<grid->getX()+size->getWidth(); i++) {
		if (i >= width) {
			continue;
		}
		for (int j=grid->getY(); j<grid->getY()+size->getHeight(); j++) {
			if (j >= height) {
				continue;
			}
			while (landscape[i][j]->isLocked() && waitOnLock) {} // Busy Wait on lock
			if (landscape[i][j]->getGridKind() == GODLandscapeObject::LANDSCAPE_UNIT) {
				GODUnitObject* unitObject = (GODUnitObject*)(landscape[i][j]->getItem());
				if (ownerId == unitObject->getOwner() && boundary == GODLandscapeObject::LANDSCAPE_UNIT) {
					continue;
				} else if (ownerId != unitObject->getOwner() && boundary == GODLandscapeObject::LANDSCAPE_UNIT) {
					return false;
				}
			}
			if (landscape[i][j]->getGridKind() > boundary) {
				return false;
			}
		}
	}
	return true;
}

/**
 * Place unit on a single location based on the grid value in unit.
 * 
 * @param unit The unit to place
 */
void GODLandscapeControl::placeUnit(GODUnitObject* unit) {
	placeUnit(unit, unit->getLocation());
}

void GODLandscapeControl::cleanGhosts(GODUnitObject* unit) {
	Utilities_GridLocation* originalGrid = unit->getLocation();
	for (int i=0; i<((unit->getAttribute(GODUnitObject::WIDTH)+2)*(unit->getAttribute(GODUnitObject::HEIGHT)+2)); i++) {
		int x = ((i/(unit->getAttribute(GODUnitObject::HEIGHT)+2))+originalGrid->getX())-1;
		int y = ((i%(unit->getAttribute(GODUnitObject::HEIGHT)+2))+originalGrid->getY())-1;
		GODLandscapeObject* landscapeObject = getLandscapeObject(new Utilities_GridLocation(x, y));
		if (landscapeObject == NULL) {
			continue;
		}
		if (landscapeObject->getGridKind() == GODLandscapeObject::LANDSCAPE_GHOST && (landscapeObject->getItem() == NULL || landscapeObject->getItem()->getId() == unit->getId())) {
			landscapeObject->setGridKind(GODLandscapeObject::LANDSCAPE_EMPTY);
			landscapeObject->setItem(NULL);
		}
	}
}

void GODLandscapeControl::removeUnit(GODUnitObject* unit) {
	Utilities_GridLocation* originalGrid = unit->getLocation();
	for (int i=0; i<(unit->getAttribute(GODUnitObject::WIDTH)*unit->getAttribute(GODUnitObject::HEIGHT)); i++) {
		int x = (i/unit->getAttribute(GODUnitObject::HEIGHT))+originalGrid->getX();
		int y = (i%unit->getAttribute(GODUnitObject::HEIGHT))+originalGrid->getY();
		GODLandscapeObject* landscapeObject = getLandscapeObject(new Utilities_GridLocation(x, y));
		if (landscapeObject->getItem()->getId() == unit->getId()) {
			landscapeObject->setGridKind(GODLandscapeObject::LANDSCAPE_EMPTY);
			landscapeObject->setItem(NULL);
			if (unit->getOwner() == 1 && GODMissionControl::getInstance()->getPathFinder()->removeUnit(originalGrid))
				GODMissionControl::getInstance()->setPathBlocked(false);
		}
	}
	calculateTargetting(originalGrid, unit, NULL);
}

/**
 * Place a unit on a new grid location, this will actually *move* the unit if it
 * already exists somewhere on the map, and should be used for both new units as
 * existing units.
 * 
 * @param unit The unit to place
 * @param grid The grid on which the unit should be placed
 */
void GODLandscapeControl::placeUnit(GODUnitObject* unit, Utilities_GridLocation* grid) {
	Utilities_GridLocation* originalGrid = unit->getLocation();
	for (int i=0; i<(unit->getAttribute(GODUnitObject::WIDTH)*unit->getAttribute(GODUnitObject::HEIGHT)); i++) {
		int x = (i/unit->getAttribute(GODUnitObject::HEIGHT))+originalGrid->getX();
		int y = (i%unit->getAttribute(GODUnitObject::HEIGHT))+originalGrid->getY();
		GODLandscapeObject* landscapeObject = getLandscapeObject(new Utilities_GridLocation(x, y));
		
		landscapeObject->setGridKind(GODLandscapeObject::LANDSCAPE_GHOST);
	}
	for (int i=0; i<(unit->getAttribute(GODUnitObject::WIDTH)*unit->getAttribute(GODUnitObject::HEIGHT)); i++) {
		int x = (i/unit->getAttribute(GODUnitObject::HEIGHT))+grid->getX();
		int y = (i%unit->getAttribute(GODUnitObject::HEIGHT))+grid->getY();
		GODLandscapeObject* landscapeObject = getLandscapeObject(new Utilities_GridLocation(x, y));

		if (landscapeObject == NULL) {
			continue;
		}

		landscapeObject->setGridKind(GODLandscapeObject::LANDSCAPE_UNIT);
		landscapeObject->setItem(unit);
		if (unit->getOwner() == 1 && !GODMissionControl::getInstance()->getPathFinder()->placeUnit(grid))
			GODMissionControl::getInstance()->setPathBlocked(true);
	}
	if (unit->getAttribute(GODUnitObject::RANGE) > 0) {
		calculateUnitRanges(unit, grid, (originalGrid == NULL)? NULL : originalGrid);
	}

	calculateTargetting(originalGrid, unit, grid);

	unit->setLocation(grid);
}

bool GODLandscapeControl::isInRange(GODUnitObject* unit, GODLandscapeObject* object) {
	std::vector<GODUnitObject*> unitsInRange = object->getUnitRange();
	for (int i=0; i<(signed)unitsInRange.size(); i++) {
		GODUnitObject* targetUnit = unitsInRange.at(i);
		if (targetUnit->getId() == unit->getId()) {
			return true;
		}
	}
	return false;
}

void GODLandscapeControl::calculateTargetting(Utilities_GridLocation* object, GODUnitObject* unit, Utilities_GridLocation* newLandscapeObject) {
	int unitWidth = unit->getAttribute(GODUnitObject::WIDTH);
	int unitHeight = unit->getAttribute(GODUnitObject::HEIGHT);
	std::vector<GODUnitObject*> unitsInOriginalRange;
	std::vector<GODUnitObject*> unitsInNewRange;
	for (int i=0; i<unitWidth*unitHeight; i++) {
		int x = (i/height);
		int y = (i%height);
		GODLandscapeObject* originalRange = getLandscapeObject(new Utilities_GridLocation(x+object->getX(),y+object->getY()));
		if (originalRange != NULL) {
			std::vector<GODUnitObject*> originalRangeVector = originalRange->getUnitRange();
			unitsInOriginalRange.assign(originalRangeVector.begin(),originalRangeVector.end());
		}
		if (newLandscapeObject == NULL) {
			continue;
		}
		GODLandscapeObject* newRange = getLandscapeObject(new Utilities_GridLocation(x+newLandscapeObject->getX(),y+newLandscapeObject->getY()));
		if (newRange != NULL) {
			std::vector<GODUnitObject*> newRangeVector = newRange->getUnitRange();
			unitsInNewRange.assign(newRangeVector.begin(),newRangeVector.end());
		}
	}
	
	for (int i=0; i<(signed)unitsInOriginalRange.size(); i++) {
		GODUnitObject* targetUnit = unitsInOriginalRange.at(i);
		GODUnitObject* targettedUnit = targetUnit->getTarget();
		if (targettedUnit != NULL && targettedUnit->getId() == unit->getId()) {
			if (!vectorContainsUnit(unitsInNewRange, targetUnit->getId())) {
				targetUnit->setTarget(NULL);
			}
		}
	}

	if (newLandscapeObject == NULL) {
		return;
	}

	for (int i=0; i<(signed)unitsInNewRange.size(); i++) {
		GODUnitObject* targetUnit = unitsInNewRange.at(i);
		GODUnitObject* targettedUnit = targetUnit->getTarget();
		if (targettedUnit == NULL) {
			if (targetUnit->getId() != unit->getId() && targetUnit->getOwner()!= unit->getOwner()) {
				targetUnit->setTarget(unit);
			}
		}
	}
}

bool GODLandscapeControl::vectorContainsUnit(std::vector<GODUnitObject*> vector, int unitId) {
	for (int i=0; i<(signed)vector.size(); i++) {
		if (vector.at(i)->getId() == unitId) {
			return true;
		}
	}
	return false;
}

/**
 * TODO Units met een hoge unitSize
 */
void GODLandscapeControl::calculateUnitRanges(GODUnitObject* unit, Utilities_GridLocation* newGrid, Utilities_GridLocation* oldGrid) {
	if (newGrid == NULL) {
		throw new GODException("NoGridGODException","GODLandscapeControl::calculateUnitRanges(GODUnitObject* unit, Utilities_GridLocation* newGrid, Utilities_GridLocation* oldGrid)");
	}
	int range = unit->getAttribute(GODUnitObject::RANGE);
	int unitWidth = unit->getAttribute(GODUnitObject::WIDTH);
	int unitHeight = unit->getAttribute(GODUnitObject::HEIGHT);
	int width = (2*range)+unitWidth;
	int height = (2*range)+unitHeight;
	for (int i=0; i<width*height; i++) {
		int x = (i/height)-range;
		int y = (i%height)-range;
		if (x < -1) {
			if ((y < ((range*-1)-(x+1)) || y > ((range+unitHeight-1)-((x*-1)-1)))) {
				continue;
			}
		} else if (x > unitWidth) {
			if ((y < (((range+unitHeight-1)*-1)-((x*-1)+1)) || y > (unitHeight-1)+(range-(x-unitHeight)))) {
				continue;
			}
		}

		Utilities_GridLocation* newTempGrid = new Utilities_GridLocation(newGrid->getX()+x,newGrid->getY()+y);
		GODLandscapeObject* newLandscapeObject = getLandscapeObject(newTempGrid);

		if (oldGrid != NULL) {
			Utilities_GridLocation* oldTempGrid = new Utilities_GridLocation(oldGrid->getX()+x,oldGrid->getY()+y);

			GODLandscapeObject* oldLandscapeObject = getLandscapeObject(oldTempGrid);
			if (oldLandscapeObject != NULL) {
				oldLandscapeObject->removeUnitRange(unit);
			}
		}

		if (newLandscapeObject == NULL) {
			continue;
		}
		newLandscapeObject->addUnitRange(unit);
		// Quick Targetting
		if (unit->getTarget() == NULL) {
			GODItemObject* quickItem = newLandscapeObject->getItem();
			if (quickItem != NULL && quickItem->getItemType() == GODItemObject::ITEMTYPE_UNIT) {
				GODUnitObject* quickTarget = (GODUnitObject*)quickItem;
				if (quickTarget->getOwner()!= unit->getOwner()) {
					unit->setTarget(quickTarget);
				}
			}
		}
	}
}
