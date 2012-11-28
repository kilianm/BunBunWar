#ifndef GODXMLPARSER_H
#define GODXMLPARSER_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <expat/expat.h>
#include <fstream>

#include "GODXML.h"

class DLLEXPORT GODXMLParser {
public:
	GODXMLParser();
	~GODXMLParser();

	void parseDocument(char* filename);

	void setCurrentObject(GODXMLObject* currentObject);
	GODXMLObject* getCurrentObject();

	void setFinalObject(GODXMLObjectParser* finalObject);
	GODXMLObjectParser* getFinalObject();
private:
	static void startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts);
	static void endElementHandler(void *userData, const XML_Char *name);

	bool readFile(char* filename);

	XML_Parser p;
	char* data;
	int size;

	GODXMLObject* currentObject;
	GODXMLObjectParser* finalObject;
};

#endif