#ifndef ARABICA_ATTRIBUTE_DEFAULTS_H
#define ARABICA_ATTRIBUTE_DEFAULTS_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
struct AttributeDefaults
{
    const string_type required;
    const string_type implied;
    const string_type fixed;

    AttributeDefaults() :
      required(string_adaptor::construct_from_utf8("#REQUIRED")),
      implied(string_adaptor::construct_from_utf8("#IMPLIED")),
      fixed(string_adaptor::construct_from_utf8("#FIXED"))
    {
    } // AttributeDefaults
}; // struct AttributeDefaults

} // namespace SAX
} // namespace Arabica

#endif
// end of file
