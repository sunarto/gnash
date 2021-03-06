// 
//   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010,
//   2011 Free Software Foundation, Inc
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef GNASH_ASOBJ_VIDEO_AS_H
#define GNASH_ASOBJ_VIDEO_AS_H

// Forward declarations
namespace gnash {
    class Global_as;
    struct ObjectURI;
    class as_object;
}

namespace gnash {

/// Native function to create a plain object with Video properties
//
/// This adds properties to the prototype, but does not add a Video
/// DisplayObject.
as_object* createVideoObject(Global_as& gl);

void video_class_init(as_object& global, const ObjectURI& uri);

void registerVideoNative(as_object& global);

} // namespace gnash

#endif
