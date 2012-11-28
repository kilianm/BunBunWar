#include "BunBunApplication.h"

BunBunApplication::BunBunApplication(int id, int parentId, int* bNextApplication, bool* bExitApplication, Root* mRoot, EventProcessor* mEventProcessor){
	this->id = id;
	this->parentId = parentId;
	this->bNextApplication = bNextApplication;
	this->bExitApplication = bExitApplication;
    this->mRoot = mRoot;
	this->mTimer = new Timer();
	this->mEventProcessor = mEventProcessor;
}

BunBunApplication::~BunBunApplication(){
	mSceneMgr->clearScene();
	MeshManager::getSingleton().removeAll();
	mWindow->removeAllListeners();
	mWindow->removeAllViewports();
	mRoot->removeFrameListener(mGuiControl);
	delete mGuiControl;
	delete mTimer;
	delete mDrawControl;
	if (this->mSceneMgr) {
		this->mSceneMgr->clearScene();
	}
}

void BunBunApplication::go(){
	try {
		_setup();
		mRoot->startRendering();
		destroyScene();
    } catch( Ogre::Exception& e ) {
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
}

void BunBunApplication::_setup(){
	mWindow = mRoot->getAutoCreatedWindow();
    chooseSceneManager();
    setup();
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    createCamera();
    createViewports();
    createScene();
	createDrawControl();
    createGuiControl();
}


void BunBunApplication::chooseSceneManager(){
	String sceneMgr = "BunBunSMInstance_"+StringConverter::toString(this->id);
	try {
		mSceneMgr = mRoot->getSceneManager(sceneMgr);
	} catch( Ogre::Exception& e ) {
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, sceneMgr);
    }
}

void BunBunApplication::createViewports(){
    // Create one viewport, entire window
    Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

void BunBunApplication::setup() {}
void BunBunApplication::createCamera() {}
void BunBunApplication::createGuiControl() {}
void BunBunApplication::createScene() {}
void BunBunApplication::createDrawControl() {}
void BunBunApplication::destroyScene() {}

