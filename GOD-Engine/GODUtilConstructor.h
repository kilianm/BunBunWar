#ifndef GODUTILCONSTRUCTOR_H
#define GODUTILCONSTRUCTOR_H

#include <bunbunwar/Utilities.h>
#include "xml/GODXML.h"

class DLLEXPORT GODSizeConstructor : public GODXMLObjectParser {
public:
	GODSizeConstructor();
	GODSizeConstructor(int width, int height);
	~GODSizeConstructor();
	Utilities_Size* getSize();
	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	Utilities_Size* size;
};

class DLLEXPORT GODGridConstructor : public GODXMLObjectParser {
public:
	GODGridConstructor();
	GODGridConstructor(int x, int y);
	~GODGridConstructor();
	Utilities_GridLocation* getGrid();
	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	Utilities_GridLocation* grid;
};

#endif