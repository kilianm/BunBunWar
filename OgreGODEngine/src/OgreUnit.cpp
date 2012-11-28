#include <bunbunwar/OgreGODEngine.h>

OgreUnit::OgreUnit() : GODUnitObject() {
	setInitValues();
}

/**
 * Voor Unit's zonder begin positie
 */
OgreUnit::OgreUnit(int id, int owner, GODUnitTypeObject* unitType) : GODUnitObject(id, owner, unitType) {
	setInitValues();
}

/**
 * Statische Unit's worden hiermee gezet
 */
OgreUnit::OgreUnit(int id, int owner, GODUnitTypeObject* unitType, Utilities_GridLocation* location) : GODUnitObject(id, owner, unitType, location) {
	setInitValues();
}

/**
 * Bewegende Unit's worden hiermee gezet
 */
OgreUnit::OgreUnit(int id, int owner, GODUnitTypeObject* unitType, GODPathObject* path) : GODUnitObject(id, owner, unitType, path) {
	setInitValues();
}

OgreUnit::~OgreUnit() {
	if (this->text) {
		delete this->text;
		this->text = NULL;
	}
	reset(mSceneMgr);
	this->created = false;
	this->childId.clear();
	mSceneMgr = NULL;
}

void OgreUnit::setInitValues() {
	this->ent = NULL;
	this->node = NULL;
	this->text = NULL;
	this->mSceneMgr = NULL;
	this->created = false;
}

void OgreUnit::setChildId(std::string childId) {
	this->childId = childId;
}

std::string OgreUnit::getChildId() {
	return this->childId;
}

bool OgreUnit::isCreated() {
	return this->created;
}

Entity* OgreUnit::getEntity() {
	return this->ent;
}

SceneNode* OgreUnit::getNode() {
	return this->node;
}

void OgreUnit::reset(SceneManager* mSceneMgr) {
	GODEvents::getInstance()->removeGODObject(getId(), getObjectType());
	if (text != NULL) {
		text->enable(false);
	}
	this->created = false;
	if (this->text) {
		delete this->text;
		this->text = NULL;
	}
	if (!mSceneMgr)
		return;
	if (this->ent) {
		mSceneMgr->destroyEntity(this->ent);
		this->ent = NULL;
	}
	if (this->node) {
		mSceneMgr->destroySceneNode(this->node->getName());
		this->node = NULL;
	}
}

void OgreUnit::create(SceneManager* mSceneMgr) {
	this->mSceneMgr = mSceneMgr;
	ent = mSceneMgr->createEntity(this->childId, (getUnitType())->getMeshName());
	GODLandscapeControl* landscapeControl = GODMissionControl::getInstance()->getLandscapeControl();
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(this->childId);
	node->translate(Vector3((location->getX()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getXPlaneModifier(), 0, (location->getY()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getYPlaneModifier()));
	node->attachObject(ent);
	if (!text) {
		if (this->getOwner() == 0)
			text = new ObjectTextDisplay(ent, mSceneMgr->getCamera("PlayerCam"), ColourValue(1.0f, 1.0f, 1.0f));
		else
			text = new ObjectTextDisplay(ent, mSceneMgr->getCamera("PlayerCam"), ColourValue(1.0f, 0.0f, 0.0f));
	}
	if (this->GODPath != NULL) {
		GODMissionControl::getInstance()->finishedMove(getId());
	}
	this->created = true;
}

void OgreUnit::draw(SceneManager* mSceneMgr, long pause) {
	GODMissionControl* missionControl = GODMissionControl::getInstance();
	if (!isDead()) {
		if (text != NULL) {
			if (hasDamage()) {
				int damage = getDamage();
				if (damage != 0) {
					text->enable(true);
					if (damage == -2) {
						text->setText("MISS");
					} else if (damage > 0) {
						text->setText(StringConverter::toString(damage));
					}
				}
				text->update();
			} else {
				text->enable(false);
			}
		}
		if (!isFinished()) {
			if (pause != 0) {
				fixTiming(pause);
			}
			
			addTimeSinceLastMove((float)GetTickCount()/1000.0f);
			if (getOwner() != 1) {
				if (getRotate() != 0.0f) {
					Quaternion q(Degree(getRotate()), Vector3::UNIT_Y);
					this->node->rotate(q);
				}
				this->node->translate(Vector3(getX(), 0, getY()));
			}
			if (isFinished()) {
				missionControl->finishedMove(getId());
			}
		}
	} else {
		if (!isFinished()) {
			missionControl->finishedMove(getId());
		}
		reset(mSceneMgr);
	}
}
