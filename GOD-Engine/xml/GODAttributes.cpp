#include "GODAttributes.h"

GODAttributes::GODAttributes(const XML_Char **atts){
	int i = 0;
	while (atts[i] != NULL) {
		GODAttribute* attribute = new GODAttribute((char*)atts[i], (char*)atts[i+1]);
		this->attr.push_back(attribute);
		i += 2;
	}
	this->iter = this->attr.begin();
}

GODAttributes::~GODAttributes() {
	this->attr.clear();
}

bool GODAttributes::hasNext() {
	if (this->attr.size() == 0) {
		return false;
	}
	if (iter != this->attr.end()) {
		return true;
	}
	return false;
}

GODAttribute* GODAttributes::next() {
	if (this->attr.size() == 0) {
		return NULL;
	}
	GODAttribute* attribute = *iter;
	iter++;
	return attribute;
}