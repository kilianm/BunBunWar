#include "GODXMLMapping.h"

GODXMLMapping* GODXMLMapping::instance = NULL;

GODXMLMapping::GODXMLMapping() {}

GODXMLMapping::~GODXMLMapping() {
	this->xmlMapping.clear();
}

GODXMLMapping* GODXMLMapping::getInstance() {
	if (instance == NULL) {
		instance = new GODXMLMapping();
	}
	return instance;
}

void GODXMLMapping::addXMLMapping(GODXMLObjectParser* objectParser) {
	if (objectParser == NULL) {
		return;
	}
	this->xmlMapping[objectParser->getXMLObjectName()] = objectParser;
}

bool GODXMLMapping::hasXMLMapping(std::string name) {
	return !(this->xmlMapping.find(name) == this->xmlMapping.end());
}

GODXMLObjectParser* GODXMLMapping::getXMLMapping(std::string name) {
	XMLObjectMap::iterator i = this->xmlMapping.find(name);
	if (i == this->xmlMapping.end()) {
		return NULL;
	}
	return i->second;
}
