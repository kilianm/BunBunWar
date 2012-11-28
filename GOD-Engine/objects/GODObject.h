#ifndef GODOBJECT_H
#define GODOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

class DLLEXPORT GODObject {
public:
	static const int OBJECTTYPE_GODUnitObject = 1;
	static const int OBJECTTYPE_GODItemObject = 2;
	static const int OBJECTTYPE_GODUnitTempObject = 3;
	static const int OBJECTTYPE_GODArrowObject = 4;

	virtual int getId()=0;
	virtual int getObjectType()=0;
};

#endif