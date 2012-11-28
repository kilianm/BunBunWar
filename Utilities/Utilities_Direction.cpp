#include <bunbunwar/Utilities.h>

Utilities_Direction::Utilities_Direction(int x, int y) {
	Utilities_Direction::x = x;
	Utilities_Direction::y = y;
	recalculateDirection();
}

Utilities_Direction::~Utilities_Direction() {
	Utilities_Direction::x = 0;
	Utilities_Direction::y = 0;

}

int Utilities_Direction::getX() {
	return x;
}

int Utilities_Direction::getY() {
	return y;
}

void Utilities_Direction::setX(int x) {
	Utilities_Direction::x = x;
}

void Utilities_Direction::setY(int y) {
	Utilities_Direction::y = y;
}

bool Utilities_Direction::isHorizontal() {
	return horizontal;
}

bool Utilities_Direction::isVertical() {
	return vertical;
}

bool Utilities_Direction::isDiagonal() {
	return diagonal;
}

void Utilities_Direction::switchDirectionClockwise() {
	if (x == 0) {
		if (y == -1) x++;
		else x--;
	} else if (x == 1) {
		y++;
		if (y > 1) {
			y = 1;
			x--;
		}
	} else if (x == -1) {
		y--;
		if (y < -1) {
			y = -1;
			x++;
		}
	}
	recalculateDirection();
}

void Utilities_Direction::switchDirectionCounterClockwise() {
	if (x == 0) {
		if (y == -1) x--;
		else x++;
	} else if (x == 1) {
		y--;
		if (y < -1) {
			y = -1;
			x--;
		}
	} else if (x == -1) {
		y++;
		if (y > 1) {
			y = 1;
			x++;
		}
	}
	recalculateDirection();
}

void Utilities_Direction::recalculateDirection() {
	if (x != 0 && y != 0 ) {
		Utilities_Direction::diagonal = true;
		Utilities_Direction::vertical = false;
		Utilities_Direction::horizontal = false;
	} else if (x != 0 && y == 0) {
		Utilities_Direction::horizontal = true;
		Utilities_Direction::diagonal = false;
		Utilities_Direction::vertical = false;
	} else if (x == 0 && y != 0) {
		Utilities_Direction::vertical = true;
		Utilities_Direction::diagonal = false;
		Utilities_Direction::horizontal = false;
	}
}

Utilities_GridLocation* Utilities_Direction::getRecalculatedGridLocation(Utilities_GridLocation* grid) {
	return new Utilities_GridLocation(grid->getX()+x, grid->getY()+y);
}