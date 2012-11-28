#ifndef GODXMLOBJECT_H
#define GODXMLOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "GODAttributes.h"

class DLLEXPORT GODXMLObject {
public:
	GODXMLObject();
	~GODXMLObject();

	void setName(std::string name);
	std::string getName();

	void setAttributes(GODAttributes* attributes);
	GODAttributes* getAttributes();

	void setParent(GODXMLObject* parent);
	GODXMLObject* getParent();

	void addChild(GODXMLObject* child);
	std::vector<GODXMLObject*> getChilds();

	bool hasNextChild();
	GODXMLObject* nextChild();
private:
	std::string name;
	GODAttributes* attributes;
	GODXMLObject* parent;
	std::vector<GODXMLObject*> childs;
	std::vector<GODXMLObject*>::iterator iter;
};

#endif