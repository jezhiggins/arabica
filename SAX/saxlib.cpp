/*
 * SAXlib.cpp - Pulls in the appropriate bits of the library, depending
 * on the configured options.  The required libraries built within this
 * package are:
 *     SAXlib
 *     Utility
 *     - the selected parser(s)
 *
 * $Id$
 */

#ifdef _MSC_VER
// turn off the useless "template name is too long" warning
#pragma warning(disable: 4786)
#endif 

#define NO_DEFAULT_PARSER
#include <SAX/XMLReader.h>

#ifdef USE_LIBXML2
#pragma message("Pulling in libxml2")
#include <SAX/wrappers/saxlibxml2.cpp>
// automagically link libxml2 if using VC++
#ifdef _MSC_VER
#pragma comment(lib, "libxml2.lib")
#endif
#endif

#ifdef USE_MSXML
#ifndef _MSC_VER
#error "USE_MSXML is only valid for VisualC++ builds"
#else
#pragma message("Nothing to pull in for MSXML")
#endif
// nothing extra to pull in for MSXML
#endif 

#ifdef USE_XERCES
// automagically link Xerces if using VC++
#ifndef _MSC_VER
#pragma message("Nothing to pull in for Xerces")
#else
#pragma message("Pulling in Xerces")
#pragma comment(lib, "xerces-c_1.lib")
#endif
#endif

#ifdef USE_GARDEN
#pragma message("Nothing to pull in for Garden")
// nothing extra to pull in for Garden
#endif

#ifdef USE_EXPAT
#pragma message("Pulling in Expat")
#include <SAX/wrappers/saxexpat.cpp>
#ifdef _MSC_VER
// automagically link expat if using VC++
#pragma comment(lib, "expat.lib")
#endif
#endif

// end of file