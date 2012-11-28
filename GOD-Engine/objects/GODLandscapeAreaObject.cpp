#include "GODLandscapeAreaObject.h"

GODLandscapeAreaObject::GODLandscapeAreaObject() {
	this->grid = NULL;
	this->size = NULL;
}

GODLandscapeAreaObject::~GODLandscapeAreaObject() {
	delete this->grid;
	delete this->size;
	this->area.clear();
}

void GODLandscapeAreaObject::setArea(std::string area) {
	this->area = area;
}

std::string GODLandscapeAreaObject::getArea() {
	return this->area;
}

void GODLandscapeAreaObject::setGrid(Utilities_GridLocation* grid) {
	this->grid = grid;
}

Utilities_GridLocation* GODLandscapeAreaObject::getGrid() {
	return this->grid;
}

void GODLandscapeAreaObject::setSize(Utilities_Size* size) {
	this->size = size;
}

Utilities_Size* GODLandscapeAreaObject::getSize() {
	return this->size;
}

bool GODLandscapeAreaObject::intersect(Utilities_GridLocation* grid) {
	return (grid->getX() >= this->grid->getX() && grid->getX() < this->grid->getX()+this->size->getWidth() &&
		grid->getY() >= this->grid->getY() && grid->getY() < this->grid->getY()+this->size->getHeight());
}

std::string GODLandscapeAreaObject::XML_OBJECT_NAME = "landscapeArea";

std::string GODLandscapeAreaObject::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODLandscapeAreaObject::parseXMLObject(GODXMLObject* object) {
	GODLandscapeAreaObject* areaObject = new GODLandscapeAreaObject();
	GODAttributes* attributes = object->getAttributes();
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "area") {
			areaObject->setArea(attribute->getValue());
		}
	}

	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		GODXMLObjectParser* parsed = GODXMLMapping::getInstance()->getXMLMapping(child->getName())->parseXMLObject(child);
		if (child->getName() == "position") {
			areaObject->setGrid(((GODGridConstructor*)parsed)->getGrid());
		} else if (child->getName() == "size") {
			areaObject->setSize(((GODSizeConstructor*)parsed)->getSize());
		}
	}
	return areaObject;
}
