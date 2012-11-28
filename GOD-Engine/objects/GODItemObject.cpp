#include "GODObjects.h"

GODItemObject::GODItemObject() {
	id = 0;
	size = NULL;
}

GODItemObject::~GODItemObject() {
	if (this->size) {
		delete this->size;
		this->size = NULL;
	}
	id = 0;
}

int GODItemObject::getObjectType() { 
	return GODObject::OBJECTTYPE_GODItemObject; 
}

int GODItemObject::getId() {
	return this->id;
}

void GODItemObject::setId(int id) {
	this->id = id;
}

int GODItemObject::getItemType() {
	return ITEMTYPE_ITEM;
}

Utilities_Size* GODItemObject::getSize() {
	return GODItemObject::size;
}

void GODItemObject::setSize(Utilities_Size* size) {
	GODItemObject::size = size;
}
