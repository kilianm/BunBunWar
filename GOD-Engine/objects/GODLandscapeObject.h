#ifndef GODLANDSCAPEOBJECT_H
#define GODLANDSCAPEOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

class DLLEXPORT GODLandscapeObject {
public:
	const static int LANDSCAPE_GHOST = -1;
	const static int LANDSCAPE_EMPTY = 0;
	const static int LANDSCAPE_UNIT = 1;
	const static int LANDSCAPE_BLOCKED = 2;

	GODLandscapeObject(Utilities_GridLocation* location);
	GODLandscapeObject(Utilities_GridLocation* location, GODItemObject* item);
	~GODLandscapeObject();

	Utilities_GridLocation* getLocation();
	void setLocation(Utilities_GridLocation* location);
	GODItemObject* getItem();
	void setItem(GODItemObject* item);
	int getGridKind();
	void setGridKind(int gridKind);

	bool isLocked();
	void setLocked(bool locked);

	void addUnitRange(GODUnitObject* unit);
	void removeUnitRange(GODUnitObject* unit);
	std::vector<GODUnitObject*> getUnitRange();

	void increasePunishment();
	void decreasePunishment();
	int getPunishment();
protected:
	template class DLLEXPORT std::allocator<GODUnitObject*>;
	template class DLLEXPORT std::vector<GODUnitObject*, std::allocator<GODUnitObject*> >;
private:
	Utilities_GridLocation* location;
	std::vector<GODUnitObject*> unitRange;
	GODItemObject* item;
	int gridKind;
	int punishment;
	bool locked;
};

#endif