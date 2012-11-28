#include "BunBunMissionGuiControl.h"

BunBunMissionGuiControl::BunBunMissionGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor) : BunBunGuiControl(mDrawControl, mTimer, mEventProcessor) {
	this->mDrawControl = (BunBunMissionDrawControl*)mDrawControl;
	this->textIsClean = true;
	createScene();
	setupEventHandlers();
}

BunBunMissionGuiControl::~BunBunMissionGuiControl() {
	this->textIsClean = true;
}

bool BunBunMissionGuiControl::onRenderFrame() {
	GODMissionControl* missionControl = GODMissionControl::getInstance();
	if (missionControl->isMoneyValueChanged() || missionControl->isLivesValueChanged()) {
		handleTitlebarChange(missionControl->getCurrentMoney(), missionControl->getCurrentLives());
	}
	if (missionControl->isFinished()) {
		handleFinishedMission(missionControl->isVictorious());
		missionControl->pause();
	}
	if (mDrawControl->getSelectedUnit() != NULL) {
		textIsClean = false;
		handleSelectionText("Health", mDrawControl->getSelectedUnit()->getAttribute(GODUnitObject::HEALTH), mDrawControl->getSelectedUnit()->getUnitType()->getHealth());
		handleSelectionText("Armor", mDrawControl->getSelectedUnit()->getAttribute(GODUnitObject::ARMOR), mDrawControl->getSelectedUnit()->getUnitType()->getArmor());
		handleSelectionText("AttackPower", mDrawControl->getSelectedUnit()->getAttribute(GODUnitObject::ATTACKPOWER), mDrawControl->getSelectedUnit()->getUnitType()->getAttackPower());
		handleSelectionText("Price", mDrawControl->getSelectedUnit()->getAttribute(GODUnitObject::PRICE), -1);
	} else if (!textIsClean) {
		textIsClean = true;
		handleSelectionText("Health", -1, -1);
		handleSelectionText("Armor", -1, -1);
		handleSelectionText("AttackPower", -1, -1);
		handleSelectionText("Price", -1, -1);
	}
	return mDrawControl->onRenderFrame();
}

void BunBunMissionGuiControl::createScene() {
	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    mGUISystem->setDefaultMouseCursor((CEGUI::utf8*)"BunBunWar", (CEGUI::utf8*)"BunBunCursor");
    CEGUI::MouseCursor::getSingleton().setImage("BunBunWar", "BunBunCursor");
	mGUISystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
	try {
		mEditorGuiSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"BunBunMissionGUI.layout");
	} catch(CEGUI::Exception &e) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, e.getMessage().c_str(), "Error parsing CEGUI menu.");
	}
	mGUISystem->setGUISheet(mEditorGuiSheet);
	setGuiAlpha(true);
}

void BunBunMissionGuiControl::setupEventHandlers() {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/Quit")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleQuit, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/MainMenu")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleMainMenu, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/Pause")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handlePause, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/BuildTower")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleBuildTower, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/UpgradeTower")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleUpgradeTower, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/DeleteTower")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleDeleteTower, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionPopup/Button/Close")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleQuit, this));
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI")->subscribeEvent(CEGUI::FrameWindow::EventRollupToggled, CEGUI::Event::Subscriber(&BunBunMissionGuiControl::handleRollupToggle, this));
}

void BunBunMissionGuiControl::mouseMoved(MouseEvent* e)  {
    CEGUI::System::getSingleton().injectMouseMove(
            e->getRelX() * mGUIRenderer->getWidth(), 
            e->getRelY() * mGUIRenderer->getHeight());
	CEGUI::Point point = CEGUI::MouseCursor::getSingleton().getPosition();
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* window = wmgr.getWindow((CEGUI::utf8*)"root")->getTargetChildAtPosition(point);

	if (window == NULL) {
		setGuiAlpha(true);
		if (mDrawControl->isBuildingTower() && !GODMissionControl::getInstance()->isFinished())
			mDrawControl->mouseMovedPlayField(point.d_x, point.d_y);
	} else {
		setGuiAlpha(false);
	}
	mDrawControl->mouseMoved(point.d_x, point.d_y, e->getRelZ());
	e->consume();
}

void BunBunMissionGuiControl::mouseDragged(MouseEvent* e) { 
	mDrawControl->mouseDragged(e->getRelX(), e->getRelY(), mInputDevice->getMouseButton(1));
	e->consume();
}

void BunBunMissionGuiControl::mousePressed(MouseEvent* e) {
    CEGUI::System::getSingleton().injectMouseButtonDown(
        convertOgreButtonToCegui(e->getButtonID()));
	CEGUI::Point point = CEGUI::MouseCursor::getSingleton().getPosition();
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* window = wmgr.getWindow((CEGUI::utf8*)"root")->getTargetChildAtPosition(point);
	
	if (mDrawControl->isBuildingTower() && e->getButtonID() == 32) {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/BuildTower")->setText("Build Tower");
		mDrawControl->resetGhostUnit();
		mDrawControl->setBuildingTower(false);
	}

	if (window == NULL && !GODMissionControl::getInstance()->isFinished()) {
		mDrawControl->mousePressed(point.d_x, point.d_y, e->getButtonID());
	}

	if (mDrawControl->getSelectedUnit() != NULL && mDrawControl->getSelectedUnit()->getOwner() == 1) {
		if (mDrawControl->getSelectedUnit()->canUpgrade()) {
			wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/UpgradeTower")->setEnabled(true);
		}
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/DeleteTower")->setEnabled(true);
	} else {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/UpgradeTower")->setEnabled(false);
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/DeleteTower")->setEnabled(false);
	}

    e->consume();
}

void BunBunMissionGuiControl::mouseReleased(MouseEvent* e) {
    CEGUI::System::getSingleton().injectMouseButtonUp(
        convertOgreButtonToCegui(e->getButtonID()));
    e->consume();
}

bool BunBunMissionGuiControl::handleRollupToggle(const CEGUI::EventArgs& e) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::FrameWindow* window = (CEGUI::FrameWindow*)wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI");
	if (!window->isRolledup()) {
		window->setPosition(mGUIOriginalPoint);
	} else {
		setGuiAlpha(true);
		mGUIOriginalPoint = wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI")->getPosition();
		float y = (float)(1.0f / mGUIRenderer->getHeight()) * window->getChild(0)->getAbsoluteHeight();
		window->setPosition(CEGUI::Point(0.0,1.0-y));
	}
	return true;
}

bool BunBunMissionGuiControl::handleQuit(const CEGUI::EventArgs& e) {
	mDrawControl->exitApplication();
	return true;
}

bool BunBunMissionGuiControl::handleMainMenu(const CEGUI::EventArgs& e) {
	mDrawControl->topApplication();
	return true;
}

bool BunBunMissionGuiControl::handleUpgradeTower(const CEGUI::EventArgs& e) {
	OgreUnit* unit = mDrawControl->getSelectedUnit();
	GODUnitTypeObject* unitType = GODMissionControl::getInstance()->getUnitTypeControl()->getUnitTypeWithIdAndNextUpgrade(unit->getUnitType()->getId(), unit->getUnitType()->getUpgrade());
	if (unitType != NULL && GODMissionControl::getInstance()->decreaseMoney(unitType->getPrice())) {
		unit->modifyAttribute(GODUnitObject::PRICE, unit->getUnitType()->getPrice());
		int health = unit->getUnitModifier()->getHealth()-(unitType->getHealth()-unit->getUnitType()->getHealth());
		if (health < 0) {
			health = 0;
		}
		unit->getUnitModifier()->setHealth(health);
		unit->setUnitType(unitType);
		unitType = GODMissionControl::getInstance()->getUnitTypeControl()->getUnitTypeWithIdAndNextUpgrade(unit->getUnitType()->getId(), unit->getUnitType()->getUpgrade());
		if (unitType == NULL) {
			CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
			wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/UpgradeTower")->setEnabled(false);
			unit->setUpgrade(false);
		}
	}
	return true;
}

bool BunBunMissionGuiControl::handleDeleteTower(const CEGUI::EventArgs& e) {
	OgreUnit* unit = mDrawControl->getSelectedUnit();
	GODMissionControl::getInstance()->increaseMoney(unit->getAttribute(GODUnitObject::PRICE)/2);
	unit->reset(mDrawControl->getSceneManager());
	GODMissionControl::getInstance()->getLandscapeControl()->removeUnit(unit);
	unit->modifyAttribute(GODUnitObject::HEALTH, ~(unit->getUnitType()->getHealth()+1));
	mDrawControl->setSelectedUnit(NULL);
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/DeleteTower")->setEnabled(false);
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/UpgradeTower")->setEnabled(false);
	return true;
}

bool BunBunMissionGuiControl::handleBuildTower(const CEGUI::EventArgs& e) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	if (mDrawControl->isBuildingTower()) {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/BuildTower")->setText("Build Tower");
		mDrawControl->resetGhostUnit();
	} else {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/BuildTower")->setText("Cancel");
	}
	mDrawControl->setBuildingTower(!mDrawControl->isBuildingTower());
	return true;
}

void BunBunMissionGuiControl::handleFinishedMission(bool victory) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* popup = wmgr.getWindow((CEGUI::utf8*)"BunBunMissionPopup");
	if (victory) {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionPopup/Text/Text")->setText("Victory!");
		popup->setText("Victory!");
	} else {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionPopup/Text/Text")->setText("Defeat!");
		popup->setText("Defeat!");
	}
	popup->setVisible(true);
}

void BunBunMissionGuiControl::handleTitlebarChange(int money, int lives) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI")->setText("Money: "+StringConverter::toString(money)+" Lives: "+StringConverter::toString(lives));
}

void BunBunMissionGuiControl::handleSelectionText(String name, int newValue, int originalValue) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	if (newValue == -1 && originalValue == -1) {
		wmgr.getWindow((CEGUI::utf8*)("BunBunMissionGUI/Text/"+name).c_str())->setText("");
	} else if (originalValue == -1) {
		wmgr.getWindow((CEGUI::utf8*)("BunBunMissionGUI/Text/"+name).c_str())->setText(name+": "+StringConverter::toString(newValue));
	} else {
		wmgr.getWindow((CEGUI::utf8*)("BunBunMissionGUI/Text/"+name).c_str())->setText(name+": "+StringConverter::toString(newValue)+"/"+StringConverter::toString(originalValue));
	}
}

bool BunBunMissionGuiControl::handlePause(const CEGUI::EventArgs& e) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	if (GODMissionControl::getInstance()->isPaused()) {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/Pause")->setText("Pause");
	} else {
		wmgr.getWindow((CEGUI::utf8*)"BunBunMissionGUI/Button/Pause")->setText("Continue");
	}
	GODMissionControl::getInstance()->pause();
	return true;
}

void BunBunMissionGuiControl::setGuiAlpha(bool alphaOn) {
	CEGUI::FrameWindow* guiWindow = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"BunBunMissionGUI");
	if (alphaOn) {
		guiWindow->setAlpha(0.7f);
	} else {
		guiWindow->setAlpha(1.0f);
	}
}
