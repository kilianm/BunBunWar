#include "BunBunMenuGuiControl.h"

BunBunMenuGuiControl::BunBunMenuGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor) : BunBunGuiControl(mDrawControl, mTimer, mEventProcessor) {
	this->mDrawControl = (BunBunMenuDrawControl*)mDrawControl;
	this->selectedGameType = NULL;
	this->selectedMission = NULL;
	createScene();
	setupEventHandlers();
}

BunBunMenuGuiControl::~BunBunMenuGuiControl() {
}

bool BunBunMenuGuiControl::onRenderFrame() {
	if (selectedGameType && selectedMission) {
		CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Button/Start")->setEnabled(true);
	} else {
		CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Button/Start")->setEnabled(false);
	}
	return mDrawControl->onRenderFrame();
}

void BunBunMenuGuiControl::createScene() {
	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    mGUISystem->setDefaultMouseCursor((CEGUI::utf8*)"BunBunWar", (CEGUI::utf8*)"BunBunCursor");
    CEGUI::MouseCursor::getSingleton().setImage("BunBunWar", "BunBunCursor");
	mGUISystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
	try {
		mEditorGuiSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"BunBunMenuGUI.layout");
	} catch(CEGUI::Exception &e) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, e.getMessage().c_str(), "Error parsing CEGUI menu.");
	}
	mGUISystem->setGUISheet(mEditorGuiSheet);

	gameTypeData = retrieveObjects("..\\gametypes\\*.bunbungametype", "../gametypes/");

	CEGUI::Combobox* objectComboBox = (CEGUI::Combobox*)CEGUI::WindowManager::getSingleton().getWindow("BunBunMenuStartGame/ComboBox/GameType");
	CEGUI::ListboxTextItem* item;
	float originalHeight = objectComboBox->getHeight();

	for(std::list<GameData>::iterator it = gameTypeData.begin(); it != gameTypeData.end(); it++ ) {
		struct GameData gameData = (GameData)*it;
		GODGameTypeObject* gameTypeObject = (GODGameTypeObject*)gameData.godXmlObject;
		item = new CEGUI::ListboxTextItem((CEGUI::utf8*)gameTypeObject->getName().c_str(), gameData.id);
		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		item->setSelectionColours(CEGUI::colour(80.0f, 80.0f, 80.0f));
		objectComboBox->addItem(item);
		objectComboBox->setHeight(originalHeight+(originalHeight*0.4f*(gameData.id+1)));
	}

	CEGUI::Listbox* objectListBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("BunBunMenuStartGame/Listbox/Map");
	std::list<String> mapList = retrieveDirectoryListing("..\\maps\\*.bunbunmap");
	int i = 0;
	for(std::list<String>::iterator it = mapList.begin(); it != mapList.end(); it++ ) {
		String filename = (String)*it;
		item = new CEGUI::ListboxTextItem((CEGUI::utf8*)filename.c_str(), i);
		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		item->setSelectionColours(CEGUI::colour(80.0f, 80.0f, 80.0f));
		objectListBox->addItem(item);
	}
}

void BunBunMenuGuiControl::setupEventHandlers() {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuGUI/Button/StartGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleStartGame, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuGUI/Button/Options")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleOptions, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuGUI/Button/Quit")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleQuit, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Button/Start")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleStartGameStart, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Button/Cancel")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleStartGameCancel, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/ComboBox/GameType")->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleGameTypeChange, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Listbox/Map")->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&BunBunMenuGuiControl::handleMissionChange, this));
}

void BunBunMenuGuiControl::mouseMoved(MouseEvent* e)  {
    CEGUI::System::getSingleton().injectMouseMove(
            e->getRelX() * mGUIRenderer->getWidth(), 
            e->getRelY() * mGUIRenderer->getHeight());
	e->consume();
}

void BunBunMenuGuiControl::mousePressed(MouseEvent* e) {
    CEGUI::System::getSingleton().injectMouseButtonDown(
        convertOgreButtonToCegui(e->getButtonID()));
    e->consume();
}

void BunBunMenuGuiControl::mouseReleased(MouseEvent* e) {
    CEGUI::System::getSingleton().injectMouseButtonUp(
        convertOgreButtonToCegui(e->getButtonID()));
    e->consume();
}

bool BunBunMenuGuiControl::handleStartGame(const CEGUI::EventArgs& e) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* startGameWindow = wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame");
	startGameWindow->setVisible(true);
	return true;
}

bool BunBunMenuGuiControl::handleOptions(const CEGUI::EventArgs& e) {
	return true;
}

bool BunBunMenuGuiControl::handleQuit(const CEGUI::EventArgs& e) {
	mDrawControl->exitApplication();
	return true;
}

bool BunBunMenuGuiControl::handleStartGameStart(const CEGUI::EventArgs& e) {
	if (selectedGameType && selectedMission) {
		this->mDrawControl->loadMission(selectedGameType, selectedMission);
	} else {
		CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"BunBunMenuStartGame/Button/Start")->setEnabled(false);
	}
	return true;
}

bool BunBunMenuGuiControl::handleStartGameCancel(const CEGUI::EventArgs& e) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* startGameWindow = wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame");
	startGameWindow->setVisible(false);
	return true;
}

bool BunBunMenuGuiControl::handleGameTypeChange(const CEGUI::EventArgs& e) {
	CEGUI::Combobox* objectComboBox = (CEGUI::Combobox*)CEGUI::WindowManager::getSingleton().getWindow("BunBunMenuStartGame/ComboBox/GameType");
	CEGUI::ListboxTextItem* item = (CEGUI::ListboxTextItem*)objectComboBox->getSelectedItem();
	if (item) {
		for(std::list<GameData>::iterator it = gameTypeData.begin(); it != gameTypeData.end(); it++ ) {
			struct GameData gameData = (GameData)*it;
			if (item->getID() == gameData.id) {
				selectedGameType = (GODGameTypeObject*)gameData.godXmlObject;
			}
		}
	} else {
		selectedGameType = NULL;
	}
	return true;
}

bool BunBunMenuGuiControl::handleMissionChange(const CEGUI::EventArgs& e) {
	CEGUI::Listbox* objectListBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("BunBunMenuStartGame/Listbox/Map");
	CEGUI::ListboxTextItem* item = (CEGUI::ListboxTextItem*)objectListBox->getFirstSelectedItem();
	if (item) {
		GODXMLParser* parser = new GODXMLParser();
		String xmlLocation = "../maps/" + (String)item->getText().c_str();
		parser->parseDocument((char*)xmlLocation.c_str());
		selectedMission = (GODMissionObject*)parser->getFinalObject();
	} else {
		selectedMission = NULL;
	}
	updateMissionInfo();
	return true;
}

void BunBunMenuGuiControl::updateMissionInfo() {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* mapInfoNameKey = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Name/Key");
	CEGUI::Window* mapInfoNameValue = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Name/Value");
	CEGUI::Window* mapInfoSizeKey = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Size/Key");
	CEGUI::Window* mapInfoSizeValue = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Size/Value");
	CEGUI::Window* mapInfoLivesKey = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Lives/Key");
	CEGUI::Window* mapInfoLivesValue = (CEGUI::Window*)wmgr.getWindow((CEGUI::utf8*)"BunBunMenuStartGame/MapInfo/Lives/Value");
	if (selectedMission) {
		String name = selectedMission->getName();
		int sizeX = selectedMission->getLandscapeControl()->getWidth();
		int sizeY = selectedMission->getLandscapeControl()->getHeight();
		int lives = selectedMission->getLives();
		mapInfoNameValue->setText(name);
		mapInfoSizeValue->setText(StringConverter::toString(sizeX) + " x " + StringConverter::toString(sizeY));
		mapInfoLivesValue->setText(StringConverter::toString(lives));
		mapInfoNameKey->setVisible(true);
		mapInfoNameValue->setVisible(true);
		mapInfoSizeKey->setVisible(true);
		mapInfoSizeValue->setVisible(true);
		mapInfoLivesKey->setVisible(true);
		mapInfoLivesValue->setVisible(true);
	} else {
		mapInfoNameKey->setVisible(false);
		mapInfoNameValue->setVisible(false);
		mapInfoSizeKey->setVisible(false);
		mapInfoSizeValue->setVisible(false);
		mapInfoLivesKey->setVisible(false);
		mapInfoLivesValue->setVisible(false);
	}
}

std::list<GameData> BunBunMenuGuiControl::retrieveObjects(String win32SearchPath, String xmlPath) {
	std::list<GameData> gameDataList;
	std::list<String> fileList = retrieveDirectoryListing(win32SearchPath);
	GODXMLParser* parser;
	int i = 0;
	for(std::list<String>::iterator it = fileList.begin(); it != fileList.end(); it++ ) {
		parser = new GODXMLParser();
		String xmlLocation = xmlPath + (String)*it;
		parser->parseDocument((char*)xmlLocation.c_str());
		GODXMLObjectParser* gameTypeObject = parser->getFinalObject();
		delete parser;
		struct GameData sGameData;
		sGameData.id = i;
		sGameData.filename = (String)*it;
		sGameData.godXmlObject = gameTypeObject;
		gameDataList.push_back(sGameData);
		i++;
	}    
	return gameDataList;
}

std::list<String> BunBunMenuGuiControl::retrieveDirectoryListing(String win32SearchPath) {
	std::list<String> stringList;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(win32SearchPath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			stringList.push_back(String(FindFileData.cFileName));
		} while (FindNextFile(hFind, &FindFileData));
	}
	FindClose(hFind);
	return stringList;
}