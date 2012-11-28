#include "GODPathFinder.h"

void GODPathFinder::setLandscapeControl(GODLandscapeControl* landscapeControl) {
	this->landscapeControl = landscapeControl;
}

GODLandscapeControl* GODPathFinder::getLandscapeControl() {
	return this->landscapeControl;
}
