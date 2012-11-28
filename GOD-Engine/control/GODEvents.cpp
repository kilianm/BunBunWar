#include <bunbunwar/GODEngine.h>

GODEvents* GODEvents::instance = NULL;

GODEvents::GODEvents() {
	iter = 0;
}

GODEvents::~GODEvents() {
	iter = 0;
	clear();
	delete instance;
}

void GODEvents::clear() {
	while ((signed)objects.size() > 0) {
		objects.erase(objects.begin());
	}
}

GODEvents* GODEvents::getInstance() {
	if (instance == NULL) {
		instance = new GODEvents();
	}
	return instance;
}

bool GODEvents::hasNext() {
	if (iter == -1) {
		iter = 0;
		return false;
	}
	if (objects.size() == 0) {
		return false;
	}
	if (iter < (signed)objects.size()) {
		return true;
	}
	iter = 0;
	return false;
}

GODObject* GODEvents::next() {
	if (objects.size() == 0) {
		return NULL;
	}
	GODObject* object = objects.at(iter);
	if (iter == (signed)objects.size()-1) {
		iter = -1;
	} else {
		iter++;
	}
	return object;
}

bool GODEvents::hasIdInList(int id, int objectType) {
	for (int i=0; i<(signed)objects.size(); i++) {
		GODObject* object = objects.at(i);
		if (object->getId() == id && object->getObjectType() == objectType) {
			return true;
		}
	}
	return false;
}

void GODEvents::addGODObject(GODObject* object) {
	objects.push_back(object);
}

void GODEvents::removeGODObject(GODObject* object) {
	GODEvents::removeGODObject(object->getId(), object->getObjectType());
}

void GODEvents::removeGODObject(int id, int objectType) {
	for (int i=0; i<(signed)objects.size(); i++) {
		GODObject* object = objects.at(i);
		if (object->getId() == id && object->getObjectType() == objectType) {
			if (i == 0 || i == objects.size()-1) {
				this->iter = -1;
			} else if (this->iter == i && this->iter < (signed)this->objects.size()-1) {
				this->iter = this->iter-1;
			} else if (this->iter == i && this->iter == (signed)this->objects.size()-1) {
				this->iter = -1;
			} else if (this->iter > i) {
				this->iter = this->iter-1;
			}
			objects.erase(objects.begin()+i);
			return;
		}
	}
}
	