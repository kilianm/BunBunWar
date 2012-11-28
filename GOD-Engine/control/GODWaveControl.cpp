#include "GODWaveControl.h"

GODWaveControl* GODWaveControl::instance = NULL;

GODWaveControl* GODWaveControl::getInstance() {
	if (instance == NULL) {
		instance = new GODWaveControl();
	}
	return instance;
}

GODWaveControl::GODWaveControl() {
	this->startSpawnNextWave = false;
	this->doneWaveSpawns = false;
	this->spawningWaves = false;
	this->currentWave = NULL;
	this->thread = NULL;
}

GODWaveControl::~GODWaveControl() {
	resetWaves();
}

typedef DWORD (WINAPI *routine_t)(void*);

void GODWaveControl::startWaves() {
	this->thread = CreateThread(0,0, (routine_t)spawnWaves, NULL, 0, NULL);
	this->startSpawnNextWave = true;
	this->spawningWaves = true;
}

void GODWaveControl::resetWaves() {
	while ((signed)waves.size() > 0) {
		GODWaveObject* wave = *(waves.begin());
		waves.pop_front();
		delete wave;
	}
	this->startSpawnNextWave = false;
	this->spawningWaves = false;
	this->doneWaveSpawns = false;
	if (this->currentWave) {
		delete this->currentWave;
		this->currentWave = NULL;
	}
	stopWaves();
	this->thread = NULL;
}

void GODWaveControl::waveDied() {
	this->startSpawnNextWave = true;
	this->doneWaveSpawns = false;
}

bool GODWaveControl::startSpawningNextWave() {
	return this->startSpawnNextWave;
}

void GODWaveControl::stopWaves() {
	if (thread != NULL) {
		spawningWaves = false;
		CloseHandle(thread);
	}
}

bool GODWaveControl::isDoneWaveSpawns() {
	return this->doneWaveSpawns;
}

bool GODWaveControl::isSpawningWaves() {
	return this->spawningWaves;
}

void GODWaveControl::setDoneWaveSpawns(bool doneWaveSpawns) {
	this->doneWaveSpawns = doneWaveSpawns;
}

GODWaveObject* GODWaveControl::nextWave() {
	if (waves.size() == 0) {
		return NULL;
	}
	GODWaveObject* wave = *(waves.begin());
	waves.pop_front();
	this->startSpawnNextWave = false;
	this->currentWave = wave;
	return wave;
}

bool GODWaveControl::hasNextWave() {
	return (waves.size()>0);
}

int GODWaveControl::getReward() {
	if (this->currentWave != NULL) {
		int reward = this->currentWave->getReward();
		delete this->currentWave;
		this->currentWave = NULL;
		return reward;
	}
	return 0;
}

void GODWaveControl::spawnWaves() {
	GODWaveControl* waveControl = GODWaveControl::getInstance();
	GODMissionControl* missionControl = GODMissionControl::getInstance();
	GODLandscapeControl* landscapeControl = missionControl->getLandscapeControl();
	GODLandscapeAreaObject* startArea = landscapeControl->getStart();
	GODLandscapeAreaObject* finishArea = landscapeControl->getStart();
	while (waveControl->isSpawningWaves()) {
		if (waveControl->startSpawningNextWave()) {
			if (!waveControl->hasNextWave()) {
				waveControl->stopWaves();
			}
			GODWaveObject* wave = waveControl->nextWave();
			GODUnitTypeObject* unitType = missionControl->getUnitTypeControl()->getUnitTypeWithIdAndUpgrade(wave->getUnitType(), wave->getUpgrade());
			GODUnitControl* unitControl = missionControl->getUnitControl();
			int spawns = wave->getAmount();
			while (waveControl->isSpawningWaves() && spawns > 0) {
				while (missionControl->isPaused()) {
					Sleep(10);
				}
				int startX = startArea->getGrid()->getX()+(rand()%startArea->getSize()->getWidth());
				int startY = startArea->getGrid()->getY()+(rand()%startArea->getSize()->getHeight());
				int finishX = finishArea->getGrid()->getX()+(rand()%finishArea->getSize()->getWidth());
				int finishY = finishArea->getGrid()->getY()+(rand()%finishArea->getSize()->getHeight());
				Utilities_GridLocation* start = new Utilities_GridLocation(startX, startY);
				Utilities_GridLocation* end = new Utilities_GridLocation(finishX, finishY);
				GODPathObject* path = new GODPathObject(start, end);
				GODTempUnitObject* unit = new GODTempUnitObject(GODAddEvents::getInstance()->nextId(), 0, unitType, path, new Utilities_Size(1,1));
				GODAddEvents::getInstance()->addGODObject(unit);
				
				spawns -= 1;
				Sleep(unitType->getMovement()*1000);
			}
			waveControl->setDoneWaveSpawns(true);
			if (!waveControl->hasNextWave()) {
				waveControl->stopWaves();
			}
		}
		Sleep(10);
	}
}

std::string GODWaveControl::XML_OBJECT_NAME = "waves";

std::string GODWaveControl::getXMLObjectName() {
	return XML_OBJECT_NAME;
}

GODXMLObjectParser* GODWaveControl::parseXMLObject(GODXMLObject* object) {
	resetWaves();
	while (object->hasNextChild()) {
		GODXMLObject* child = object->nextChild();
		GODWaveObject* parsed = (GODWaveObject*)GODXMLMapping::getInstance()->getXMLMapping(child->getName())->parseXMLObject(child);
		waves.push_back(parsed);
	}
	return NULL;
}
