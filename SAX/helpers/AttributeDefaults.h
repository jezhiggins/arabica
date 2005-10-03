#ifndef ARABICA_ATTRIBUTE_DEFAULTS_H
#define ARABICA_ATTRIBUTE_DEFAULTS_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
#include <Utils/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
struct AttributeDefaults
{
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;
  
    const stringT required;
    const stringT implied;
    const stringT fixed;

    AttributeDefaults() :
      required(string_adaptorT::construct_from_utf8("#REQUIRED")),
      implied(string_adaptorT::construct_from_utf8("#IMPLIED")),
      fixed(string_adaptorT::construct_from_utf8("#FIXED"))
    {
    } // AttributeDefaults
}; // struct AttributeDefaults

} // namespace SAX

#endif
// end of file
