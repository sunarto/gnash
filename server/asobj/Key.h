// 
//   Copyright (C) 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 


#ifndef __KEY_H__
#define __KEY_H__

#include "tu_config.h"
#include "as_object.h" // for inheritance
#include "fn_call.h"
#include "event_id.h"
#include "gnash.h" // for gnash::key namespace
#include "dsodefs.h"
#include <bitset>

#ifdef WIN32
#   undef _CONTROL
#   undef _SPACE
#   undef _UP
#endif

namespace gnash {

/************************************************************************
 *
 * This has been moved from action.cpp, when things are clean
 * everything should have been moved up
 *
 ************************************************************************/

class DSOEXPORT key_as_object : public as_object
{

protected:

#ifdef GNASH_USE_GC
    // Mark all key listeners as reachable
    void markReachableResources() const;
#endif // def GNASH_USE_GC

public:

    key_as_object();

    // Pass SWF keycode, returns true if currently pressed.
    bool is_key_down(int keycode);

    // Pass gnash::key::code. Changes m_last_key_event
    // and adds appropriate SWF keycode to bit array of keys
    // pressed (_unreleasedKeys)
    void set_key_down(key::code code);

    // Pass gnash::key::code. Changes m_last_key_event
    // and removes appropriate SWF keycode from bit array of keys
    // pressed (_unreleasedKeys)
    void set_key_up(key::code code);
    
    int get_last_key() const;

    /// Responsible for user defined key events handlers only;
    /// take over both characters and non-characters object.
    void notify_listeners(const event_id& key_event_type);

private:
    /// bit-array for recording the unreleased keys
    std::bitset<key::KEYCOUNT> _unreleasedKeys;   

    typedef std::list<boost::intrusive_ptr<as_object> > Listeners;
    Listeners _listeners;

    int _lastKeyEvent;
};

void key_class_init(as_object& global);

} // end of gnash namespace

// __KEY_H__
#endif

