/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/

/**
    @file 
        Terrain.cpp
    @brief
        Shows OGRE's terrain rendering plugin.
*/

#include <bunbunwar/OgreLayer.h>
#include <bunbunwar/GODEngine.h>
#include <bunbunwar/Utilities.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
	GODMissionObject* missionObject = new GODMissionObject();
	GODLandscapeControl* landscapeControl = new GODLandscapeControl();
	GODSizeConstructor* sizeConstructor = new GODSizeConstructor();
	GODGridConstructor* gridConstructor = new GODGridConstructor();
	GODUnitTypeObject* unitTypeObject = new GODUnitTypeObject();
	GODUnitTypeControl* unitTypeControl = new GODUnitTypeControl();
	GODGameTypeObject* gameTypeObject = new GODGameTypeObject();
	GODLandscapeAreaObject* landscapeAreaObject = new GODLandscapeAreaObject();
	GODWaveObject* waveObject = new GODWaveObject();
	GODWaveControl* waveControl = GODWaveControl::getInstance();

	GODXMLMapping* mapping = GODXMLMapping::getInstance();
	mapping->addXMLMapping(missionObject);
	mapping->addXMLMapping(landscapeControl);
	mapping->addXMLMapping(sizeConstructor);
	mapping->addXMLMapping(gridConstructor);
	mapping->addXMLMapping(unitTypeObject);
	mapping->addXMLMapping(unitTypeControl);
	mapping->addXMLMapping(gameTypeObject);
	mapping->addXMLMapping(landscapeAreaObject);
	mapping->addXMLMapping(waveObject);
	mapping->addXMLMapping(waveControl);

	MainApplication::go();
    return 0;
}

#ifdef __cplusplus
}
#endif
