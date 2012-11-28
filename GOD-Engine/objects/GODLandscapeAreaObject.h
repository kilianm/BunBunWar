#ifndef GODLANDSCAPEAREAOBJECT_H
#define GODLANDSCAPEAREAOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <bunbunwar/Utilities.h>
#include "../xml/GODXML.h"
#include "../GODUtilConstructor.h"

class DLLEXPORT GODLandscapeAreaObject : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODLandscapeAreaObject();
	~GODLandscapeAreaObject();

	void setArea(std::string area);
	std::string getArea();

	void setGrid(Utilities_GridLocation* grid);
	Utilities_GridLocation* getGrid();

	void setSize(Utilities_Size* size);
	Utilities_Size* getSize();

	bool intersect(Utilities_GridLocation* grid);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	std::string area;
	Utilities_GridLocation* grid;
	Utilities_Size* size;
};

#endif