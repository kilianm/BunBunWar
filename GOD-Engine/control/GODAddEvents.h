#ifndef GODADDEVENTS_H
#define GODADDEVENTS_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../objects/GODObject.h"
#include <list>

class DLLEXPORT GODAddEvents {
public:
	~GODAddEvents();

	static GODAddEvents* getInstance();

	void clear();

	GODObject* next();

	int amountOnStack();
	void addGODObject(GODObject* object);

	int nextId();
protected:
	GODAddEvents();
private:
	static GODAddEvents* instance;
	int id;

	std::list<GODObject*> objects;
};

#endif