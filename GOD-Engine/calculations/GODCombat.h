#ifndef GODCOMBAT_H
#define GODCOMBAT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../control/GODUnitControl.h"
#include "../control/GODMissionControl.h"

class DLLEXPORT GODCombat {
public:
	~GODCombat();
	static GODCombat* getInstance();
	int attack(GODUnitObject* attacker, GODUnitObject* defender);
	void combat(std::vector<GODUnitObject*> *attackers, std::vector<GODUnitObject*> *defenders, GODUnitControl *unitControl);
protected:
	GODCombat();
private:
	bool chanceOnModifiedAttack(int attribute, GODUnitObject* unit);

	static GODCombat* instance;
};

#endif