#ifndef ARABICA_VS6_WORKAROUND_H
#define ARABICA_VS6_WORKAROUND_H

#ifndef ARABICA_VS6_WORKAROUND
#error "This file is only for use in Visual C++/Studio v6 builds."
#endif 

#undef max
#undef min

namespace std {
  typedef ::mbstate_t mbstate_t;

  template<typename T>
  T max(T a, T b) 
  { 
    return (a > b) ? b : a; 
  }

  template<typename T>
  T min(T a, T b) 
  { 
    return (a < b) ? a : b; 
  }
}


#endif
