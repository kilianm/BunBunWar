#ifndef GODUNITTYPECONTROL_H
#define GODUNITTYPECONTROL_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../objects/GODObjects.h"
#include "../xml/GODXML.h"

class DLLEXPORT GODUnitTypeControl : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODUnitTypeControl();
	~GODUnitTypeControl();

	void addUnitType(GODUnitTypeObject* unitType);
	void loadUnitTypes(GODScriptObject* script);

	bool hasId(int id);
	GODUnitTypeObject* getUnitType(int location);
	GODUnitTypeObject* getUnitTypeWithId(int id);
	GODUnitTypeObject* getUnitTypeWithIdAndUpgrade(int id, int upgrade);
	GODUnitTypeObject* getUnitTypeWithIdAndNextUpgrade(int id, int upgrade);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private: 
	std::vector<GODUnitTypeObject*> unitTypes;
};

#endif