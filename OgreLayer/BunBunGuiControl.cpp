#include "BunBunGuiControl.h"

BunBunGuiControl::BunBunGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor) {
	this->mDrawControl = mDrawControl;
	this->mTimer = mTimer;
	this->mEventProcessor = mEventProcessor;
	this->mEventProcessor->startProcessingEvents();
	this->mEventProcessor->addKeyListener(this);
    this->mEventProcessor->addMouseListener(this);
	this->mEventProcessor->addMouseMotionListener(this);
	this->mInputDevice = this->mEventProcessor->getInputReader();
	this->mGUIRenderer = new CEGUI::OgreCEGUIRenderer(mDrawControl->getWindow(), Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mDrawControl->getSceneManager());
    this->mGUISystem = new CEGUI::System(this->mGUIRenderer);
	this->mEditorGuiSheet = NULL;
    CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
}

BunBunGuiControl::~BunBunGuiControl() {
	mEventProcessor->stopProcessingEvents();
	mEventProcessor->removeKeyListener(this);
	mEventProcessor->removeMouseListener(this);
	mEventProcessor->removeMouseMotionListener(this);
    CEGUI::WindowManager::getSingleton().destroyWindow(mEditorGuiSheet);
    delete mGUISystem;
}

bool BunBunGuiControl::frameStarted(const FrameEvent& evt) {
	if (!*mDrawControl->getRunning() || mDrawControl->getWindow()->isClosed())
		return false;
	if (mTimer->getMilliseconds() > TIME_FRAME_MS) {
		int missedTimeFrames = (int)mTimer->getMilliseconds();
		missedTimeFrames = (int)(missedTimeFrames/TIME_FRAME_MS);
		if (!mDrawControl->onTimeFrame(missedTimeFrames))
			return false;
		mTimer->reset();
	}	

	return onRenderFrame();
}

bool BunBunGuiControl::frameEnded(const FrameEvent& evt) {
	return true;
}


void BunBunGuiControl::keyClicked(KeyEvent* e) {
	e->consume();
}

void BunBunGuiControl::keyPressed(KeyEvent* e) {
	e->consume();
}

void BunBunGuiControl::keyReleased(KeyEvent* e) {
	e->consume();
}

void BunBunGuiControl::keyFocusIn(KeyEvent* e) {
	e->consume();
}

void BunBunGuiControl::keyFocusOut(KeyEvent* e) {
	e->consume();
}

void BunBunGuiControl::mouseClicked(MouseEvent* e) {
	e->consume();
}

void BunBunGuiControl::mouseEntered(MouseEvent* e) {
	e->consume();
}

void BunBunGuiControl::mouseExited(MouseEvent* e) {
	e->consume();
}

void BunBunGuiControl::mousePressed(MouseEvent* e) {
    e->consume();
}

void BunBunGuiControl::mouseReleased(MouseEvent* e) {
    e->consume();
}

void BunBunGuiControl::mouseDragEntered(MouseEvent* e) {
    e->consume();
}

void BunBunGuiControl::mouseDragExited(MouseEvent* e) {
    e->consume();
}

void BunBunGuiControl::mouseDragDropped(MouseEvent* e) {
    e->consume();
}

void BunBunGuiControl::mouseMoved(MouseEvent* e)  {
    e->consume();
}

void BunBunGuiControl::mouseDragged(MouseEvent* e) { 
	e->consume();
}

void BunBunGuiControl::mouseDragMoved(MouseEvent* e) { 
	e->consume();
}

CEGUI::MouseButton BunBunGuiControl::convertOgreButtonToCegui(int buttonID) {
   switch (buttonID) {
		case MouseEvent::BUTTON0_MASK:
			return CEGUI::LeftButton;
		case MouseEvent::BUTTON1_MASK:
			return CEGUI::RightButton;
		case MouseEvent::BUTTON2_MASK:
			return CEGUI::MiddleButton;
		case MouseEvent::BUTTON3_MASK:
			return CEGUI::X1Button;
		default:
			return CEGUI::LeftButton;
   }
}
