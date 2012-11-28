#ifndef GODTOWERDEFENSEPATHFINDER_H
#define GODTOWERDEFENSEPATHFINDER_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

#include "GODPathFinder.h"

class DLLEXPORT GODTowerDefensePathFinder: public GODPathFinder {
public:
	GODTowerDefensePathFinder();
	~GODTowerDefensePathFinder();

	void setLandscapeControl(GODLandscapeControl* landscapeControl);
	bool createLandscapeObject(Utilities_GridLocation* location);
	bool placeUnit(Utilities_GridLocation* location);
	bool removeUnit(Utilities_GridLocation* location);
	bool moveUnit(GODUnitObject* unit);
protected:
private:
	const static int SAFEZONE_OFFSET = 2;
	const static int pathDirection_N = 1;
	const static int pathDirection_NE = 2; 
	const static int pathDirection_E = 3;
	const static int pathDirection_SE = 4;
	const static int pathDirection_S = 5;
	const static int pathDirection_SW = 6;
	const static int pathDirection_W = 7;
	const static int pathDirection_NW = 8;

	Utilities_Path* baselinePath;    

	void initBaseline();
	void calculateBaseline();
	bool fixBaseline(Utilities_GridLocation* intersectionPoint = NULL);
	Utilities_Path* fixIntersectedPath(Utilities_GridLocation* startPoint, Utilities_GridLocation* endPoint, int intersectDirection);
	Utilities_GridLocation* findNextStep(Utilities_Path* path, int* favoredDirection, bool clockWise);
	int getNextDirection(int direction, bool clockWise, int steps = 1);
	int getRandomDirection(int direction, int discloseDir1 = 0, int discloseDir2 = 0);
	Utilities_GridLocation* getDirectionLocation(Utilities_GridLocation* oldPos, int direction);
	int getLocationDirection(Utilities_GridLocation* fromPos, Utilities_GridLocation* toPos);
	bool isDiagonal(int direction);
	int getClosestBaselineDirection(GODUnitObject* unit);
	Utilities_GridLocation* calculateUnitMove(GODUnitObject* unit, int defaultDirection, bool checkNextMove = true);
	bool moveBaselineUnit(GODUnitObject* unit);
	bool moveLostUnit(GODUnitObject* unit);
	void moveUnit(GODUnitObject* unit, Utilities_GridLocation* newPos);
	bool isValidMove(Utilities_GridLocation* newPos, bool checkBaseLineOffset = true);
	bool isValidMove(Utilities_GridLocation* oldPos, Utilities_GridLocation* newPos, bool checkBaseLineOffset = true, bool allowDiagonal = true);
};
#endif