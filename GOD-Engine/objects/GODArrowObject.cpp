#include "GODArrowObject.h"

GODArrowObject::GODArrowObject(int id, Utilities_GridLocation* source, Utilities_GridLocation* target) {
	this->id = id;
	this->source = source;
	this->target = target;
}

GODArrowObject::~GODArrowObject() {
	this->id = 0;
	this->source = NULL;
	this->target = NULL;
}

int GODArrowObject::getId() {
	return this->id;
}

int GODArrowObject::getObjectType() {
	return GODObject::OBJECTTYPE_GODArrowObject;
}

Utilities_GridLocation* GODArrowObject::getSource() {
	return this->source;
}

Utilities_GridLocation* GODArrowObject::getTarget() {
	return this->target;
}

void GODArrowObject::moveArrow(long modifier, long xPlaneModifier, long yPlaneModifier) {
	float xNew = (target->getX()*(float)modifier)-(float)xPlaneModifier;
	float xOld = (source->getX()*(float)modifier)-(float)xPlaneModifier;
	float yNew = (target->getY()*(float)modifier)-(float)yPlaneModifier;
	float yOld = (source->getY()*(float)modifier)-(float)yPlaneModifier;
	this->xTotal = xNew - xOld;
	this->xLeft = this->xTotal;
	this->yTotal = yNew - yOld;
	this->yLeft = this->yTotal;
	this->timeForMovement = 0.25f;
	this->timeSinceLastMove = 0.0f;
	this->timeLastMove = (float)GetTickCount()/1000.0f;
}

void GODArrowObject::fixTiming(long pause) {
	if (this->timeLastMove != 0.0f) {
		this->timeLastMove += ((float)pause)/1000.0f;
	}
}

void GODArrowObject::addTimeSinceLastMove(float timeLastMove) {
	if (this->timeLastMove == 0.0f) {
		this->timeLastMove = timeLastMove;
	} else {
		this->timeSinceLastMove = timeLastMove-this->timeLastMove;
		this->timeLastMove = timeLastMove;
	}
}

float GODArrowObject::getX() {
	if (this->timeSinceLastMove == 0.0f) {
		return 0.0f;
	}
	float x = this->xTotal / ( this->timeForMovement / this->timeSinceLastMove );
	this->xLeft = this->xLeft - x;
	return x;
}

float GODArrowObject::getY() {
	if (this->timeSinceLastMove == 0.0f) {
		return 0.0f;
	}
	float y = this->yTotal / ( this->timeForMovement / this->timeSinceLastMove );
	this->yLeft = this->yLeft - y;
	return y;
}

bool GODArrowObject::isFinished() {
	if (!this->finished) {
		if (((this->xTotal < 0.0f && this->xLeft >= 0.0f) || (this->xTotal > 0.0f && this->xLeft <= 0.0f) || (this->xLeft == 0)) 
			&& ((this->yTotal < 0.0f && this->yLeft >= 0.0f) || (this->yTotal > 0.0f && this->yLeft <= 0.0f) || (this->yLeft == 0))) {
			this->finished = true;
			this->xTotal = 0.0f;
			this->xLeft = 0.0f;
			this->yTotal = 0.0f;
			this->yLeft = 0.0f;
		}
	}
	return this->finished;
}
