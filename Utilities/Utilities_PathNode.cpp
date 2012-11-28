#include <bunbunwar/Utilities.h>


Utilities_PathNode::Utilities_PathNode(Utilities_GridLocation* location, Utilities_PathNode* behindNode, Utilities_PathNode* infrontNode) {
	this->location = location;
	this->behindNode = behindNode;
	this->infrontNode = infrontNode;
}

Utilities_PathNode::~Utilities_PathNode() {
	this->location = NULL;
	this->behindNode = NULL;
	this->infrontNode = NULL;
}

Utilities_GridLocation* Utilities_PathNode::getLocation() {
	return location;
}

Utilities_PathNode* Utilities_PathNode::getBehindNode() {
	return behindNode;
}

Utilities_PathNode* Utilities_PathNode::getInFrontNode() {
	return infrontNode;
}

void Utilities_PathNode::setLocation(Utilities_GridLocation* location){
	this->location = location;
}

void Utilities_PathNode::setBehindNode(Utilities_PathNode* behindNode){
	this->behindNode = behindNode;
}

void Utilities_PathNode::setInFrontNode(Utilities_PathNode* infrontNode){
	this->infrontNode = infrontNode;
}

void Utilities_PathNode::reverse() {
	Utilities_PathNode* oldBehindNode = this->behindNode;
	Utilities_PathNode* oldInfrontNode = this->infrontNode;
	this->infrontNode = oldBehindNode;
	this->behindNode = oldInfrontNode;
}
