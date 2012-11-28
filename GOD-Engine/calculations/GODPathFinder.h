#ifndef GODPATHFINDER_H
#define GODPATHFINDER_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../control/GODLandscapeControl.h"
#include "../control/GODEvents.h"

class DLLEXPORT GODPathFinder {
public:
	virtual void setLandscapeControl(GODLandscapeControl* landscapeControl);
	virtual GODLandscapeControl* getLandscapeControl();
	virtual bool createLandscapeObject(Utilities_GridLocation* location)=0;
	virtual bool placeUnit(Utilities_GridLocation* location)=0;
	virtual bool removeUnit(Utilities_GridLocation* location)=0;
	virtual bool moveUnit(GODUnitObject* unit)=0;
protected:
	GODLandscapeControl* landscapeControl; 
};

#endif