#include <bunbunwar/Utilities.h>

Utilities_Path::Utilities_Path(Utilities_GridLocation* start, int width, int height) {
	this->width = width;
	this->height = height;
	this->grid = new Utilities_PathNode**[this->width];
	for (int i=0; i<this->width; i++) {
		this->grid[i] = new Utilities_PathNode*[this->height];
	}
	for (int i=0; i<this->width; i++) {
		for (int j=0; j<this->height; j++) {
			this->grid[i][j] = NULL;
		}
	}
	this->firstStep = new Utilities_PathNode(start);
	setGrid(start, this->firstStep);
	this->lastStep = NULL;
	this->firstEndCache = NULL;
	this->lastEndCache = NULL;
}

Utilities_Path::~Utilities_Path() {
	for (int i=0; i<this->width; i++) {
		for (int j=0; j<this->height; j++) {
			delete this->grid[i][j];
		}
		delete [] this->grid[i];
	}
	delete [] this->grid;
	this->lastStep = NULL;
	this->firstStep = NULL;
	this->firstEndCache = NULL;
	this->lastEndCache = NULL;
}

bool Utilities_Path::addStep(Utilities_GridLocation* step, Utilities_PathNode* behindNode, Utilities_PathNode* inFrontNode){
	if(!isValidStep(step))
		return false;
	if (!behindNode)
		behindNode = this->lastStep;
	if (!behindNode)
		behindNode = this->firstStep;
	Utilities_PathNode* stepNode = new Utilities_PathNode(step, behindNode, inFrontNode);
	stepNode->getBehindNode()->setInFrontNode(stepNode);
	setGrid(step, stepNode);
	this->lastStep = stepNode;
	return true;
}

bool Utilities_Path::isValidStep(Utilities_GridLocation* step) {
	Utilities_PathNode* node = this->lastStep;
	if (!node)
		node = this->firstStep;
	int xDiff = node->getLocation()->getX() - step->getX();
	int yDiff = node->getLocation()->getY() - step->getY();
	if (!(xDiff >= 1 || xDiff <= 1 || yDiff >= -1 || yDiff <= -1 || xDiff == 0 || yDiff == 0))
		return false;
	return !inPath(step);
}

bool Utilities_Path::removeLastStep() {
	if (!this->lastStep) 
		return false;
	Utilities_PathNode* oldLastStep = this->lastStep;
	this->lastStep = oldLastStep->getBehindNode();
	setGrid(oldLastStep->getLocation(), NULL);
	return true;
}

Utilities_PathNode* Utilities_Path::getGrid(Utilities_GridLocation* loc) {
	return this->grid[loc->getX()][loc->getY()];
}

void Utilities_Path::setGrid(Utilities_GridLocation* loc, Utilities_PathNode* node) {
	this->grid[loc->getX()][loc->getY()] = node;
	clearCache();
}

Utilities_PathNode* Utilities_Path::getPath(Utilities_GridLocation* location, int offset) {
	if (inGridRange(location)) {
		Utilities_PathNode* node = getGrid(location);
		if (node)
			return node;
	}
	if (offset == 0)
		return NULL;

	Utilities_GridLocation* testLoc = NULL;
	for (int y=offset; y>=offset; y--) {
		if (y == 0)
			y--; 
		testLoc = new Utilities_GridLocation(location->getX(), location->getY()+y);
		if (inGridRange(testLoc)) {
			Utilities_PathNode* node = getGrid(testLoc);
			if (node)
				return node;
		}
	}
	for (int x=~offset; x<=offset; x++) {
		if (x == 0)
			x++; 
		testLoc = new Utilities_GridLocation(location->getX()+x, location->getY());
		if (inGridRange(testLoc)) {
			Utilities_PathNode* node = getGrid(testLoc);
			if (node)
				return node;
		}
	}
	for (int y=offset; y>=offset; y--) {
		if (y == 0)
			y--; 
		for (int x=~offset; x<=offset; x++) {
			if (x == 0)
				x++; 
			testLoc = new Utilities_GridLocation(location->getX()+x, location->getY()+y);
			if (inGridRange(testLoc)) {
				Utilities_PathNode* node = getGrid(testLoc);
				if (node)
					return node;
			}
		}
	}
	return NULL;
}

bool Utilities_Path::inPath(Utilities_GridLocation* location, int offset) {
	return (getPath(location, offset) != NULL);
}

bool Utilities_Path::inGridRange(Utilities_GridLocation* location) {
	if (!location)
		return false;
	return !(location->getX() < 0 || location->getX() >= this->width || location->getY() < 0 || location->getY() >= this->height);
}

Utilities_GridLocation* Utilities_Path::getFirstStep() {
	if (!this->firstStep)
		return NULL;
	return this->firstStep->getLocation();
}

Utilities_GridLocation* Utilities_Path::getLastStep() {
	if (!this->lastStep)
		return NULL;
	return this->lastStep->getLocation();
}

Utilities_PathNode* Utilities_Path::getFirstStepNode() {
	return this->firstStep;
}

Utilities_PathNode* Utilities_Path::getLastStepNode() {
	return this->lastStep;
}

Utilities_PathNode* Utilities_Path::getClosestNode(Utilities_GridLocation* location) {
	Utilities_PathNode* foundNode = NULL;
	int scope = 0;
	do {
		if (scope > this->width && scope > this->height)
			break;
		foundNode = getPath(location, scope);
		scope++;
	} while (!foundNode);
	return foundNode;
}

bool Utilities_Path::createIntersect(Utilities_GridLocation* intersect) {
	if (intersect->equals(this->lastStep->getLocation()) || 
		intersect->equals(this->firstStep->getLocation()))
		return false;
	if (!inPath(intersect)) 
		return false;
	Utilities_PathNode* node = this->firstStep;
	while (node->getInFrontNode()) {
		node->getInFrontNode()->setBehindNode(node);
		setGrid(node->getLocation(), node);
        node = node->getInFrontNode();
	}
	this->lastStep = node;
	Utilities_PathNode* intersectNode = getGrid(intersect);
	Utilities_PathNode* behindNode = getGrid(intersectNode->getBehindNode()->getLocation());
	Utilities_PathNode* inFrontNode = getGrid(intersectNode->getInFrontNode()->getLocation());
	behindNode->setInFrontNode(NULL);
	inFrontNode->setBehindNode(NULL);
	setGrid(behindNode->getLocation(), behindNode);
	setGrid(inFrontNode->getLocation(), inFrontNode);
	setGrid(intersect, NULL);
	return true;
}

Utilities_PathNode* Utilities_Path::findFirstEndNode() {
	if (this->firstEndCache)
		return this->firstEndCache;
	Utilities_PathNode* node = this->firstStep;
	while (node->getInFrontNode()) {
		node = node->getInFrontNode();
	}
	this->firstEndCache = node;
	return node;
}

Utilities_GridLocation* Utilities_Path::findFirstEnd() {
	Utilities_PathNode* node = findFirstEndNode();
	if (node)
		return node->getLocation();
	return NULL;
}

Utilities_PathNode* Utilities_Path::findLastEndNode() {
	if (this->lastEndCache)
		return this->lastEndCache;
	Utilities_PathNode* node = this->lastStep;
	while (node->getBehindNode()) {
		node = node->getBehindNode();
	}
	this->lastEndCache = node;
	return node;
}

Utilities_GridLocation* Utilities_Path::findLastEnd() {
	Utilities_PathNode* node = findLastEndNode();
	if (node)
		return node->getLocation();
	return NULL;
}

bool Utilities_Path::addPathFix(Utilities_Path* pathFix) {
	bool result = false;
	if (this->findLastEnd()->equals(pathFix->getFirstStep()) &&
		this->findFirstEnd()->equals(pathFix->getLastStep())) {
		pathFix->reverse();
	}
	if (this->findFirstEnd()->equals(pathFix->getFirstStep()) &&
		this->findLastEnd()->equals(pathFix->getLastStep())) {
		addPath(pathFix);
		result = true;
	}
//	delete pathFix;
	return result;
}
	
void Utilities_Path::addPath(Utilities_Path* path) {
	Utilities_PathNode* node = path->getFirstStepNode();
	Utilities_PathNode* lastNode = findFirstEndNode();
	Utilities_PathNode* beforeNode = lastNode;
	while (beforeNode->getBehindNode()) {
		beforeNode = beforeNode->getBehindNode();
		Utilities_PathNode* pathNode = path->getPath(beforeNode->getLocation());
		if (pathNode) {
			node = pathNode;
			lastNode = beforeNode;
			setGrid(beforeNode->getInFrontNode()->getLocation(), NULL);
			beforeNode->setInFrontNode(NULL);
		}

	}
	if (node->getLocation()->equals(lastNode->getLocation())) {
		Utilities_PathNode* beforeLastNode = lastNode->getBehindNode();
		if (beforeLastNode) {
			beforeLastNode->setInFrontNode(node);
			node->setBehindNode(beforeLastNode);
		}
		setGrid(node->getLocation(), node);
		Utilities_PathNode* firstNode = node;
		while (firstNode->getBehindNode()) {
			firstNode = firstNode->getBehindNode();
			setGrid(firstNode->getLocation(), firstNode);
		}
		this->firstStep = firstNode;
	} else {
		addPathNode(lastNode, true);
	}
	Utilities_PathNode* endNode = node;
	do {
		endNode = endNode->getInFrontNode();
		if (addPathNode(endNode))
			break;
	} while (endNode->getInFrontNode());
}

bool Utilities_Path::addPathNode(Utilities_PathNode* pathNode, bool first) {
	Utilities_PathNode* existingNode = getGrid(pathNode->getLocation());
	if (!first && existingNode) {
		Utilities_PathNode* behindNode = existingNode;
		while (behindNode && behindNode->getBehindNode()) {
			behindNode = behindNode->getBehindNode();
			setGrid(behindNode->getLocation(), NULL);
		}
		Utilities_PathNode* firstValidNode = existingNode->getInFrontNode();
		pathNode->setInFrontNode(firstValidNode);
		firstValidNode->setBehindNode(pathNode);
		setGrid(pathNode->getLocation(), pathNode);
		Utilities_PathNode* endNode = pathNode;
		do {
			endNode = endNode->getInFrontNode();
			setGrid(endNode->getLocation(), endNode);
		} while (endNode->getInFrontNode());
		this->lastStep = endNode;
		return true;
	} else {
		this->addStep(pathNode->getLocation(), pathNode->getBehindNode(), pathNode->getInFrontNode());
		return false;
	}
	return false;
}

void Utilities_Path::reverse() {
	Utilities_PathNode* oldFirstStep = this->firstStep;
	Utilities_PathNode* oldLastStep = this->lastStep;
	this->firstStep = oldLastStep;
	this->lastStep = oldFirstStep;

	Utilities_PathNode* node = this->lastStep;
	node->reverse();
	while (node->getBehindNode()) {
		node = node->getBehindNode();
		node->reverse();
	}
}

bool Utilities_Path::isBroken() {
	if (findFirstEnd()->equals(lastStep->getLocation()) && findLastEnd()->equals(firstStep->getLocation()))
		return false;
	return true;
}

void Utilities_Path::clearCache() {
	this->firstEndCache = NULL;
	this->lastEndCache = NULL;
}

int Utilities_Path::getWidth(){
	return this->width;
}

int Utilities_Path::getHeight(){
	return this->height;
}