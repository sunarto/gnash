// rc.cpp:  "Run Command" configuration file, for Gnash.
// 
//   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010 Free Software
//   Foundation, Inc
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

// This is generated by autoconf
#ifdef HAVE_CONFIG_H
# include "gnashconfig.h"
#endif

#include "StringPredicates.h"
#include "log.h"
#include "crc.h"

#ifdef HAVE_PWD_H
# include <pwd.h>
#endif

#include <sys/types.h>
#include "GnashSystemIOHeaders.h" // for getuid()
#include <sys/stat.h>
#include <boost/cstdint.hpp>

#include <cctype>  // for toupper
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace gnash;

/// \namespace cygnal
///	This namespace is for all the Cygnal specific classes.
namespace cygnal {

/// \brief Return the default instance of RC file,
CRcInitFile&
CRcInitFile::getDefaultInstance()
{
	// TODO: allocate on the heap and provide a destroyDefaultInstance,
	//       for finer control of destruction order
	static CRcInitFile crcfile;
	return crcfile;
}

CRcInitFile::CRcInitFile()
    : _port_offset(0),
      _testing(false),
      _threading(false),
      _fdthread(100),
      _netdebug(false),
      _admin(false),
      _certfile("server.pem"),
      _certdir("/etc/pki/tls")
{
//    GNASH_REPORT_FUNCTION;
    loadFiles();
}

//Never destroy (TODO: add a destroyDefaultInstance)
CRcInitFile::~CRcInitFile()
{
//    GNASH_REPORT_FUNCTION;    
}

/// \brief Load all the configuration files.
///	This includes parsing the default .gnashrc file for
///	Gnash settings that control the swf parser and virtual
///	machine. These setting can be overridden in the
///	.cygnalrc file, plus the Cygnal specific file has
///	options only used by Cygnal.
bool
CRcInitFile::loadFiles()
{
//    GNASH_REPORT_FUNCTION;
    
    // Check the default system location
    string loadfile = "/etc/cygnalrc";
    parseFile(loadfile);
    
    // Check the default config location
    loadfile = "/usr/local/etc/cygnalrc";
    parseFile(loadfile);
    
    // Check the users home directory
    char *home = getenv("HOME");
    if (home) {
        loadfile = home;
        loadfile += "/.cygnalrc";
        parseFile(loadfile);
    }

    // Check the GNASHRC environment variable
    char *cygnalrc = getenv("CYGNALRC");
    if (cygnalrc) {
        loadfile = cygnalrc;
        return parseFile(loadfile);
    }
    
    return false;
}

/// \brief Parse and load configuration file
///
/// @param filespec The path and file name of the disk file to parse.
///
/// @return True if the file was parsed successfully, false if not.
bool
CRcInitFile::parseFile(const std::string& filespec)
{
//     GNASH_REPORT_FUNCTION;
    struct stat stats;
    string action;
    string variable;
    string value;
    ifstream in;

	StringNoCaseEqual noCaseCompare;
    
//  log_debug ("Seeing if %s exists", filespec);
    if (filespec.size() == 0) {
        return false;
    }
    
    if (stat(filespec.c_str(), &stats) == 0) {
        in.open(filespec.c_str());
        
        if (!in) {
            log_error(_("Couldn't open file: %s"), filespec.c_str());
            return false;
        }
        
        // Read in each line and parse it
        do {

	    // Make sure action is empty, otherwise the last loop (with no new
	    // data) keeps action, variable and value from the previous loop. This
	    // causes problems if set blacklist or set whitelist are last, because
	    // value is erased while parsing and the lists are thus deleted.
	    action.clear();

            // Get the first token
            in >> action;

            // Ignore comment lines
            if (action[0] == '#') {
                // suck up the rest of the line
                char name[128];
                in.getline(name, 128);
                continue;
            } 
            
	    // Get second token
            in >> variable;

            // cout << "Parsing " << variable << endl;

	    // Read in rest of line for parsing.
            getline(in, value);

	    // Erase leading spaces.
            string::size_type position = value.find_first_not_of(' ');
            if(position != string::npos) value.erase(0, position);

            if (noCaseCompare(variable, "debuglog")) {
                expandPath (value);
                setDebugLog(value);
                continue;
            }

            if (noCaseCompare(variable, "documentroot") ) {
                setDocumentRoot(value);
                continue;
            }

            if (noCaseCompare(variable, "cgiroot") ) {
                setCgiRoot(value);
                continue;
            }

            if (noCaseCompare(variable, "documentroot") ) {
                _wwwroot = value;
                continue;
            }
            
            if (noCaseCompare(variable, "CertDir") ) {
                expandPath(value);
                _certdir = value;
                continue;
            }
            
            if (noCaseCompare(variable, "CertFile") ) {
                expandPath(value);
                _certfile = value;
                continue;
            }
                        
            bool test;
            bool threads;
	    bool netdebug;
	    bool admin;
            uint32_t num;

            // Get the standard options inherited froom Gnash's config file
            if ( extractSetting(test, "actionDump", variable, value) )
                useParserDump(test);
            else if ( extractSetting(test, "parserDump", variable, value) )
                useActionDump(test);
            else if ( extractNumber(num, "verbosity", variable, value) )
                verbosityLevel(num);

            // Get the options specific to Cygnal's config file.
            else if ( extractSetting(admin, "admin", variable, value) )
                setAdminFlag(admin);
            else if ( extractSetting(netdebug, "netdebug", variable, value) )
                setNetDebugFlag(netdebug);
            else if ( extractSetting(test, "testing", variable, value) )
                setTestingFlag(test);
            else if ( extractSetting(threads, "threading", variable, value) )
                setThreadingFlag(threads);
	    else if (extractNumber(num, "fdThread", variable, value) )
		setFDThread(num);
            else if (extractNumber(num, "portOffset", variable, value) )
		setPortOffset(num);

        } while (!in.eof());

    } else {
        if (in) {
            in.close();
        }
        return false;
    }  
    
    if (in) {
        in.close();
    }

    return true;
}

/// \brief Dump the internal data of this class in a human readable form.
/// @remarks This should only be used for debugging purposes.
void
CRcInitFile::dump(std::ostream& os) const
{
    os << endl << "Dump CRcInitFile:" << endl;
    os << "\tVerbosity Level: " << _verbosity << endl;
    os << "\tDump ActionScript processing: "
         << ((_actionDump)?"enabled":"disabled") << endl;
    os << "\tDump parser info: "
         << ((_parserDump)?"enabled":"disabled") << endl;
    os << "\tActionScript coding errors verbosity: "
         << ((_verboseASCodingErrors)?"enabled":"disabled") << endl;
    os << "\tPort Offset: " << _port_offset << endl;
    os << "\tThreading support: "
         << ((_threading)?"enabled":"disabled") << endl;
    os << "\tSpecial Testing output for Gnash: "
         << ((_testing)?"enabled":"disabled") << endl;

//    RcInitFile::dump();
}

} // end of namespace cygnal

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

