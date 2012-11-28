#ifndef __BunBunApplication_H__
#define __BunBunApplication_H__

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <ogre/Ogre.h>
#include <ogre/OgreConfigFile.h>
#include <ogre/OgreTimer.h>

#include "BunBunSceneManager.h"
#include "BunBunDrawControl.h"
#include "BunBunGuiControl.h"

using namespace Ogre;

class BunBunApplication {
public:
	BunBunApplication(int id, int parentId, int* bNextApplication, bool* bExitApplication, Root* mRoot, EventProcessor* mEventProcessor);
	virtual ~BunBunApplication();
	void go();

protected:
	int id;
	int parentId;
	int* bNextApplication;
	bool* bExitApplication;
    Root* mRoot;
    Camera* mCamera;
    SceneManager* mSceneMgr;
    RenderWindow* mWindow;
    BunBunDrawControl* mDrawControl;
    BunBunGuiControl* mGuiControl;
	Timer* mTimer;
	EventProcessor* mEventProcessor;

    virtual void chooseSceneManager();
    virtual void createViewports();
	virtual void setup();
    virtual void createCamera();
    virtual void createGuiControl();
    virtual void createScene();
    virtual void createDrawControl();
    virtual void destroyScene();
private:
	void _setup();

};


#endif
