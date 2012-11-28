#ifndef GODGAMETYPEOBJECT_H
#define GODGAMETYPEOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../xml/GODXML.h"
#include "../calculations/GODPathFinder.h"
#include "../calculations/GODAssaultPathFinder.h"
#include "../calculations/GODTowerDefensePathFinder.h"

class DLLEXPORT GODGameTypeObject : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODGameTypeObject();
	~GODGameTypeObject();

	GODPathFinder* getPathFinder();
	void setPathFinder(GODPathFinder* pathFinder);
	bool isAlwaysAttack();
	void setAlwaysAttack(bool alwaysAttack);
	bool isAttackOnBlock();
	void setAttackOnBlock(bool attackOnBlock);
	bool disappearOnFinish();
	void setDisapearOnFinish(bool disappear);
	std::string getName();
	void setName(std::string name);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	GODPathFinder* pathFinder;

	std::string name;

	bool alwaysAttack;
	bool attackOnBlock;
	bool disappear;
};

#endif