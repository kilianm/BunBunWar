#ifndef GODATTRIBUTES_H
#define GODATTRIBUTES_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <expat/expat.h>

#include "GODAttribute.h"

class DLLEXPORT GODAttributes {
public:
	GODAttributes(const XML_Char **atts);
	~GODAttributes();

	bool hasNext();
	GODAttribute* next();
private:
	std::vector<GODAttribute*> attr;
	std::vector<GODAttribute*>::iterator iter;
};

#endif