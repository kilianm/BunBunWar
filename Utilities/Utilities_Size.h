#ifndef UTILITIES_GRIDSIZE_H
#define UTILITIES_GRIDSIZE_H

#include <bunbunwar/stdafx.h>

class DLLEXPORT Utilities_Size {
public:
	Utilities_Size();
	Utilities_Size(int width, int height);
	~Utilities_Size();

	// Getters & Setters
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
private:
	int width;
	int height;
};

#endif