#ifndef GODARROWOBJECT_H
#define GODARROWOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <bunbunwar/Utilities.h>
#include "GODObjects.h"

class DLLEXPORT GODArrowObject : public GODObject {
public:
	GODArrowObject(int id, Utilities_GridLocation* source, Utilities_GridLocation* target);
	virtual ~GODArrowObject();

	int getId();
	int getObjectType();
	Utilities_GridLocation* getSource();
	Utilities_GridLocation* getTarget();

	void moveArrow(long modifier, long xPlaneModifier, long yPlaneModifier);
	void fixTiming(long pause);
	void addTimeSinceLastMove(float timeLastMove);
	float getX();
	float getY();

	bool isFinished();
protected:
	int id;
	Utilities_GridLocation* source;
	Utilities_GridLocation* target;
private:
	float xTotal;
	float xLeft;
	float yTotal;
	float yLeft;

	float rotate;

	float timeLastMove;
	float timeForMovement;
	float timeSinceLastMove;

	bool finished;
};

#endif