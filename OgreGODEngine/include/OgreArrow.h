#ifndef OGREARROW_H
#define OGREARROW_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/Utilities.h>
#include <bunbunwar/GODEngine.h>
#include <bunbunwar/OgreGODEngine.h>
#include <ogre/Ogre.h>

class DLLEXPORT OgreArrow : public GODArrowObject {
public:
	OgreArrow(int id, Utilities_GridLocation* source, Utilities_GridLocation* target);
	~OgreArrow();

	void setChildId(std::string childId);
	std::string getChildId();

	bool isCreated();

	void create(SceneManager* mSceneMgr);
	void draw(SceneManager* mSceneMgr, long pause);

	Entity* getEntity();
	SceneNode* getNode();

	void reset(SceneManager* mSceneMgr);

	float getRotate();
private:
	std::string childId;
	Entity *ent;
	SceneNode *node;

	float rotate;

	SceneManager* mSceneMgr;

	bool created;
};

#endif