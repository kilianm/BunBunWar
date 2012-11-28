#include "BunBunMissionDrawControl.h"


BunBunMissionDrawControl::BunBunMissionDrawControl(Camera* mCamera, SceneManager* mSceneMgr, RenderWindow* mWindow, int* bNextApplication, bool* bExitApplication): BunBunDrawControl(mCamera, mSceneMgr, mWindow, bNextApplication, bExitApplication) {
	this->lastPause = 0;
	this->selectedUnit = NULL;
	this->buildingTower = false;
	this->ghostUnit = NULL;
	this->ghostBlocked = false;
	mRaySceneQuery = NULL;
}

BunBunMissionDrawControl::~BunBunMissionDrawControl()
{
	if (mRaySceneQuery) {
		mSceneMgr->destroyQuery(mRaySceneQuery);
		mRaySceneQuery= NULL;
	}
	this->buildingTower = false;
	this->ghostBlocked = false;
	this->lastPause = 0;
	selectedUnit = NULL;
}

bool BunBunMissionDrawControl::onTimeFrame(int missedTimeFrames) {
	if (mSideScroll.x != 0 || mSideScroll.z != 0)
		moveCamera(mSideScroll);

	return true;
}

bool BunBunMissionDrawControl::onRenderFrame()
{
	if(GODMissionControl::getInstance()->isPaused()) {
		if (this->lastPause == 0) {
			this->lastPause = GetTickCount();
		}
		return true;
	}

	GODAddEvents* addEvents = GODAddEvents::getInstance();
	GODMissionControl* missionControl = GODMissionControl::getInstance();
	// Add
	int onStack = addEvents->amountOnStack();
	while (onStack > 0) {
		GODObject* object = addEvents->next();
		if (object != NULL) {
			switch (object->getObjectType()) {
				case GODObject::OBJECTTYPE_GODUnitTempObject: {
					GODTempUnitObject* unitTemp = (GODTempUnitObject*)object;
					OgreUnit* ogreUnit = new OgreUnit(missionControl->getUnitControl()->nextId(), unitTemp->getOwner(), unitTemp->getUnitType(), unitTemp->getPathObject());
					ogreUnit->setSize(unitTemp->getSize());
					ogreUnit->setChildId("unitId_"+StringConverter::toString(ogreUnit->getId()));
					GODEvents::getInstance()->addGODObject(ogreUnit);
					missionControl->getUnitControl()->addUnit(ogreUnit);
					missionControl->getLandscapeControl()->placeUnit(ogreUnit);
					ogreUnit->create(mSceneMgr);
				} break;
				case GODObject::OBJECTTYPE_GODArrowObject: {
					GODArrowObject* arrowObject = (GODArrowObject*)object;
					OgreArrow* ogreArrow = new OgreArrow(arrowObject->getId(), arrowObject->getSource(), arrowObject->getTarget());;
					GODEvents::getInstance()->addGODObject(ogreArrow);
					ogreArrow->moveArrow(missionControl->getLandscapeControl()->getModifier(), missionControl->getLandscapeControl()->getXPlaneModifier(), missionControl->getLandscapeControl()->getYPlaneModifier());
					ogreArrow->create(mSceneMgr);
				} break;
			}
		}
		onStack -= 1;
	}

	GODEvents* events = GODEvents::getInstance();
	
	// Move
	while (events->hasNext()) {
		GODObject* object = events->next();
		if (object != NULL) {
			long pause = 0;
			if (this->lastPause != 0) {
				pause = GetTickCount()-this->lastPause;
			}
			switch (object->getObjectType()) {
				case GODObject::OBJECTTYPE_GODUnitObject: {
					((OgreUnit*)object)->draw(mSceneMgr, pause);
				} break;
				case GODObject::OBJECTTYPE_GODArrowObject: {
					OgreArrow* arrow = (OgreArrow*)object;
					if (arrow->isCreated()) {
						arrow->draw(mSceneMgr, pause);
					} else {
						GODEvents::getInstance()->removeGODObject(arrow);
						//delete arrow;
					}
				} break;
			}
		}
	}

	if (selectedUnit && selectedUnit->isDead())
		selectedUnit = NULL;

	this->lastPause = 0;
	return true;
}

void BunBunMissionDrawControl::mousePressed(float x, float y, int button) {
	if (button == MouseEvent::BUTTON1_MASK) {
		setHighlighted(false, selectedUnit);
		selectedUnit = NULL;
		return;
	}
	if (button != MouseEvent::BUTTON0_MASK) {
		return;
	}
	
	GODLandscapeObject* obj = getObjectAtLocation(x, y);

	if (obj == NULL) {
		return;
	}

	GODMissionControl* missionControl = GODMissionControl::getInstance();
	if (obj->getGridKind() == GODLandscapeObject::LANDSCAPE_EMPTY) {
		setHighlighted(false, selectedUnit);
		selectedUnit = NULL;
		GODUnitTypeObject* type = missionControl->getUnitTypeControl()->getUnitTypeWithId(1);
		if (type != NULL && this->buildingTower && missionControl->decreaseMoney(type->getPrice())) {
			int id = missionControl->getUnitControl()->nextId();
			OgreUnit* unit = new OgreUnit(id, 1, type, obj->getLocation());
			unit->setSize(new Utilities_Size(1,1));
			String grid_id = "unitId_"+StringConverter::toString(id);
			unit->setChildId(grid_id);
			GODEvents::getInstance()->addGODObject(unit);
			missionControl->getUnitControl()->addUnit(unit);
			missionControl->getLandscapeControl()->placeUnit(unit);
			unit->create(mSceneMgr);
		}
	} else if (obj->getGridKind() != GODLandscapeObject::LANDSCAPE_BLOCKED) {
		setHighlighted(false, selectedUnit);
		if (obj != NULL) {
			selectedUnit = (OgreUnit*)obj->getItem();
			if (selectedUnit != NULL && selectedUnit->isDead()) {
				selectedUnit = NULL;
				return;
			}
			setHighlighted(true, selectedUnit, new ColourValue(1.0, 1.0, 0.0, 1.0));
		}
	} else {
		setHighlighted(false, selectedUnit);
		selectedUnit = NULL;
	}
}

void BunBunMissionDrawControl::mouseDragged(float relX, float relY, int button)
{
	if (button == 1) {
		moveCamera(Vector3(0+(relX * MOUSE_MOTION_MODIFIER),0,0));
		moveCamera(Vector3(0,0,0+(relY * MOUSE_MOTION_MODIFIER)));
	}
}
void BunBunMissionDrawControl::mouseMoved(float x, float y, float relZ) {
	moveCamera(Vector3(0,0-(relZ * MOUSE_ZOOM_MODIFIER),0));
	borderScroll(x, y);
}

void BunBunMissionDrawControl::mouseMovedPlayField(float x, float y) {
	GODLandscapeObject* obj = getObjectAtLocation(x, y);
	if (obj == NULL) {
		return;
	}

	GODMissionControl* missionControl = GODMissionControl::getInstance();

	bool newlyCreated = false;

	if (!this->ghostUnit) {
		GODUnitTypeObject* type = missionControl->getUnitTypeControl()->getUnitTypeWithId(1);
		this->ghostUnit = new OgreUnit();
		this->ghostUnit->setUnitType(type);
		this->ghostUnit->setChildId("ghostUnit");
		this->ghostUnit->setLocation(obj->getLocation());
		this->ghostUnit->create(mSceneMgr);
		newlyCreated = true;
	} else if (!this->ghostUnit->getEntity()) {
		this->ghostUnit->setLocation(obj->getLocation());
		this->ghostUnit->create(mSceneMgr);
	} else {
		setHighlighted(false, this->ghostUnit, NULL, this->ghostBlocked ? "_HighlightedRed" : "_HighlightedGreen");
	}
	if (obj->getGridKind() <= GODLandscapeObject::LANDSCAPE_EMPTY) {
		this->ghostBlocked = false;
		setHighlighted(true, this->ghostUnit, new ColourValue(0.0, 1.0, 0.0, 1.0), "_HighlightedGreen");
	} else {
		this->ghostBlocked = true;
		setHighlighted(true, this->ghostUnit, new ColourValue(1.0, 0.0, 0.0, 1.0), "_HighlightedRed");
	}
	if (!newlyCreated) {
		GODLandscapeControl* landscapeControl = missionControl->getLandscapeControl();
		float tx = (obj->getLocation()->getX()*landscapeControl->getModifier())-landscapeControl->getXPlaneModifier();
		tx = tx-((this->ghostUnit->getLocation()->getX()*landscapeControl->getModifier())-landscapeControl->getXPlaneModifier());
		float ty = (obj->getLocation()->getY()*landscapeControl->getModifier())-landscapeControl->getYPlaneModifier();
		ty = ty-((this->ghostUnit->getLocation()->getY()*landscapeControl->getModifier())-landscapeControl->getYPlaneModifier());
		this->ghostUnit->getNode()->translate(Vector3(tx, 0, ty));
		this->ghostUnit->setLocation(obj->getLocation());
	}
}

bool BunBunMissionDrawControl::isBuildingTower() {
	return this->buildingTower;
}

void BunBunMissionDrawControl::setBuildingTower(bool buildingTower) {
	this->buildingTower = buildingTower;
}

GODLandscapeObject* BunBunMissionDrawControl::getObjectAtLocation(float x, float y) {
	float tx = (float)(1.0f / mWindow->getWidth()) * x;
	float ty = (float)(1.0f / mWindow->getHeight()) * y;
	Ray mouseRay = mCamera->getCameraToViewportRay(tx, ty);
	mRaySceneQuery = mSceneMgr->createRayQuery(mouseRay);
	mRaySceneQuery->setQueryMask(GODLandscapeControl::LANDSCAPE_GRID_QUERY_FLAG);
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr;
	GODLandscapeObject* obj = NULL;
	for(itr=result.begin();itr!=result.end();itr++){
		if (itr->movable && itr->movable->getName().substr(0, 10) == "gridLocId_" ) {
			GODMissionControl* missionControl = GODMissionControl::getInstance();
			GODLandscapeControl* landscapeControl = missionControl->getLandscapeControl();
			BunBunFloorEntity* ent = (BunBunFloorEntity*)itr->movable;
			obj = landscapeControl->getLandscapeObject(ent->getGridLocation());
			break;
		}
	}
	mRaySceneQuery->clearResults( );
	mSceneMgr->destroyQuery(mRaySceneQuery);
	mRaySceneQuery = NULL;
	return obj;
}

void BunBunMissionDrawControl::setHighlighted(bool highlight, OgreUnit* unit, ColourValue* val, String nameExtension) {
	if (unit != NULL) {
		setHighlighted(highlight, unit->getEntity(), val, nameExtension);
	}
}

// This code is from Team Pantheon's Rastullahs Lockenpracht
void BunBunMissionDrawControl::setHighlighted(bool highlight, Entity* ent, ColourValue* val, String nameExtension) {
	if (ent == NULL || (highlight && val == NULL)) {
		return;
	}

    int numEnts = ent->getNumSubEntities();

    for( int i = 0; i < numEnts; i++ ) {
        SubEntity* subent = ent->getSubEntity(i);

        if( subent == NULL )
            continue;

        if (ent->isHardwareAnimationEnabled()) {
            subent->setCustomParameter(0,
                highlight ? Vector4(1, 1, 1, 1) : Vector4(0, 0, 0, 0));
        }

        MaterialPtr oldMaterial = subent->getMaterial();

        if( highlight ) {           	 
            MaterialPtr material = MaterialManager::getSingleton().getByName( oldMaterial->getName()+nameExtension );

            if( material.isNull() )  {
                material = oldMaterial->clone( oldMaterial->getName()+nameExtension );

				material->setAmbient(Ogre::ColourValue(val->r, val->g, val->b, val->a));
                material->setDiffuse(Ogre::ColourValue(val->r, val->g, val->b, val->a));
                material->setSelfIllumination(0.8, 0.8, 0.8); 
            }

            subent->setMaterialName(material->getName());
        } else {
            String matName = oldMaterial->getName();
            matName = matName.erase(matName.length() - nameExtension.length(), nameExtension.length() );
            subent->setMaterialName( matName );				
        }
    }
	if (val) {
		delete val;
		val = NULL;
	}
}

void BunBunMissionDrawControl::resetGhostUnit() {
	this->ghostUnit->reset(mSceneMgr);
}

void BunBunMissionDrawControl::borderScroll(float x, float y)
{
	Real minBorder = 0.001;
	Real maxBorderX = mWindow->getWidth()-10;
	Real maxBorderZ = mWindow->getHeight()-10;
	if (x < minBorder || x > maxBorderX) {
		if (x < minBorder)
			mSideScroll.x = 0-MOUSE_SIDESCROLL_MODIFIER;
		if (x > maxBorderX)
			mSideScroll.x = MOUSE_SIDESCROLL_MODIFIER;
	} else
		mSideScroll.x = 0;
	if (y < minBorder || y > maxBorderZ) {
		if (y < minBorder)
			mSideScroll.z = 0-MOUSE_SIDESCROLL_MODIFIER;
		if (y > maxBorderZ)
			mSideScroll.z = MOUSE_SIDESCROLL_MODIFIER;
	} else
		mSideScroll.z = 0;
}

void BunBunMissionDrawControl::moveCamera(const Vector3& trans)
{
	const Vector3 newPos = mCamera->getPosition();
	if ((newPos.y+trans.y) < CAMERA_ZOOM_MIN || (newPos.y+trans.y) > CAMERA_ZOOM_MAX)
		return;

	mCamera->move(trans);
}

OgreUnit* BunBunMissionDrawControl::getSelectedUnit() {
	return this->selectedUnit;
}

void BunBunMissionDrawControl::setSelectedUnit(OgreUnit* selectedUnit) {
	this->selectedUnit = selectedUnit;
}

void BunBunMissionDrawControl::processStreamingKeyInput(InputReader* mInputDevice)
{
    if (mInputDevice->isKeyDown(KC_LEFT) || mInputDevice->isKeyDown(KC_A))
		moveCamera(Vector3(0-KEYBOARD_MOTION_MODIFIER,0,0));

    if (mInputDevice->isKeyDown(KC_RIGHT) || mInputDevice->isKeyDown(KC_D))
		moveCamera(Vector3(0+KEYBOARD_MOTION_MODIFIER,0,0));

    if (mInputDevice->isKeyDown(KC_UP) || mInputDevice->isKeyDown(KC_W) )
		moveCamera(Vector3(0,0,0-KEYBOARD_MOTION_MODIFIER));

    if (mInputDevice->isKeyDown(KC_DOWN) || mInputDevice->isKeyDown(KC_S) )
		moveCamera(Vector3(0,0,0+KEYBOARD_MOTION_MODIFIER));

    if (mInputDevice->isKeyDown(KC_PGUP))
		moveCamera(Vector3(0,0-KEYBOARD_ZOOM_MODIFIER,0));

    if (mInputDevice->isKeyDown(KC_PGDOWN))
		moveCamera(Vector3(0,0+KEYBOARD_ZOOM_MODIFIER,0));
}
