#ifndef ATTRIBUTE_DEFAULTS_H
#define ATTRIBUTE_DEFAULTS_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = default_string_adaptor<string_type> >
struct AttributeDefaults
{
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;
  
    const stringT required;
    const stringT implied;
    const stringT fixed;

    AttributeDefaults() :
      required(string_adaptorT().makeStringT("#REQUIRED")),
      implied(string_adaptorT().makeStringT("#IMPLIED")),
      fixed(string_adaptorT().makeStringT("#FIXED"))
    {
    } // AttributeDefaults
}; // struct AttributeDefaults

} // namespace SAX

#endif
// end of file
