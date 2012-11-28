#include "GODCalculations.h"

GODCombat* GODCombat::instance = NULL;

GODCombat::GODCombat() {
	srand( (unsigned int)time(NULL) );
}

GODCombat::~GODCombat() {
	delete instance;
}

GODCombat* GODCombat::getInstance() {
	if (instance == NULL) {
		instance = new GODCombat();
	}
	return instance;
}

// TODO de volgende code moet als er meer wordt aangepast dan alleen health
// worden aangepast.
int GODCombat::attack(GODUnitObject* attacker, GODUnitObject* defender) {
	long currentTime = GetTickCount();
	if (currentTime <= attacker->getLastAttack()+attacker->getAttribute(GODUnitObject::ATTACKSPEED) || attacker->getAttribute(GODUnitObject::RANGE) == 0) {
		return -3;
	}
	attacker->setLastAttack(currentTime);

	if (attacker->isDead() || defender->isDead()) {
		return -1;
	}

	if (chanceOnModifiedAttack(GODUnitObject::MISSRATE, attacker)) {
		return -2;
	}

	int attackPower = attacker->getAttribute(GODUnitObject::ATTACKPOWER);
	// crit = 25-75% attackPower improvement
	if (chanceOnModifiedAttack(GODUnitObject::CRITRATE, attacker)) {
		double critRate = 1.0+(((double)(rand()%50)+25.0)/100.0);
		attackPower = (int)(attackPower*critRate);
		critRate = 0;
	}

	int armor = defender->getAttribute(GODUnitObject::ARMOR);
	if (armor > 1000) {
		armor = 1000; // Om te zorgen dat je armor niet hoger dan een attack kan worden
	}

	double armorReduction = 1.0-((armor*0.05)/100.0); // 1000 = 50% attack reduction, 0 = 0%
	double attackReduction = 1.0+(((double)(rand()%20)-15.0) / 100); // -15% - 5% incasatie voor randomness
	double attack = (attackPower*armorReduction)*attackReduction;

	while (defender->isUsed()) {}
	defender->setUsed(true);
	if (!attacker->isDead()) {
		currentTime = GetTickCount();
		attacker->setLastAttack(currentTime);
		GODAddEvents::getInstance()->addGODObject(new GODArrowObject(GODAddEvents::getInstance()->nextId(), attacker->getLocation(), defender->getLocation()));
		defender->modifyAttribute(GODUnitObject::HEALTH,((int)attack)*-1);
	}
	defender->setUsed(false);

	// Cleaning service
	attackPower = 0;
	armorReduction = 0;
	attackReduction = 0;
	return (int)attack;
}

bool GODCombat::chanceOnModifiedAttack(int attribute, GODUnitObject* unit) {
	return ((rand()%(100/unit->getAttribute(attribute))) == 0);
}

void GODCombat::combat(std::vector<GODUnitObject*> *attackersPointer, std::vector<GODUnitObject*> *defendersPointer, GODUnitControl *unitControl) {
	std::vector<GODUnitObject*> defenders = *defendersPointer;
	std::vector<GODUnitObject*> attackers = *attackersPointer;
	for (int i=0; i<(int)attackers.size(); i++) {
		GODUnitObject* attacker = attackers.at(i);
		if (attacker->isDead()) {
			continue;
		}
		GODUnitObject* defender = attacker->getTarget();
		if (defender == NULL) {
			continue;
		}
		if (defender->isDead()) {
			continue;
		}
		if (!GODMissionControl::getInstance()->isAttacking(attacker)) {
			continue;
		}
		int dmg = attack(attacker,defender);
		if (dmg == -3) {
			continue;
		}
		defender->setDamage(dmg);
		if (defender->isDead()) {
			if (defenders.size() > 1) {
				defenders.clear();
				std::vector<GODUnitObject*> newPopulation = unitControl->getAliveUnits(defender->getOwner());
				defenders.assign(newPopulation.begin(),newPopulation.end());
				newPopulation.clear();
			} else {
				defenders.clear();
			}
			attacker->setTarget(NULL);
			printf("%i Died\n", defender->getId());
		}
	}
}