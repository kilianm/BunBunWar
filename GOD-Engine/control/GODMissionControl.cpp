#include "GODControl.h"

GODMissionControl* GODMissionControl::instance = NULL;

GODMissionControl::GODMissionControl() {
	missionObject = NULL;
	gameTypeObject = NULL;
	thread = NULL;
	moneyValueChanged = true;
	finished = false;
	victory = false;
	defeat = false;
	paused = false;
	pathBlocked = false;
	missionActive = false;
}

GODMissionControl::~GODMissionControl() {
	resetMission();
}

GODMissionControl* GODMissionControl::getInstance() {
	if (instance == NULL) {
		instance = new GODMissionControl();
	}
	return instance;
}

void GODMissionControl::resetMission() {
	GODAddEvents::getInstance()->clear();
	GODEvents::getInstance()->clear();
	if (GODWaveControl::getInstance()->isSpawningWaves()) {
		GODWaveControl::getInstance()->resetWaves();
	}
	if (missionObject) {
		delete missionObject;
		missionObject = NULL;
	}
	if (gameTypeObject) {
		delete gameTypeObject;
		gameTypeObject = NULL;
	}
	moneyValueChanged = true;
	finished = false;
	victory = false;
	defeat = false;
	paused = false;
	pathBlocked = false;
	missionActive = false;
}

typedef DWORD (WINAPI *routine_t)(void*);

void GODMissionControl::loadMission(GODGameTypeObject* gameTypeObject, GODMissionObject* missionObject) {
	if (this->isMissionActive()) {
		stopMission();
	} 
	if (gameTypeObject && missionObject) {
		resetMission();
	}
	setGameTypeObject(gameTypeObject);
	GODUnitControl* unitControl = new GODUnitControl();
	missionObject->setUnitControl(unitControl);
	setMissionObject(missionObject);
	getPathFinder()->setLandscapeControl(getLandscapeControl());
	isMissionLoaded();
}

GODGameTypeObject* GODMissionControl::getGameTypeObject() {
	return this->gameTypeObject;
}

GODMissionObject* GODMissionControl::getMissionObject() {
	return this->missionObject;
}

bool GODMissionControl::isLoaded() {
	return !(this->missionObject == NULL || this->gameTypeObject == NULL);
}

void GODMissionControl::isMissionLoaded() {
	if (!isLoaded())
		throw new GODException("GODMissionControlNoMissionLoaded","GODMissionControl::isMissionLoaded()");
}

void GODMissionControl::setGameTypeObject(GODGameTypeObject* gameTypeObject) {
	this->gameTypeObject = gameTypeObject;
}

void GODMissionControl::setMissionObject(GODMissionObject* missionObject) {
	this->missionObject = missionObject;
}

void GODMissionControl::startMission() {
	isMissionLoaded();
	missionActive = true;
	GODWaveControl::getInstance()->startWaves();
	this->thread = CreateThread(0,0, (routine_t)mission, NULL, 0, NULL);
}

void GODMissionControl::stopMission() {
	if (missionActive) {
		missionActive = false;
		CloseHandle(thread);
		thread = NULL;
	}
}

void GODMissionControl::increaseMoney(int money) {
	isMissionLoaded();
	missionObject->setCurrentMoney(missionObject->getCurrentMoney()+money);
	this->moneyValueChanged = true;
}

bool GODMissionControl::decreaseMoney(int money) {
	isMissionLoaded();
	if (missionObject->getCurrentMoney() - money < 0) {
		return false;
	}
	missionObject->setCurrentMoney(missionObject->getCurrentMoney()-money);
	this->moneyValueChanged = true;
	return true;
}

bool GODMissionControl::isMoneyValueChanged() {
	if (this->moneyValueChanged) {
		this->moneyValueChanged = false;
		return true;
	}
	return false;
}

int GODMissionControl::getCurrentLives() {
	isMissionLoaded();
	return this->missionObject->getLives();
}

bool GODMissionControl::decreaseLive() {
	isMissionLoaded();
	if (missionObject->getLives() - 1 < 0) {
		return false;
	}
	missionObject->setLives(missionObject->getLives()-1);
	this->livesValueChanged = true;
	return true;
}

bool GODMissionControl::isLivesValueChanged() {
	if (this->livesValueChanged) {
		this->livesValueChanged = false;
		return true;
	}
	return false;
}

bool GODMissionControl::isMissionActive() {
	return this->missionActive;
}

int GODMissionControl::getCurrentMoney() {
	isMissionLoaded();
	return missionObject->getCurrentMoney();
}

int GODMissionControl::getTotalMoney() {
	isMissionLoaded();
	return missionObject->getTotalMoney();
}

void GODMissionControl::setPathBlocked(bool pathBlocked) {
	isMissionLoaded();
	this->pathBlocked = pathBlocked;
}

bool GODMissionControl::isPathBlocked() {
	isMissionLoaded();
	return this->pathBlocked;
}

void GODMissionControl::setVictory() {
	isMissionLoaded();
	this->defeat = false;
	this->victory = true;
	this->finished = true;
}

void GODMissionControl::setDefeat() {
	isMissionLoaded();
	this->defeat = true;
	this->victory = false;
	this->finished = true;
}

bool GODMissionControl::isVictorious() {
	isMissionLoaded();
	return this->victory;
}

bool GODMissionControl::isDefeated() {
	isMissionLoaded();
	return this->defeat;
}

bool GODMissionControl::isFinished() {
	isMissionLoaded();
	return this->finished;
}

bool GODMissionControl::isPaused() {
	isMissionLoaded();
	return this->paused;
}

void GODMissionControl::pause() {
	isMissionLoaded();
	this->paused = !this->paused;
}

//TODO needs rewrite!
void GODMissionControl::mission() {
	GODMissionControl* missionControl = GODMissionControl::getInstance();
	GODUnitControl* unitControl = missionControl->getUnitControl();
	while (missionControl->isMissionActive()) {
		while (missionControl->isPaused()) {
			Sleep(10);
		}
		std::vector<GODUnitObject*> ownUnits = unitControl->getAliveUnits(1);
		std::vector<GODUnitObject*> enemyUnits = unitControl->getAliveUnits(0);

		int aliveCountOwn = (int)ownUnits.size();
		int aliveCountEnemy = (int)enemyUnits.size();

		GODCombat* combat = GODCombat::getInstance();

		combat->combat(&ownUnits, &enemyUnits, unitControl);
		combat->combat(&enemyUnits, &ownUnits, unitControl);

		aliveCountOwn = (int)ownUnits.size();
		aliveCountEnemy = (int)enemyUnits.size();

		if (GODWaveControl::getInstance()->isDoneWaveSpawns() && aliveCountEnemy <= 0) {
			if (!GODWaveControl::getInstance()->hasNextWave()) {
				missionControl->setVictory();
				GODWaveControl::getInstance()->stopWaves();
			} else {
				GODMissionControl::getInstance()->increaseMoney(GODWaveControl::getInstance()->getReward());
				GODWaveControl::getInstance()->waveDied();
			}
		}

		ownUnits.clear();
		enemyUnits.clear();

		aliveCountOwn = 0;
		aliveCountEnemy = 0;

		Sleep(10);
	}
}

GODPathFinder* GODMissionControl::getPathFinder() {
	isMissionLoaded();
	return gameTypeObject->getPathFinder();
}

void GODMissionControl::finishedMove(int unitId) {
	isMissionLoaded();
	GODUnitObject* unit = getUnitControl()->getUnitWithId(unitId);
	if (unit != NULL) {
		getLandscapeControl()->cleanGhosts(unit);
		GODEvents::getInstance()->removeGODObject(unit);
		if (!unit->isDead() && !getLandscapeControl()->getFinish()->intersect(unit->getLocation())) {
			this->setPathBlocked(!getPathFinder()->moveUnit(unit));
		} else if (!unit->isDead()) {
			unit->modifyAttribute(GODUnitObject::HEALTH, ~(unit->getUnitType()->getHealth()));
			if (this->gameTypeObject->disappearOnFinish()) {
				GODEvents::getInstance()->addGODObject(unit);
			}
			if (!this->decreaseLive()) {
				setDefeat();
				GODWaveControl::getInstance()->stopWaves();
			}
		} else {
			GODLandscapeObject* obj = getLandscapeControl()->getLandscapeObject(unit->getLocation());
			if (obj->getItem() != NULL || obj->getGridKind() != GODLandscapeObject::LANDSCAPE_EMPTY) {
				obj->setGridKind(GODLandscapeObject::LANDSCAPE_EMPTY);
				obj->setItem(NULL);
			}
		}
	}
}

// Since there is no mission data, add them yourself
void GODMissionControl::addUnit(GODUnitObject* unit) {
	isMissionLoaded();
	getUnitControl()->addUnit(unit);
}

bool GODMissionControl::hasCondition(int unitGroup, int alive) {
	isMissionLoaded();
	if (victoryCondition(unitGroup, alive)) {
		return true;
	} else if (defeatCondition(unitGroup, alive)) {
		return true;
	}
	return false;
}

bool GODMissionControl::victoryCondition(int unitGroup, int alive) {
	isMissionLoaded();
	if (unitGroup == 1 && alive == 0) {
		return true;
	}
	return false;
}

bool GODMissionControl::defeatCondition(int unitGroup, int alive) {
	isMissionLoaded();
	if (unitGroup == 0 && alive == 0) {
		return true;
	}
	return false;
}

GODUnitControl* GODMissionControl::getUnitControl() {
	isMissionLoaded();
	return missionObject->getUnitControl();
}

GODLandscapeControl* GODMissionControl::getLandscapeControl() {
	isMissionLoaded();
	return missionObject->getLandscapeControl();
}

GODUnitTypeControl* GODMissionControl::getUnitTypeControl() {
	isMissionLoaded();
	return missionObject->getUnitTypeControl();
}

bool GODMissionControl::isAttacking(GODUnitObject* unit) {
	if (unit->getOwner() == 0 && (gameTypeObject->isAlwaysAttack() || (gameTypeObject->isAttackOnBlock() && this->isPathBlocked())))
		return true;
	else if (unit->getOwner() == 1)
		return true;
	return false;
}