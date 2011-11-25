
#ifdef _MSC_VER
// turn off the useless "template name is too long" warning
#pragma warning(disable: 4786)
#endif

#include <SAX/ArabicaConfig.hpp>

#ifdef ARABICA_USE_EXPAT
#include "SAX/wrappers/saxexpat.cpp"
#ifdef _MSC_VER
#pragma message("Pulling in Expat wrappers")
#endif
#endif

#ifdef ARABICA_USE_LIBXML2
#include "SAX/wrappers/saxlibxml2.cpp"
#ifdef _MSC_VER
#pragma message("Pulling in libxml2 wrappers")
#endif
#endif

#ifdef ARABICA_USE_XERCES
#include "SAX/wrappers/saxxerces.cpp"
#ifdef _MSC_VER
#pragma message("Pulling in Xerces wrappers")
#endif
#endif

#ifdef ARABICA_USE_MSXML
#ifdef _MSC_VER
#pragma message("Using MSXML")
#endif
#endif

#ifdef ARABICA_USE_GARDEN
#ifdef _MSC_VER
#pragma message("Using Garden")
#endif
#endif

#ifndef ARABICA_NO_CODECVT_SPECIALISATIONS
#include "convert/impl/codecvt_specialisations.cpp"
#endif 

#ifdef __GNUWIN32__
#ifdef _LIB
#include <windows.h>

BOOL APIENTRY DllMain(HINSTANCE hInst,
                      DWORD reason,
		      LPVOID reserved)
{
  return TRUE;
}
#endif
#endif
