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


ifndef ARABICA_CONFIG_H
define ARABICA_CONFIG_H

#ifdef ARABICA_NO_WCHAR_T
#undef ARABICA_NO_WCHAR_T
define pasty(ARABICA, _NO_WCHAR_T) 1
#endif

endif // ARABICA_CONFIG_H


