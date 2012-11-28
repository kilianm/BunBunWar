#ifndef UTILITIES_DIRECTION_H
#define UTILITIES_DIRECTION_H

#include <bunbunwar/stdafx.h>

class DLLEXPORT Utilities_Direction {
public:
	Utilities_Direction();
	Utilities_Direction(int x, int y);
	~Utilities_Direction();

	// Getters & Setters
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	bool isHorizontal();
	bool isVertical();
	bool isDiagonal();

	void recalculateDirection();

	void switchDirectionClockwise();
	void switchDirectionCounterClockwise();

	Utilities_GridLocation* getRecalculatedGridLocation(Utilities_GridLocation* grid);
private:
	int x;
	int y;
	bool horizontal;
	bool vertical;
	bool diagonal;
};

#endif