#define pasty(m, n) m##n
#define include pasty(#, include)
#define ifdef pasty(#, ifdef)
#define ifndef pasty(#, ifndef)
#define endif pasty(#, endif)
#define define pasty(#, define)
#define message pasty(#, pragma message)
#define undef pasty(#, undef)
#define error pasty(#, error)
#define else pasty(#, else)
#define comment pasty(#, pragma comment)

#ifdef _MSC_VER
// turn off the useless "template name is too long" warning
#pragma warning(disable: 4786)
#endif 

define NO_DEFAULT_PARSER
include <SAX/XMLReader.h>

#ifdef USE_LIBXML2
include <SAX/wrappers/saxlibxml2.cpp>
#ifdef _MSC_VER
message("Pulling in libxml2 wrappers.")
#endif
#endif

#ifdef USE_MSXML
#ifndef _MSC_VER
error "USE_MSXML is only valid for VisualC++ builds"
#else
message("Nothing to pull in for MSXML.")
#endif
#endif 

#ifdef USE_XERCES
include <SAX/wrappers/saxxerces.cpp>
#ifdef _MSC_VER
message("Pulling in Xerces wrappers.")
#endif
#endif

#ifdef USE_GARDEN
message("Nothing to pull in for Garden.")
#endif

#ifdef USE_EXPAT
include <SAX/wrappers/saxexpat.cpp>
#ifdef _MSC_VER
message("Pulling in Expat wrappers.")
#endif	
#endif




