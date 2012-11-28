#ifndef __BunBunMissionDrawControl_H__
#define __BunBunMissionDrawControl_H__

#define MOUSE_MOTION_MODIFIER 2000
#define MOUSE_ZOOM_MODIFIER 1000
#define MOUSE_SIDESCROLL_MODIFIER 15
#define KEYBOARD_MOTION_MODIFIER 5
#define KEYBOARD_ZOOM_MODIFIER 10
#define CAMERA_ZOOM_MIN 400
#define CAMERA_ZOOM_MAX 2500

#include "BunBunDrawControl.h"

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <ogre/OgreMouseEvent.h>
#include <bunbunwar/OgreGODEngine.h>
#include <bunbunwar/GODEngine.h>
#include "BunBunFloorEntity.h"

using namespace Ogre;

class BunBunMissionDrawControl: public BunBunDrawControl
{
public:
	BunBunMissionDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication);
    ~BunBunMissionDrawControl();

	bool onTimeFrame(int missedTimeFrames);
	bool onRenderFrame();

	void mousePressed(float x, float y, int button);
	void mouseDragged(float relX, float relY, int button);
	void mouseMoved(float x, float y, float relZ);
	void mouseMovedPlayField(float x, float y);

	void borderScroll(float x, float y);
	void moveCamera(const Vector3& trans);
	bool isBuildingTower();
	void setBuildingTower(bool buildingTower);
	void resetGhostUnit();
	void processStreamingKeyInput(InputReader* mInputDevice);
	OgreUnit* getSelectedUnit();
	void setSelectedUnit(OgreUnit* selectedUnit);
	void setHighlighted(bool highlight, OgreUnit* unit, ColourValue* val = NULL, String nameExtension = "_HighLight");
	void setHighlighted(bool highlight, Entity* ent, ColourValue* val = NULL, String nameExtension = "_HighLight");
	GODLandscapeObject* getObjectAtLocation(float x, float y);
protected:
	RaySceneQuery* mRaySceneQuery;
	bool buildingTower;
	long lastPause;
	OgreUnit* selectedUnit;
	OgreUnit* ghostUnit;
	bool ghostBlocked;
	Vector3 mSideScroll;
};

#endif
