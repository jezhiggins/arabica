/*
 * SAXlib.cpp - Pulls in the appropriate bits of the library, depending
 * on the configured options.
 *
 * $Id$
 */

#ifdef _MSC_VER
// turn off the useless "template name is too long" warning
#pragma warning(disable: 4786)
#pragma comment(lib, "Utilities.lib")
#endif 

#define NO_DEFAULT_PARSER
#include <SAX/XMLReader.h>

#ifdef USE_LIBXML2
#pragma message("Pulling in libxml2")
#include <SAX/wrappers/saxlibxml2.cpp>
#ifdef _MSC_VER
// automagically link libxml2 if using VC++
#pragma comment(lib, "libxml2.lib")
#endif
#endif

#ifdef USE_MSXML
#pragma message("Nothing to pull in for MSXML")
// nothing extra to pull in for MSXML
#endif 

#ifdef USE_XERCES
#pragma message("Nothing to pull in for Xerces")
// nothing extra to pull in for Xerces
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