#ifndef GODUNITOBJECT_H
#define GODUNITOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

#include "GODObjects.h"

class DLLEXPORT GODUnitObject: public GODItemObject {
public:
	static const int HEALTH = 1;
	static const int MOVEMENT = 2;
	static const int ATTACKPOWER = 3;
	static const int ARMOR = 4;
	static const int ATTACKSPEED = 5;
	static const int RANGE = 6;
	static const int MISSRATE = 7;
	static const int CRITRATE = 8;
	static const int WIDTH = 9;
	static const int HEIGHT = 10;
	static const int PRICE = 11;

	GODUnitObject();
	GODUnitObject(int id, int owner, GODUnitTypeObject* unitType);
	GODUnitObject(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* path);
	GODUnitObject(int id, int owner, GODUnitTypeObject* unitType, Utilities_GridLocation* location);
	virtual ~GODUnitObject();

	int getItemType();

	// Getters & Setters
	GODUnitTypeObject* getUnitType();
	void setUnitType(GODUnitTypeObject* unitType);
	GODUnitModifierObject* getUnitModifier();
	void setUnitModifier(GODUnitModifierObject* unitModifier);
	int getOwner();
	void setOwner(int owner);

	long getLastAttack();
	void setLastAttack(long lastAttack);

	bool isDead();
	bool canUpgrade();
	void setUpgrade(bool upgrade);

	GODUnitObject* getTarget();
	void setTarget(GODUnitObject* target);

	bool isUsed();
	void setUsed(bool used);

	void modifyAttribute(int attribute, int value);
	int getAttribute(int attribute);

	Utilities_GridLocation* getLocation();
	void setLocation(Utilities_GridLocation* location);

	GODPathObject* getGODPath();
	void setGODPath(GODPathObject* GODPath);

	Utilities_Path* getPath();
	void setPath(Utilities_Path* path);
	void resetPath();

	void moveUnit(Utilities_GridLocation* oldLocation, Utilities_GridLocation* newLocation, int time, long modifier, long xPlaneModifier, long yPlaneModifier);
	void restUnit();

	void addTimeSinceLastMove(float timeSinceLastMove);
	void fixTiming(long pause);
	float getX();
	float getY();

	void setRotate(int rotate);
	float getRotate();

	void setDamage(int damage);
	int getDamage();
	bool hasDamage();

	bool isFinished();
	bool equals(GODUnitObject* unit);

	int getObjectType();

	Utilities_GridLocation* getNextLocation();
protected:
	Utilities_GridLocation* location;
	GODPathObject* GODPath;
	Utilities_Path* path;
private:
	GODUnitTypeObject* unitType;
	GODUnitModifierObject* unitModifier;
	int owner;
	bool used;
	long lastAttack;
	GODUnitObject* target;

	int damage;
	float timeForDamageSet;

	float xTotal;
	float xLeft;
	float yTotal;
	float yLeft;

	float rotate;

	bool finished;
	bool dead;
	bool upgrade;

	float timeLastMove;
	float timeForMovement;
	float timeSinceLastMove;

	int getRotation(Utilities_GridLocation* grid1, Utilities_GridLocation* grid2);
};

#endif
