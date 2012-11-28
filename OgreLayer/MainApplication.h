#ifndef __MainApplication_H__
#define __MainApplication_H__

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <ogre/Ogre.h>
#include <ogre/OgreConfigFile.h>

#include "BunBunApplication.h"
#include "BunBunMenuApplication.h"
#include "BunBunMissionApplication.h"

using namespace Ogre;

class DLLEXPORT MainApplication {
public:
	static void go();

protected:
	static const int APPLICATION_MENU = 1;
	static const int APPLICATION_MISSION = 2;

	static bool exitApplication;
	static int lastApplication;
	static int nextApplication;
	static Root* mRoot;
	static EventProcessor* mEventProcessor;

	static bool initialize();
};


#endif
