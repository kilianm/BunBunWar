#include <bunbunwar/Utilities.h>

Utilities_GridLocation::Utilities_GridLocation() {}
Utilities_GridLocation::Utilities_GridLocation(int x, int y) {
	this->x = x;
	this->y = y;
}

Utilities_GridLocation::~Utilities_GridLocation() {
	this->x = 0;
	this->y = 0;
}

int Utilities_GridLocation::getX() {
	return x;
}

int Utilities_GridLocation::getY() {
	return y;
}

void Utilities_GridLocation::setX(int x) {
	this->x = x;
}

void Utilities_GridLocation::setY(int y) {
	this->y = y;
}

bool Utilities_GridLocation::equals(Utilities_GridLocation* grid) {
	if (grid == NULL) {
		return false;
	}
	return (grid->getX() == x && grid->getY() == y);
}
