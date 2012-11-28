#ifndef GODXMLMAPPING_H
#define GODXMLMAPPING_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <map>
#include <string>
#include "GODXML.h"

class DLLEXPORT GODXMLMapping {
public:
	static GODXMLMapping* getInstance();
	~GODXMLMapping();

	void addXMLMapping(GODXMLObjectParser* objectParser);
	bool hasXMLMapping(std::string name);
	GODXMLObjectParser* getXMLMapping(std::string name);
protected:
	GODXMLMapping();
private:
	typedef std::map<std::string, GODXMLObjectParser*> XMLObjectMap;
	XMLObjectMap xmlMapping;

	static GODXMLMapping* instance;
};

#endif