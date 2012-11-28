#ifndef GODASSAULTPATHFINDER_H
#define GODASSAULTPATHFINDER_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

#include "GODPathFinder.h"

class DLLEXPORT GODAssaultPathFinder: public GODPathFinder {
public:
	GODAssaultPathFinder();
	~GODAssaultPathFinder();

	bool createLandscapeObject(Utilities_GridLocation* location);
	bool placeUnit(Utilities_GridLocation* location);
	bool removeUnit(Utilities_GridLocation* location);
	bool moveUnit(GODUnitObject* unit);
protected:
private:
	int calculateRouteValue(GODLandscapeObject* lanscapeObject, Utilities_GridLocation* endLocation);
	int calculateRouteValue(Utilities_GridLocation* grid, Utilities_GridLocation* endLocation);
	int calculateSingleValue(int current, int final);
	Utilities_GridLocation* calculateBestMove(GODUnitObject* unit, GODLandscapeObject* start, Utilities_Direction* direction, int level, Utilities_GridLocation* endLocation, int* value);
};
#endif