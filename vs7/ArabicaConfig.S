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


ifndef ARABICA_ARABICA_CONFIG_H
define ARABICA_ARABICA_CONFIG_H

#ifdef ARABICA_NO_WCHAR_T
#undef ARABICA_NO_WCHAR_T
define ARABICA_NO_WCHAR_T
#endif

#ifdef _MSC_VER
#if (_MSC_VER < 1300)
define ARABICA_VS6_WORKAROUND
#endif

define ARABICA_NO_CODECVT_SPECIALISATIONS
#endif

#ifndef NO_BOOST
define HAVE_BOOST
#endif

define ARABICA_USE_WINSOCK
define ARABICA_WINDOWS

#if defined(_DEBUG) || (__DEBUG__)
define ARABICA_DEBUG
#endif

#ifdef USE_LIBXML2
#undef USE_LIBXML2
define USE_LIBXML2
#endif

#ifdef USE_EXPAT
#undef USE_EXPAT
define USE_EXPAT
#endif

#ifdef USE_XERCES
#undef USE_XERCES
define USE_XERCES
#endif

#ifdef USE_GARDEN
#undef USE_GARDEN
define USE_GARDEN
define ARABICA_NO_WCHAR_T
#endif

#ifdef USE_MSXML
#undef USE_MSXML
define USE_MSXML
#endif			
				
endif


