#ifndef GODEVENTS_H
#define GODEVENTS_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../objects/GODObject.h"

class DLLEXPORT GODEvents {
public:
	~GODEvents();

	static GODEvents* getInstance();

	void clear();

	bool hasNext();
	GODObject* next();

	bool hasIdInList(int id, int objectType);

	void addGODObject(GODObject* object);
	void removeGODObject(int id, int objectType);
	void removeGODObject(GODObject* object);
protected:
	GODEvents();
private:
	static GODEvents* instance;

	int iter;
	std::vector<GODObject*> objects;
};

#endif