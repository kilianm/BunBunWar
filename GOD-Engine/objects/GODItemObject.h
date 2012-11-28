#ifndef GODITEMOBJECT_H
#define GODITEMOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

#include "GODObjects.h"

class DLLEXPORT GODItemObject: public GODObject {
public:
	static const int ITEMTYPE_UNIT = 1;
	static const int ITEMTYPE_ITEM = 2;

	GODItemObject();
	virtual ~GODItemObject();

	int getId();
	void setId(int id);

	Utilities_Size* getSize();
	void setSize(Utilities_Size* size);

	virtual int getItemType();

	int getObjectType();
protected:
	Utilities_Size* size;
	int id;
};

#endif