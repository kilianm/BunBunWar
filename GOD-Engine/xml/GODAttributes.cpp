#include "GODAttributes.h"

GODAttributes::GODAttributes(const XML_Char **atts){
	this->iter = NULL;
	int i = 0;
	while (atts[i] != NULL) {
		GODAttribute* attribute = new GODAttribute((char*)atts[i], (char*)atts[i+1]);
		this->attr.push_back(attribute);
		i += 2;
	}
}

GODAttributes::~GODAttributes() {
	this->attr.clear();
}

bool GODAttributes::hasNext() {
	if (iter == NULL) {
		iter = this->attr.begin();
	}
	if (this->attr.size() == 0) {
		return false;
	}
	if (iter != this->attr.end()) {
		return true;
	}
	iter = this->attr.begin();
	return false;
}

GODAttribute* GODAttributes::next() {
	if (this->attr.size() == 0) {
		return NULL;
	}
	GODAttribute* attribute = *iter;
	if (iter == this->attr.end()) {
		iter = NULL;
	} else {
		iter++;
	}
	return attribute;
}