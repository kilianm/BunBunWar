#include "GODXMLObject.h"

GODXMLObject::GODXMLObject() {
	this->attributes = NULL;
	this->parent = NULL;
}

GODXMLObject::~GODXMLObject() {
	this->childs.clear();
	this->name.clear();
	this->parent = NULL;
	delete this->attributes;
}

void GODXMLObject::setName(std::string name) {
	this->name = name;
}

std::string GODXMLObject::getName() {
	return this->name;
}

void GODXMLObject::setAttributes(GODAttributes* attributes) {
	this->attributes = attributes;
}

GODAttributes* GODXMLObject::getAttributes() {
	return this->attributes;
}

void GODXMLObject::setParent(GODXMLObject* parent) {
	this->parent = parent;
}

GODXMLObject* GODXMLObject::getParent() {
	return this->parent;
}

void GODXMLObject::addChild(GODXMLObject* child) {
	this->childs.push_back(child);
}

std::vector<GODXMLObject*> GODXMLObject::getChilds() {
	return this->childs;
}

bool GODXMLObject::hasNextChild() {
	if (iter == NULL) {
		iter = this->childs.begin();
	}
	if (this->childs.size() == 0) {
		return false;
	}
	if (iter != this->childs.end()) {
		return true;
	}
	iter = this->childs.begin();
	return false;
}

GODXMLObject* GODXMLObject::nextChild() {
	if (this->childs.size() == 0) {
		return NULL;
	}
	GODXMLObject* child = *iter;
	if (iter == this->childs.end()) {
		iter = NULL;
	} else {
		iter++;
	}
	return child;
}
