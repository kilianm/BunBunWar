#include "BunBunMissionApplication.h"

BunBunMissionApplication::BunBunMissionApplication(int id, int parentId, int* nextApplication, bool* exitApplication, Root* mRoot, EventProcessor* mEventProcessor) : BunBunApplication(id, parentId, nextApplication, exitApplication, mRoot, mEventProcessor) {
}

BunBunMissionApplication::~BunBunMissionApplication()
{
	mRoot->removeMovableObjectFactory(mBunBunFloorEntityFactory);
	delete mBunBunFloorEntityFactory;
}

void BunBunMissionApplication::createCamera()
{
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

		mSceneMgr->setSkyBox(true, "BunBun/SpaceSkyBox");
        mCamera->setPosition(Vector3(CAMERA_X_DEFAULT,CAMERA_ZOOM_DEFAULT,CAMERA_Z_DEFAULT));
        mCamera->lookAt(Vector3(CAMERA_LOOKAT_X,CAMERA_LOOKAT_Y,CAMERA_LOOKAT_Z));
}

void BunBunMissionApplication::createScene() 
{
		//mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
        mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
        Light* l = mSceneMgr->createLight("MainLight");
        l->setPosition(0,600,0);

		GODLandscapeControl* landscapeControl = GODMissionControl::getInstance()->getLandscapeControl();

        Entity *ent;

        // Define a floor plane mesh
        Plane p;
        p.normal = Vector3::UNIT_Y;
        p.d = 1;
        MeshManager::getSingleton().createPlane("FloorPlane",
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			p,(landscapeControl->getWidth()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER*8), //just make plane a bit bigger for the moment
			(landscapeControl->getHeight()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER*4), //just make plane a bit bigger for the moment
			1,1,true,1,5,5,Vector3::UNIT_Z);

        Plane gu;
        gu.normal = Vector3::UNIT_Y;
        gu.d = -50;	
		MeshManager::getSingleton().createPlane("Landscape_GridUnit",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, gu, 
			GODLandscapeControl::LANDSCAPE_GRID_MODIFIER-1, GODLandscapeControl::LANDSCAPE_GRID_MODIFIER-1, 
			1,1,true,1,5,5,Vector3::UNIT_Z);

        // Create an entity (the floor)
        ent = mSceneMgr->createEntity("floor", "FloorPlane");
        ent->setMaterialName("BunBun/RustySteel");
		ent->setCastShadows(false);

        mSceneMgr->getRootSceneNode()->attachObject(ent);

		landscapeControl->setModifier(GODLandscapeControl::LANDSCAPE_GRID_MODIFIER);
		for (int x = 0; x < landscapeControl->getWidth(); x++) {
			for (int y = 0; y < landscapeControl->getHeight(); y++) {
				Utilities_GridLocation* grid = new Utilities_GridLocation(x,y);
				GODLandscapeObject* obj = landscapeControl->getLandscapeObject(grid);
				String gridloc_id;
				gridloc_id = "gridLocId_"+StringConverter::toString(x)+"_"+StringConverter::toString(y);
				BunBunFloorEntity* floorEnt = ((BunBunSceneManager*)mSceneMgr)->createBunBunFloorEntity(gridloc_id, "Landscape_GridUnit");
				floorEnt->setMaterialName("BunBun/GrassFloorSmall");
				floorEnt->setCastShadows(false);
				floorEnt->setGridLocation(grid);
				floorEnt->setQueryFlags(GODLandscapeControl::LANDSCAPE_GRID_QUERY_FLAG);
				SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode(gridloc_id);
				node->scale(1.1f, 0.0f, 1.1f);
				node->translate(Vector3((x*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getXPlaneModifier(), 0, (y*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getYPlaneModifier()));
				node->attachObject(floorEnt);

				if (obj->getGridKind() == GODLandscapeObject::LANDSCAPE_EMPTY) {
					// do nothing yet
				} else {
					String grid_id;
					if (obj->getGridKind() == GODLandscapeObject::LANDSCAPE_UNIT) {
						OgreUnit* unit = (OgreUnit*)obj->getItem();
						if (!unit->isCreated()) {
							grid_id = "unitId_"+StringConverter::toString(unit->getId());
							unit->setChildId(grid_id);
							unit->create(mSceneMgr);
						} else {
							ent = NULL;
						}
					} else {
						grid_id = "gridloc_"+StringConverter::toString(x)+"_"+StringConverter::toString(y);
						ent = mSceneMgr->createEntity(grid_id, "cube.mesh");
						ent->setMaterialName("BunBun/Rock");
						SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode(grid_id);
						node->translate(Vector3((x*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getXPlaneModifier(), 0, (y*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getYPlaneModifier()));
						node->attachObject(ent);
						node->scale(0.5f, 0.5f, 0.5f);
					}
				}
			}
		}
		GODMissionControl::getInstance()->startMission();
}

void BunBunMissionApplication::setup()
{
    ConfigFile cf;
    cf.load("res_mission.cfg");
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
	mBunBunFloorEntityFactory = new BunBunFloorEntityFactory();
	mRoot->addMovableObjectFactory(mBunBunFloorEntityFactory);
}

void BunBunMissionApplication::createDrawControl(){
	this->mDrawControl = new BunBunMissionDrawControl(mCamera, mSceneMgr, mWindow, bNextApplication, bExitApplication);
}

void BunBunMissionApplication::createGuiControl()
{
	mGuiControl = new BunBunMissionGuiControl(mDrawControl, mTimer, mEventProcessor);
	mRoot->addFrameListener(mGuiControl);
}

void BunBunMissionApplication::destroyScene() {
	if (GODMissionControl::getInstance()->isMissionActive())
		GODMissionControl::getInstance()->stopMission();
}
