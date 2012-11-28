#include "GODAttribute.h"

GODAttribute::GODAttribute(std::string name, std::string value) {
	this->name = name;
	this->value = value;
}

GODAttribute::~GODAttribute() {
	this->name.clear();
	this->value.clear();
}

std::string GODAttribute::getName() {
	return this->name;
}

void GODAttribute::setName(std::string name) {
	this->name = name;
}

std::string GODAttribute::getValue() {
	return this->value;
}

void GODAttribute::setValue(std::string value) {
	this->value = value;
}
