#ifndef ARABICA_PARSERCONFIG_H
#define ARABICA_PARSERCONFIG_H

#ifdef ARABICA_USE_LIBXML2
#include <SAX/wrappers/saxlibxml2.hpp>
#undef DEF_SAX_P
#define DEF_SAX_P libxml2_wrapper
#ifdef _MSC_VER
#pragma message("Including libxml2")
#pragma comment(lib, "libxml2.lib")
#endif
#endif

#ifdef ARABICA_USE_MSXML
#ifndef _MSC_VER
#error "Can only use MSXML on Windows"
#endif
#pragma message("Including MSXML")
#include <SAX/wrappers/saxmsxml2.hpp>
#undef DEF_SAX_P
#define DEF_SAX_P msxml2_wrapper
#endif 

#ifdef ARABICA_USE_XERCES
#include <SAX/wrappers/saxxerces.hpp>
#undef DEF_SAX_P
#define DEF_SAX_P xerces_wrapper
#ifndef ARABICA_NOT_USE_PRAGMA_LINKER_OPTIONS
#ifdef _MSC_VER
#pragma message("Including Xerces v3")
#ifdef _DEBUG
#pragma comment(lib, "xerces-c_3D.lib")
#else
#pragma comment(lib, "xerces-c_3.lib")
#endif
#endif
#endif
#endif

#ifdef ARABICA_USE_GARDEN
#ifdef _MSC_VER
#pragma message("Including Garden")
#endif
#include <SAX/parsers/saxgarden.hpp>
#undef DEF_SAX_P
#define DEF_SAX_P Garden
#endif

#ifdef ARABICA_USE_EXPAT
#include <SAX/wrappers/saxexpat.hpp>
#undef DEF_SAX_P
#define DEF_SAX_P expat_wrapper
#ifdef _MSC_VER
#ifndef ARABICA_NOT_USE_PRAGMA_LINKER_OPTIONS
#pragma message("Including Expat")
#ifndef XML_STATIC
#pragma comment(lib, "libexpat.lib")
#else
#pragma comment(lib, "libexpatMT.lib")
#endif
#endif
#endif
#endif

#ifdef _MSC_VER
#ifndef ARABICA_NOT_USE_PRAGMA_LINKER_OPTIONS
#pragma comment(lib, "wsock32.lib")
#endif
#endif


#ifndef NO_DEFAULT_PARSER
#ifdef DEF_SAX_P
namespace Arabica
{
namespace SAX
{
template<class string_type, class T0 = Arabica::nil_t, class T1 = Arabica::nil_t>
  class XMLReader : public DEF_SAX_P<string_type, T0, T1> { };
} // namespace SAX
} // namespace Arabica
#else
#error "No default parser defined."
#endif
#endif

#undef DEF_P

#endif 


