#ifndef OBJECTTEXTDISPLAY_H
#define OBJECTTEXTDISPLAY_H

#include <ogre/Ogre.h>

class DLLEXPORT ObjectTextDisplay {
public:
	ObjectTextDisplay(const Ogre::MovableObject* p, const Ogre::Camera* c, const Ogre::ColourValue colourValue);
    virtual ~ObjectTextDisplay();

	void enable(bool enable);

	void setText(const Ogre::String& text);
	void update();
protected:
	const Ogre::MovableObject* m_p;
	const Ogre::Camera* m_c;
	bool m_enabled;
	Ogre::Overlay* m_pOverlay;
	Ogre::OverlayElement* m_pText;
	Ogre::OverlayContainer* m_pContainer;
	Ogre::String m_text;
};

#endif
