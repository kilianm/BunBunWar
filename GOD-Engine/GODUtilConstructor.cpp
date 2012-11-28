#include "GODUtilConstructor.h"

GODSizeConstructor::GODSizeConstructor() {}

GODSizeConstructor::GODSizeConstructor(int width, int height) {
	size = new Utilities_Size(width, height);
}

GODSizeConstructor::~GODSizeConstructor() {
	delete size;
}

Utilities_Size* GODSizeConstructor::getSize() { return size; }

std::string GODSizeConstructor::getXMLObjectName() { return "size"; }

GODXMLObjectParser* GODSizeConstructor::parseXMLObject(GODXMLObject* object) {
	GODAttributes* attributes = object->getAttributes();
	int width = 0;
	int height = 0;
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "width") {
			width = atoi(attribute->getValue().c_str());
		} else if (attribute->getName() == "height") {
			height = atoi(attribute->getValue().c_str());
		}
	}
	return new GODSizeConstructor(width, height);
}

//-----------------------------------------------------
GODGridConstructor::GODGridConstructor() {}

GODGridConstructor::GODGridConstructor(int x, int y) {
	grid = new Utilities_GridLocation(x, y);
}

GODGridConstructor::~GODGridConstructor() {
	delete grid;
}

Utilities_GridLocation* GODGridConstructor::getGrid() { return grid; }

std::string GODGridConstructor::getXMLObjectName() { return "position"; }

GODXMLObjectParser* GODGridConstructor::parseXMLObject(GODXMLObject* object) {
	GODAttributes* attributes = object->getAttributes();
	int x = 0;
	int y = 0;
	while (attributes->hasNext()) {
		GODAttribute* attribute = attributes->next();
		if (attribute->getName() == "x") {
			x = atoi(attribute->getValue().c_str())-1;
		} else if (attribute->getName() == "y") {
			y = atoi(attribute->getValue().c_str())-1;
		}
	}
	return new GODGridConstructor(x, y);
}