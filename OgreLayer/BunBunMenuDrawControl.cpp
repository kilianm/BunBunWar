#include "BunBunMenuDrawControl.h"

BunBunMenuDrawControl::BunBunMenuDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication): BunBunDrawControl(mCamera, mSceneMgr, mWindow, bNextApplication, bExitApplication) {
}

BunBunMenuDrawControl::~BunBunMenuDrawControl() {
}

bool BunBunMenuDrawControl::onTimeFrame(int missedTimeFrames) {
	mCamera->rotate(Vector3::UNIT_Z, Radian(0.001f));
	return true;
}

bool BunBunMenuDrawControl::onRenderFrame() {
	return true;
}

void BunBunMenuDrawControl::loadMission(GODGameTypeObject* gameTypeObject, GODMissionObject* missionObject) {
	GODMissionControl::getInstance()->loadMission(gameTypeObject, missionObject);
	*mRunning = false;
	*bNextApplication = 2; // the mission app
}
