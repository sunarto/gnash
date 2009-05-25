// ConvolutionFilter_as.hx:  ActionScript 3 "ConvolutionFilter" class, for Gnash.
//
// Generated by gen-as3.sh on: 20090515 by "rob". Remove this
// after any hand editing loosing changes.
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

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.filters.ConvolutionFilter;
import flash.display.MovieClip;
#else
import flash.ConvolutionFilter;
import flash.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class ConvolutionFilter_as {
    static function main() {
        var x1:ConvolutionFilter = new ConvolutionFilter();

        // Make sure we actually get a valid class        
        if (x1 != null) {
            DejaGnu.pass("ConvolutionFilter class exists");
        } else {
            DejaGnu.fail("ConvolutionFilter class doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.alpha == 0) {
	    DejaGnu.pass("ConvolutionFilter.alpha property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.alpha property doesn't exist");
	}
	if (x1.bias == 0) {
	    DejaGnu.pass("ConvolutionFilter.bias property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.bias property doesn't exist");
	}
	if (x1.clamp == false) {
	    DejaGnu.pass("ConvolutionFilter.clamp property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.clamp property doesn't exist");
	}
	if (x1.color == uint) {
	    DejaGnu.pass("ConvolutionFilter.color property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.color property doesn't exist");
	}
	if (x1.divisor == 0) {
	    DejaGnu.pass("ConvolutionFilter.divisor property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.divisor property doesn't exist");
	}
	if (x1.matrix == 0) {
	    DejaGnu.pass("ConvolutionFilter.matrix property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.matrix property doesn't exist");
	}
	if (x1.matrixX == 0) {
	    DejaGnu.pass("ConvolutionFilter.matrixX property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.matrixX property doesn't exist");
	}
	if (x1.matrixY == 0) {
	    DejaGnu.pass("ConvolutionFilter.matrixY property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.matrixY property doesn't exist");
	}
	if (x1.preserveAlpha == false) {
	    DejaGnu.pass("ConvolutionFilter.preserveAlpha property exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter.preserveAlpha property doesn't exist");
	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.ConvolutionFilter == 0) {
	    DejaGnu.pass("ConvolutionFilter::ConvolutionFilter() method exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter::ConvolutionFilter() method doesn't exist");
	}
	if (x1.clone == BitmapFilter) {
	    DejaGnu.pass("ConvolutionFilter::clone() method exists");
	} else {
	    DejaGnu.fail("ConvolutionFilter::clone() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

