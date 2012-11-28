#include "BunBunDrawControl.h"

BunBunDrawControl::BunBunDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication)
{
	this->mCamera = mCamera;
	this->mSceneMgr = mSceneMgr;
	this->mWindow = mWindow;
	this->bNextApplication = bNextApplication;
	this->bExitApplication = bExitApplication;
	this->mRunning = new bool;
	*mRunning = true;
}

BunBunDrawControl::~BunBunDrawControl()
{
}

void BunBunDrawControl::exitApplication() {
	*mRunning = false;
	*bExitApplication = true;
}

void BunBunDrawControl::topApplication() {
	*mRunning = false;
	if (GODMissionControl::getInstance()->isMissionActive()) {
		GODMissionControl::getInstance()->stopMission();
		GODMissionControl::getInstance()->resetMission();
	}
	*bNextApplication = *bNextApplication-1;
}

Camera* BunBunDrawControl::getCamera() {
	return this->mCamera;
}

SceneManager* BunBunDrawControl::getSceneManager() {
	return this->mSceneMgr;
}

RenderWindow* BunBunDrawControl::getWindow() {
	return this->mWindow;
}

bool* BunBunDrawControl::getRunning() {
	return this->mRunning;
}

