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


ifndef ARABICA_PARSERCONFIG_H
define ARABICA_PARSERCONFIG_H

#ifdef USE_LIBXML2
include <SAX/wrappers/saxlibxml2.h>
undef DEF_SAX_P
define DEF_SAX_P libxml2_wrapper
#ifdef _MSC_VER
message("Including libxml2")
comment(lib, "libxml2.lib")
#endif
#endif
#ifdef USE_MSXML
#ifndef _MSC_VER
error "Can only use MSXML on Windows"
#endif
message("Including MSXML")
include <SAX/wrappers/saxmsxml2.h>
undef DEF_SAX_P
define DEF_SAX_P msxml2_wrapper
#endif 
#ifdef USE_XERCES1
include <SAX/wrappers/saxxerces.h>
undef DEF_SAX_P
define DEF_SAX_P xerces_wrapper
#ifdef _MSC_VER
message("Including Xerces 1")
comment(lib, "xerces-c_1.lib")
#endif
#endif
#ifdef USE_XERCES
include <SAX/wrappers/saxxerces.h>
undef DEF_SAX_P
define DEF_SAX_P xerces_wrapper
#ifdef _MSC_VER
message("Including Xerces")
comment(lib, "xerces-c_2.lib")
#endif
#endif
#ifdef USE_GARDEN
message("Including Garden")
include <SAX/parsers/saxgarden.h>
undef DEF_SAX_P
define DEF_SAX_P Garden
#endif
#ifdef USE_EXPAT
include <SAX/wrappers/saxexpat.h>
undef DEF_SAX_P
define DEF_SAX_P expat_wrapper
#ifdef _MSC_VER
message("Including Expat")
comment(lib, "libexpat.lib")
#endif
#endif

ifndef NO_DEFAULT_PARSER
ifdef DEF_SAX_P
namespace SAX
{
  template<class string_type>
  class XMLReader : public DEF_SAX_P<string_type> { };
} // namespace SAX
else
error "No default parser defined."
endif
endif

undef DEF_P

endif 


