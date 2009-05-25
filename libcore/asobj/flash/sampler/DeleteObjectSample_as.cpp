// DeleteObjectSample_as.cpp:  ActionScript "DeleteObjectSample" class, for Gnash.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
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
//

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "sampler/DeleteObjectSample_as.h"
#include "log.h"
#include "fn_call.h"
#include "smart_ptr.h" // for boost intrusive_ptr
#include "builtin_function.h" // need builtin_function
#include "GnashException.h" // for ActionException

namespace gnash {

// Forward declarations
namespace {
    as_value deleteobjectsample_ctor(const fn_call& fn);
    void attachDeleteObjectSampleInterface(as_object& o);
    void attachDeleteObjectSampleStaticInterface(as_object& o);
    as_object* getDeleteObjectSampleInterface();

}

// extern (used by Global.cpp)
void deleteobjectsample_class_init(as_object& global)
{
    static boost::intrusive_ptr<builtin_function> cl;

    if (!cl) {
        cl = new builtin_function(&deleteobjectsample_ctor, getDeleteObjectSampleInterface());
        attachDeleteObjectSampleStaticInterface(*cl);
    }

    // Register _global.DeleteObjectSample
    global.init_member("DeleteObjectSample", cl.get());
}

namespace {

void
attachDeleteObjectSampleInterface(as_object& o)
{
}

void
attachDeleteObjectSampleStaticInterface(as_object& o)
{

}

as_object*
getDeleteObjectSampleInterface()
{
    static boost::intrusive_ptr<as_object> o;
    if ( ! o ) {
        o = new as_object();
        attachDeleteObjectSampleInterface(*o);
    }
    return o.get();
}

as_value
deleteobjectsample_ctor(const fn_call& fn)
{
    boost::intrusive_ptr<as_object> obj = new DeleteObjectSample_as;

    return as_value(obj.get()); // will keep alive
}

} // anonymous namespace 
} // gnash namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

