#include "../include/OgreArrow.h"

OgreArrow::OgreArrow(int id, Utilities_GridLocation* source, Utilities_GridLocation* target) : GODArrowObject(id, source, target) {
	this->childId = "arrow_"+StringConverter::toString(id);
	this->created = true;
	this->rotate = 0.0f;
}

OgreArrow::~OgreArrow() {
	this->childId.clear();
	this->created = false;
	this->rotate = 0.0f;
	reset(mSceneMgr);
	mSceneMgr = NULL;
}

bool OgreArrow::isCreated() {
	return this->created;
}

void OgreArrow::setChildId(std::string childId) {
	this->childId = childId;
}

std::string OgreArrow::getChildId() {
	return this->childId;
}

void OgreArrow::create(SceneManager* mSceneMgr) {
	this->mSceneMgr = mSceneMgr;
	ent = mSceneMgr->createEntity(this->childId, "Arrow.mesh");
	ent->setMaterialName("BunBun/RustySteel");
	GODLandscapeControl* landscapeControl = GODMissionControl::getInstance()->getLandscapeControl();
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(this->childId);
	node->translate(Vector3((this->source->getX()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getXPlaneModifier(), 0, (this->source->getY()*GODLandscapeControl::LANDSCAPE_GRID_MODIFIER)-landscapeControl->getYPlaneModifier()));
	node->attachObject(ent);
	this->rotate = getRotate();
	this->created = true;
}

void OgreArrow::draw(SceneManager* mSceneMgr, long pause) {
	if (pause != 0) {
		fixTiming(pause);
	}
	addTimeSinceLastMove((float)GetTickCount()/1000.0f);
	if (this->rotate != 0.0f) {
		Quaternion q(Degree(this->rotate), Vector3::UNIT_Y);
		this->node->rotate(q);
		this->rotate = 0.0f;
	}
	this->node->translate(Vector3(getX(), 0, getY()));
	if (isFinished()) {
		this->created = false;
		reset(mSceneMgr);
	}
}

Entity* OgreArrow::getEntity() {
	return this->ent;
}

SceneNode* OgreArrow::getNode() {
	return this->node;
}

void OgreArrow::reset(SceneManager* mSceneMgr) {
	if (this->ent) {
		mSceneMgr->destroyEntity(this->ent);
		this->ent = NULL;
	}
	if (this->node) {
		mSceneMgr->destroySceneNode(this->node->getName());
		this->node = NULL;
	}
}

float OgreArrow::getRotate() {
	int directionX = this->target->getX()-this->source->getX();
	int directionY = this->target->getY()-this->source->getY();

	float angle = 0.0f;

	if (directionX < 0) {
		angle = 180.0f+Ogre::Math::ATan((float)directionY/(float)~directionX).valueDegrees();
	} else {
		angle = Ogre::Math::ATan((float)directionY/(float)directionX).valueDegrees()*-1;
	}
	return angle;
}
