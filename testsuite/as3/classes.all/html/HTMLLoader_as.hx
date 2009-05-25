// HTMLLoader_as.hx:  ActionScript 3 "HTMLLoader" class, for Gnash.
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
import flash.html.HTMLLoader;
import flash.display.MovieClip;
#else
import flash.HTMLLoader;
import flash.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class HTMLLoader_as {
    static function main() {
        var x1:HTMLLoader = new HTMLLoader();

        // Make sure we actually get a valid class        
        if (x1 != null) {
            DejaGnu.pass("HTMLLoader class exists");
        } else {
            DejaGnu.fail("HTMLLoader class doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.authenticate == false) {
	    DejaGnu.pass("HTMLLoader.authenticate property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.authenticate property doesn't exist");
	}
	if (x1.cacheResponse == false) {
	    DejaGnu.pass("HTMLLoader.cacheResponse property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.cacheResponse property doesn't exist");
	}
	if (x1.contentHeight == 0) {
	    DejaGnu.pass("HTMLLoader.contentHeight property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.contentHeight property doesn't exist");
	}
	if (x1.contentWidth == 0) {
	    DejaGnu.pass("HTMLLoader.contentWidth property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.contentWidth property doesn't exist");
	}
	if (x1.hasFocusableContent == false) {
	    DejaGnu.pass("HTMLLoader.hasFocusableContent property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.hasFocusableContent property doesn't exist");
	}
	if (x1.height == 0) {
	    DejaGnu.pass("HTMLLoader.height property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.height property doesn't exist");
	}
	if (x1.historyLength == uint) {
	    DejaGnu.pass("HTMLLoader.historyLength property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.historyLength property doesn't exist");
	}
	if (x1.historyPosition == uint) {
	    DejaGnu.pass("HTMLLoader.historyPosition property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.historyPosition property doesn't exist");
	}
	if (x1.htmlHost == htmlHost) {
	    DejaGnu.pass("HTMLLoader.htmlHost property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.htmlHost property doesn't exist");
	}
	if (x1.loaded == false) {
	    DejaGnu.pass("HTMLLoader.loaded property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.loaded property doesn't exist");
	}
	if (x1.location == null) {
	    DejaGnu.pass("HTMLLoader.location property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.location property doesn't exist");
	}
	if (x1.manageCookies == false) {
	    DejaGnu.pass("HTMLLoader.manageCookies property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.manageCookies property doesn't exist");
	}
	if (x1.navigateInSystemBrowser == false) {
	    DejaGnu.pass("HTMLLoader.navigateInSystemBrowser property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.navigateInSystemBrowser property doesn't exist");
	}
	if (x1.paintsDefaultBackground == false) {
	    DejaGnu.pass("HTMLLoader.paintsDefaultBackground property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.paintsDefaultBackground property doesn't exist");
	}
	if (x1.pdfCapability == 0) {
	    DejaGnu.pass("HTMLLoader.pdfCapability property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.pdfCapability property doesn't exist");
	}
	if (x1.runtimeApplicationDomain == runtimeApplicationDomain) {
	    DejaGnu.pass("HTMLLoader.runtimeApplicationDomain property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.runtimeApplicationDomain property doesn't exist");
	}
	if (x1.scrollH == 0) {
	    DejaGnu.pass("HTMLLoader.scrollH property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.scrollH property doesn't exist");
	}
	if (x1.scrollV == 0) {
	    DejaGnu.pass("HTMLLoader.scrollV property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.scrollV property doesn't exist");
	}
	if (x1.textEncodingFallback == null) {
	    DejaGnu.pass("HTMLLoader.textEncodingFallback property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.textEncodingFallback property doesn't exist");
	}
	if (x1.textEncodingOverride == null) {
	    DejaGnu.pass("HTMLLoader.textEncodingOverride property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.textEncodingOverride property doesn't exist");
	}
	if (x1.useCache == false) {
	    DejaGnu.pass("HTMLLoader.useCache property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.useCache property doesn't exist");
	}
	if (x1.userAgent == null) {
	    DejaGnu.pass("HTMLLoader.userAgent property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.userAgent property doesn't exist");
	}
	if (x1.width == 0) {
	    DejaGnu.pass("HTMLLoader.width property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.width property doesn't exist");
	}
	if (x1.window == Object) {
	    DejaGnu.pass("HTMLLoader.window property exists");
	} else {
	    DejaGnu.fail("HTMLLoader.window property doesn't exist");
	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.HTMLLoader == HTMLLoader) {
	    DejaGnu.pass("HTMLLoader::HTMLLoader() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::HTMLLoader() method doesn't exist");
	}
	if (x1.cancelLoad == null) {
	    DejaGnu.pass("HTMLLoader::cancelLoad() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::cancelLoad() method doesn't exist");
	}
	if (x1.createRootWindow == HTMLLoader) {
	    DejaGnu.pass("HTMLLoader::createRootWindow() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::createRootWindow() method doesn't exist");
	}
	if (x1.getHistoryAt == HTMLHistoryItem) {
	    DejaGnu.pass("HTMLLoader::getHistoryAt() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::getHistoryAt() method doesn't exist");
	}
	if (x1.historyBack == null) {
	    DejaGnu.pass("HTMLLoader::historyBack() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::historyBack() method doesn't exist");
	}
	if (x1.historyForward == null) {
	    DejaGnu.pass("HTMLLoader::historyForward() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::historyForward() method doesn't exist");
	}
	if (x1.historyGo == null) {
	    DejaGnu.pass("HTMLLoader::historyGo() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::historyGo() method doesn't exist");
	}
	if (x1.load == null) {
	    DejaGnu.pass("HTMLLoader::load() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::load() method doesn't exist");
	}
	if (x1.loadString == null) {
	    DejaGnu.pass("HTMLLoader::loadString() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::loadString() method doesn't exist");
	}
	if (x1.reload == null) {
	    DejaGnu.pass("HTMLLoader::reload() method exists");
	} else {
	    DejaGnu.fail("HTMLLoader::reload() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

