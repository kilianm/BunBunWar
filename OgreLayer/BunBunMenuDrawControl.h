#ifndef __BunBunMenuDrawControl_H__
#define __BunBunMenuDrawControl_H__

#include "BunBunDrawControl.h"

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <bunbunwar/OgreGODEngine.h>
#include <bunbunwar/GODEngine.h>

using namespace Ogre;

class BunBunMenuDrawControl: public BunBunDrawControl
{
public:
	BunBunMenuDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication);
    ~BunBunMenuDrawControl();

	bool onTimeFrame(int missedTimeFrames);
	bool onRenderFrame();

	void loadMission(GODGameTypeObject* gameTypeObject, GODMissionObject* missionObject);
};

#endif
