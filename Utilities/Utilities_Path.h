#ifndef UTILITIES_PATH_H
#define UTILITIES_PATH_H

#include <bunbunwar/stdafx.h>

class DLLEXPORT Utilities_Path {
public:
	Utilities_Path(Utilities_GridLocation* start, int width, int height);
	~Utilities_Path();

	bool addStep(Utilities_GridLocation* step, Utilities_PathNode* behindNode = NULL, Utilities_PathNode* inFrontNode = NULL);
	bool removeLastStep();
	Utilities_PathNode* getPath(Utilities_GridLocation* location, int offset = 0);
	bool inPath(Utilities_GridLocation* location, int offset = 0);
	bool isValidStep(Utilities_GridLocation* step);
	Utilities_GridLocation* getFirstStep();
	Utilities_GridLocation* getLastStep();
	Utilities_PathNode* getFirstStepNode();
	Utilities_PathNode* getLastStepNode();
	Utilities_PathNode* getClosestNode(Utilities_GridLocation* location);
	bool createIntersect(Utilities_GridLocation* intersect);
	Utilities_PathNode* findFirstEndNode();
	Utilities_PathNode* findLastEndNode();
	Utilities_GridLocation* findFirstEnd();
	Utilities_GridLocation* findLastEnd();
	bool addPathFix(Utilities_Path* pathFix);
	void addPath(Utilities_Path* path);
	bool isBroken();
	void reverse();
	int getWidth();
	int getHeight();

private:
	int width;
	int height;
	Utilities_PathNode*** grid;
	Utilities_PathNode* lastStep;
	Utilities_PathNode* firstStep;
	Utilities_PathNode* firstEndCache;
	Utilities_PathNode* lastEndCache;

	Utilities_PathNode* getGrid(Utilities_GridLocation* loc);
	void setGrid(Utilities_GridLocation* loc, Utilities_PathNode* node);
	bool inGridRange(Utilities_GridLocation* location);
	bool addPathNode(Utilities_PathNode* pathNode,  bool first = false);
	void clearCache();
};

#endif