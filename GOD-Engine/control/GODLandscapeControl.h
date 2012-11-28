#ifndef GODLANDSCAPECONTROL_H
#define GODLANDSCAPECONTROL_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../objects/GODObjects.h"
#include "../xml/GODXML.h"

class DLLEXPORT GODLandscapeControl : public GODXMLObjectParser {
public:
	const static int LANDSCAPE_GRID_MODIFIER = 50;
	const static int LANDSCAPE_GRID_QUERY_FLAG = 1<<0;
	static std::string XML_OBJECT_NAME;

	GODLandscapeControl();
	GODLandscapeControl(int x, int y);
	~GODLandscapeControl();

	void loadLandscape();
	GODLandscapeObject* getLandscapeObject(int x, int y);
	GODLandscapeObject* getLandscapeObject(Utilities_GridLocation* grid);
	void createLandscapeObject(Utilities_GridLocation* grid, GODItemObject* object);
	bool isOnField(Utilities_GridLocation* grid);
	bool isEmpty(int x, int y);
	bool isEmpty(Utilities_GridLocation* grid, Utilities_Size* size = NULL, int ownerId = 0, int boundary = 0, bool waitOnLock = false);

	void cleanGhosts(GODUnitObject* unit);
	void removeUnit(GODUnitObject* unit);
	void placeUnit(GODUnitObject* unit);
	void placeUnit(GODUnitObject* unit, Utilities_GridLocation* grid);
	bool isInRange(GODUnitObject* unit, GODLandscapeObject* object);

	int getWidth();
	int getHeight();

	void setModifier(int modifier);
	int getModifier();
	int getXPlaneModifier();
	int getYPlaneModifier();

	GODLandscapeAreaObject* getStart();
	void setStart(GODLandscapeAreaObject* start);

	GODLandscapeAreaObject* getFinish();
	void setFinish(GODLandscapeAreaObject* finish);

	void printMapToSystem();

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	void calculateTargetting(Utilities_GridLocation* object, GODUnitObject* unit, Utilities_GridLocation* newLandscapeObject);
	void calculateUnitRanges(GODUnitObject* unit, Utilities_GridLocation* originalGrid, Utilities_GridLocation* newLandscapeObject);
	bool vectorContainsUnit(std::vector<GODUnitObject*> vector, int unitId);

	int x_plane_modifier;
	int y_plane_modifier;
	int modifier;
	
	GODLandscapeAreaObject* start;
	GODLandscapeAreaObject* finish;
	GODLandscapeObject*** landscape;
	int width;
	int height;
	bool locked;
};

#endif