#ifndef GODXMLOBJECTPARSER_H
#define GODXMLOBJECTPARSER_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

#include "GODXMLObject.h"

class DLLEXPORT GODXMLObjectParser {
public:
	virtual std::string getXMLObjectName()=0;
	virtual GODXMLObjectParser* parseXMLObject(GODXMLObject* object)=0;
};

#endif