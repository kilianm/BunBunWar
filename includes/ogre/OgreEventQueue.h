/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
/***************************************************************************
OgreEventQueue.h  -  
	The EventQueue holds InputEvents.
	It doesn't create or delete the objects, just stores them.

-------------------
begin                : Nov 19 2002
copyright            : (C) 2002 by Kenny Sabir
email                : kenny@sparksuit.com
***************************************************************************/

#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include "OgrePrerequisites.h"

namespace Ogre {

	/** This class holds InputEvents given to it by the EventProcessor in a FIFO queue. */
    class _OgreExport EventQueue
    {
    protected:
		std::queue<InputEvent*> mEventQueue;
		bool mActivateEventQueue;

    public:
        EventQueue();
        virtual ~EventQueue();
		void push(InputEvent* e);
		InputEvent* pop();


		/**
		 * Turn the queue on so it can pop and push InputEvents
		 */
		void activateEventQueue(bool set);

        /* Adrian Cearnau - modified the return type from int to size_t and made the method const. */
		size_t getSize() const;

    };



}


#endif //__EVENT_QUEUE_H__
