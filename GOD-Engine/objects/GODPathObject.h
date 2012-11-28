#ifndef GODPATHOBJECT_H
#define GODPATHOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

class DLLEXPORT GODPathObject {
public:
	GODPathObject(Utilities_GridLocation* startLocation, Utilities_GridLocation* endLocation);
	~GODPathObject();

	void setStartLocation(Utilities_GridLocation* startLocation);
	Utilities_GridLocation* getStartLocation();
	void setEndLocation(Utilities_GridLocation* endLocation);
	Utilities_GridLocation* getEndLocation();

	void setPreviousMove(Utilities_GridLocation* previousMove);
	Utilities_GridLocation* getPreviousMove();

	void setDirection(Utilities_Direction* direction);
	Utilities_Direction* getDirection();

	void setLastMovementTime(long lastMovementTime);
	long getLastMovementTime();
private:
	Utilities_GridLocation* startLocation;
	Utilities_GridLocation* endLocation;
	Utilities_GridLocation* previousMove;
	Utilities_Direction* direction;
	long lastMovementTime;
};

#endif