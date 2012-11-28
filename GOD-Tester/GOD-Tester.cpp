// GOD-Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <bunbunwar/GODEngine.h>
#include <bunbunwar/Utilities.h>

int _tmain(int argc, _TCHAR* argv[])
{
	GODUnitTypeObject* type = new GODUnitTypeObject();
	type->setAttackPower(100);
	type->setHealth(500);
	type->setArmor(400);
	type->setCritRate(5);
	type->setMissRate(5);
	type->setAttackSpeed(1800);
	type->setRange(3);
	type->setMovement(1);

	Utilities_GridLocation* start = new Utilities_GridLocation(5, 0);
	Utilities_GridLocation* end = new Utilities_GridLocation(5, 9);
	GODPathObject* path = new GODPathObject(start, end);

	GODUnitObject* unit = new GODUnitObject(2, 0, type, path);
	unit->setSize(new Utilities_Size(1,1));

	//Control
	GODUnitTypeControl* unitTypeControl = new GODUnitTypeControl();
	unitTypeControl->addUnitType(type);
	GODUnitControl* unitControl = new GODUnitControl();
	unitControl->addUnit(unit);
	GODLandscapeControl* landscapeControl = new GODLandscapeControl(10,30);
	landscapeControl->placeUnit(unit);

	GODMissionControl* missionControl = GODMissionControl::getInstance();
	missionControl->setUnitControl(unitControl);
	missionControl->setLandscapeControl(landscapeControl);
	missionControl->setUnitTypeControl(unitTypeControl);

	GODItemObject* item1 = new GODItemObject();
	item1->setSize(new Utilities_Size(2,2));
	landscapeControl->createLandscapeObject(new Utilities_GridLocation(4,15),item1);
	GODItemObject* item2 = new GODItemObject();
	item2->setSize(new Utilities_Size(2,2));
	landscapeControl->createLandscapeObject(new Utilities_GridLocation(6,15),item2);
	GODItemObject* item3 = new GODItemObject();
	item3->setSize(new Utilities_Size(2,2));
	landscapeControl->createLandscapeObject(new Utilities_GridLocation(8,15),item3);
	GODItemObject* item4 = new GODItemObject();
	item4->setSize(new Utilities_Size(1,1));
	landscapeControl->createLandscapeObject(new Utilities_GridLocation(4,10),item4);
	GODItemObject* item5 = new GODItemObject();
	item5->setSize(new Utilities_Size(1,1));
	landscapeControl->createLandscapeObject(new Utilities_GridLocation(7,10),item5);

	//landscapeControl->printMapToSystem();

	while (!unit->getGrid()->equals(end)) {
	//for (int i=0; i<100; i++) {
		printf("Move From (%i,%i)",unit->getGrid()->getX(), unit->getGrid()->getY());
		GODPathFinder::getInstance()->moveUnit(landscapeControl, unit);
		printf(" To (%i,%i)\n",unit->getGrid()->getX(), unit->getGrid()->getY());
	}

	//landscapeControl->calculateUnitRanges(own, NULL, NULL);

	/*GODMissionControl* missionControl = new GODMissionControl();
	missionControl->newMission("");

	for (int i=0; i<100; i++) {
		GODUnitObject* own = new GODUnitObject(i, i%2, type);
		missionControl->addUnit(own);
		own->modifyAttribute(GODUnitObject::HEALTH, rand()%500);
		own->modifyAttribute(GODUnitObject::ARMOR, rand()%400);
		own->modifyAttribute(GODUnitObject::CRITRATE, rand()%5);
		own->modifyAttribute(GODUnitObject::MISSRATE, rand()%5);
		own->modifyAttribute(GODUnitObject::ATTACKPOWER, rand()%100);
		own->modifyAttribute(GODUnitObject::ATTACKSPEED, (rand()%900)*-1);
	}

	missionControl->mission();*/

	system("PAUSE");

	//delete type;
	//delete landscapeControl;
	//delete path;
	//delete unit;
	//delete missionControl;

	return 0;
}
