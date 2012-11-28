#include "BunBunMenuApplication.h"

BunBunMenuApplication::BunBunMenuApplication(int id, int parentId, int* nextApplication, bool* exitApplication, Root* mRoot, EventProcessor* mEventProcessor) : BunBunApplication(id, parentId, nextApplication, exitApplication, mRoot, mEventProcessor) {
}

BunBunMenuApplication::~BunBunMenuApplication(){
}

void BunBunMenuApplication::createCamera(){
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

        mCamera->setPosition(Vector3(0,0,0));
}

void BunBunMenuApplication::createScene() {
		//mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	    mSceneMgr->setSkyBox(true, "BunBun/SpaceSkyBox");
}

void BunBunMenuApplication::setup() {
    ConfigFile cf;
    cf.load("res_menu.cfg");
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

void BunBunMenuApplication::createDrawControl(){
	this->mDrawControl = new BunBunMenuDrawControl(mCamera, mSceneMgr, mWindow, bNextApplication, bExitApplication);
}

void BunBunMenuApplication::createGuiControl(){
	mGuiControl = new BunBunMenuGuiControl(mDrawControl, mTimer, mEventProcessor);
	mRoot->addFrameListener(mGuiControl);
}

void BunBunMenuApplication::destroyScene() {
}