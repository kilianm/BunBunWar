#ifndef OGREUNIT_H
#define OGREUNIT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/Utilities.h>
#include <bunbunwar/GODEngine.h>
#include <bunbunwar/OgreGODEngine.h>
#include <ogre/Ogre.h>

using namespace Ogre;

class DLLEXPORT OgreUnit : public GODUnitObject {
public:
	OgreUnit();
	OgreUnit(int id, int owner, GODUnitTypeObject* unitType);
	OgreUnit(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* path);
	OgreUnit(int id, int owner, GODUnitTypeObject* unitType, Utilities_GridLocation* grid);
	~OgreUnit();

	void setChildId(std::string childId);
	std::string getChildId();

	void setInitValues();

	void create(SceneManager* mSceneMgr);
	void draw(SceneManager* mSceneMgr, long pause);

	Entity* getEntity();
	SceneNode* getNode();
	void reset(SceneManager* mSceneMgr);

	bool isCreated();
private:
	std::string childId;
	Entity *ent;
	SceneNode *node;
	ObjectTextDisplay* text;

	SceneManager* mSceneMgr;

	bool created;
};

#endif