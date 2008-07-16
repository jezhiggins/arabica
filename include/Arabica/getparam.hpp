#ifndef ARABICA_UTILS_GET_PARAM_HPP
#define ARABICA_UTILS_GET_PARAM_HPP

#ifdef HAVE_BOOST
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#endif

namespace Arabica
{

struct nil_t { };

#ifdef HAVE_BOOST
template <typename BaseT, typename DefaultT, typename T0, typename T1>
struct get_param
{
  typedef typename boost::mpl::if_<
      boost::is_base_and_derived<BaseT, T0>
      , T0
      , typename boost::mpl::if_<
            boost::is_base_and_derived<BaseT, T1>
          , T1
          , DefaultT
        >::type
    >::type type;
}; // get_param
#else
template <typename T0, typename DefaultT>
struct chosen_type { typedef T0 type; };

template <typename DefaultT>
struct chosen_type<Arabica::nil_t, DefaultT> { typedef DefaultT type; };

template <typename BaseT, typename DefaultT, typename T0, typename T1>
struct get_param
{
  typedef typename chosen_type<T0, DefaultT>::type type;
};
#endif

template <typename string_type, typename T0, typename T1>
struct get_string_adaptor
{
  typedef typename get_param<Arabica::string_adaptor_tag, 
                             Arabica::default_string_adaptor<string_type>, 
                             T0, 
                             T1>::type type;
};

} // namespace Arabica

#endif

