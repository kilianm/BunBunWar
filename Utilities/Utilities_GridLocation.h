#ifndef UTILITIES_GRIDLOCATION_H
#define UTILITIES_GRIDLOCATION_H

#include <bunbunwar/stdafx.h>

class DLLEXPORT Utilities_GridLocation {
public:
	Utilities_GridLocation();
	Utilities_GridLocation(int x, int y);
	~Utilities_GridLocation();

	// Getters & Setters
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	bool equals(Utilities_GridLocation* grid);
private:
	int x;
	int y;
};

#endif