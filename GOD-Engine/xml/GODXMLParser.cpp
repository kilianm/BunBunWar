#include "GODXMLParser.h"

GODXMLParser::GODXMLParser() {
	this->p = XML_ParserCreate(NULL);
	this->currentObject = NULL;
	this->finalObject = NULL;
}

GODXMLParser::~GODXMLParser() {
	XML_ParserFree(p);
	this->finalObject = NULL;
	delete this->currentObject;
	delete [] data;
}

void GODXMLParser::parseDocument(char* filename) {
	int error;
	if (readFile(filename)) {
		XML_SetElementHandler(p, GODXMLParser::startElementHandler, GODXMLParser::endElementHandler);
		XML_SetUserData(p, (void*)this);
		error = XML_Parse(p, data, size, false);
	}
}

void GODXMLParser::setCurrentObject(GODXMLObject* currentObject) {
	this->currentObject = currentObject;
}

GODXMLObject* GODXMLParser::getCurrentObject() {
	return this->currentObject;
}

void GODXMLParser::setFinalObject(GODXMLObjectParser* finalObject) {
	this->finalObject = finalObject;
}

GODXMLObjectParser* GODXMLParser::getFinalObject() {
	return this->finalObject;
}

bool GODXMLParser::readFile(char* filename) {
    std::ifstream dataFile(filename);

	if( dataFile.fail()) {
        return false;
    }

	dataFile.seekg (0, std::ios::end);
	int size = dataFile.tellg();
    dataFile.seekg (0, std::ios::beg);

    unsigned char* buffer = new unsigned char[size];

    try {
        dataFile.read(reinterpret_cast<char*>(buffer), size);
    } catch(std::ifstream::failure e) {
        delete [] buffer;
		return false;
    }

    dataFile.close();
	this->data = (char*)buffer;
	this->size = size;
	return true;
}

void GODXMLParser::startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts) {
	GODAttributes* attributes = new GODAttributes(atts);
	GODXMLObject* xmlObject = new GODXMLObject();
	xmlObject->setName((char*)name);
	xmlObject->setAttributes(attributes);
	GODXMLParser* parser = (GODXMLParser*)userData;
	if (parser->getCurrentObject() != NULL) {
		xmlObject->setParent(parser->getCurrentObject());
		parser->getCurrentObject()->addChild(xmlObject);
	}
	parser->setCurrentObject(xmlObject);
}

void GODXMLParser::endElementHandler(void *userData, const XML_Char *name) {
	GODXMLParser* parser = (GODXMLParser*)userData;
	GODXMLObject* xmlObject = parser->getCurrentObject();
	if (xmlObject == NULL) {
		return;
	}
	if (xmlObject->getParent() == NULL && xmlObject->hasNextChild()) {
		GODXMLObject* xmlChild = xmlObject->nextChild();
		std::string name = xmlChild->getName();
		if (GODXMLMapping::getInstance()->hasXMLMapping(name)) {
			parser->setFinalObject(GODXMLMapping::getInstance()->getXMLMapping(name)->parseXMLObject(xmlChild));
		}
	}
	parser->setCurrentObject(xmlObject->getParent());
}
