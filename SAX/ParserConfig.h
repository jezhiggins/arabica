#ifndef ParserConfig_h // -*- C++ -*-
#  define ParserConfig_h

/**
 * Uncomment below what you use: expat, libxml2, xerces (1 or 2), msxml2
 * or garden.
 *
 */

// #  define USE_EXPAT
#  define USE_LIBXML2
// #  define USE_XERCES
// #  define USE_MSXML
// #  define USE_XERCES1
// #  define USE_XERCES
// #  define USE_GARDEN

#ifndef DEF_SAX_P
#  ifdef USE_EXPAT
// #  define DEF_SAX_P expat_wrapper
#  endif
#  ifdef USE_LIBXML2
#    define DEF_SAX_P libxml2_wrapper
#  endif
#  ifdef USE_MSXML
// #  define DEF_SAX_P msxml2_wrapper
#  endif
#  ifdef USE_GARDEN
// #  define DEF_SAX_P Garden
#  endif
#  if defined(USE_XERCES) || defined(USE_XERCES1)
// #  define DEF_SAX_P xerces_wrapper
#  endif
#endif


#  ifdef USE_EXPAT
#    include <SAX/wrappers/saxexpat.h>
#  endif

#  ifdef USE_LIBXML2
#    include <SAX/wrappers/saxlibxml2.h>
#  endif

#  ifdef USE_MSXML
#    include <SAX/wrappers/saxmsxml2.h>
#  endif

#  if defined(USE_XERCES) || defined(USE_XERCES1)
#    include <SAX/wrappers/saxxerces.h>
#  endif

#  ifdef USE_GARDEN
#    include <SAX/wrappers/saxgarden.h>
#  endif


#  ifndef NO_DEFAULT_PARSER
#    ifdef DEF_SAX_P
namespace SAX
{
  template<class string_type, class wrapper = DEF_SAX_P<string_type> >
  class XMLReader : public wrapper { };
}
#    else
#      error "No default parser defined."
#    endif
#  endif // NO_DEFAULT_PARSER

# endif
