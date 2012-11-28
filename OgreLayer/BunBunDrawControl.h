#ifndef __BunBunDrawControl_H__
#define __BunBunDrawControl_H__

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <ogre/Ogre.h>
#include <ogre/OgreStringConverter.h>
#include <ogre/OgreException.h>
#include <bunbunwar/GODEngine.h>

using namespace Ogre;

class BunBunDrawControl
{
public:
	BunBunDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication);
    virtual ~BunBunDrawControl();

	virtual bool onTimeFrame(int missedTimeFrames)=0;
	virtual bool onRenderFrame()=0;

	virtual void exitApplication();
	virtual void topApplication();

	virtual Camera* getCamera();
	virtual SceneManager* getSceneManager();
	virtual RenderWindow* getWindow();
	virtual bool* getRunning();

protected:
	Camera* mCamera;
    SceneManager* mSceneMgr;
    RenderWindow* mWindow;
	int* bNextApplication;
	bool* bExitApplication;
	bool* mRunning;
};

#endif
