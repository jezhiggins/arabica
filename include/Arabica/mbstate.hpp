#ifndef ARABICA_MBSTATE_T
#define ARABICA_MBSTATE_T

#ifdef ARABICA_NO_STD_MBSTATE_T

#ifndef ARABICA_NO_MBSTATE_T
#include <wchar.t>
namespace std {
  using ::mbstate_t;
}
#else
namespace std {
  typedef struct
  {
    int dummy;    /* So that {0} is a valid constant initializer. */
  } mbstate_t;
}
#endif 


#endif

#endif
