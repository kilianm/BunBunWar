#ifndef UTILITIES_PATHNODE_H
#define UTILITIES_PATHNODE_H

#include <bunbunwar/stdafx.h>

class DLLEXPORT Utilities_PathNode {
public:
	Utilities_PathNode(Utilities_GridLocation* location, Utilities_PathNode* behindNode = NULL, Utilities_PathNode* infrontNode = NULL);
	~Utilities_PathNode();

	Utilities_GridLocation* getLocation();
	Utilities_PathNode* getBehindNode();
	Utilities_PathNode* getInFrontNode();
	void setLocation(Utilities_GridLocation* location);
	void setBehindNode(Utilities_PathNode* infrontNode);
	void setInFrontNode(Utilities_PathNode* infrontNode);
	void reverse();

private:
	Utilities_GridLocation* location;
	Utilities_PathNode* behindNode;
	Utilities_PathNode* infrontNode;
};

#endif