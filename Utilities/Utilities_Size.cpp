#include <bunbunwar/Utilities.h>

Utilities_Size::Utilities_Size() {}
Utilities_Size::Utilities_Size(int width, int height) {
	this->width = width;
	this->height = height;
}

Utilities_Size::~Utilities_Size() {
	this->width = 0;
	this->height = 0;
}

int Utilities_Size::getWidth() {
	return width;
}

int Utilities_Size::getHeight() {
	return height;
}

void Utilities_Size::setWidth(int width) {
	this->width = width;
}

void Utilities_Size::setHeight(int height) {
	this->height = height;
}
