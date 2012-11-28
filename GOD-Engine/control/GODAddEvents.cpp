#include "GODAddEvents.h"

GODAddEvents* GODAddEvents::instance = NULL;

GODAddEvents::GODAddEvents() {
	id = 0;
}

GODAddEvents::~GODAddEvents() {
	id = 0;
	clear();
	delete instance;
}

void GODAddEvents::clear() {
	while ((signed)objects.size() > 0) {
		objects.erase(objects.begin());
	}
}

GODAddEvents* GODAddEvents::getInstance() {
	if (instance == NULL) {
		instance = new GODAddEvents();
	}
	return instance;
}

int GODAddEvents::amountOnStack() {
	return (int)objects.size();	
}

GODObject* GODAddEvents::next() {
	if (objects.size() == 0) {
		return NULL;
	}
	GODObject* object = (GODObject*)*(objects.begin());
	objects.pop_front();
	return object;
}


void GODAddEvents::addGODObject(GODObject* object) {
	objects.push_back(object);
}

int GODAddEvents::nextId() {
	id = id+1;
	if (id > 1000) {
		id = 0;
	}
	return id;
}
