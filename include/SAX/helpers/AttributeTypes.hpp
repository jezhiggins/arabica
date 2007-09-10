#ifndef ARABICA_ATTRIBUTE_TYPES_H
#define ARABICA_ATTRIBUTE_TYPES_H
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
struct AttributeTypes
{
    const string_type cdata;
    const string_type nmtoken;
    const string_type nmtokens;
    const string_type enumeration;
    const string_type entity;
    const string_type entities;
    const string_type id;
    const string_type idref;
    const string_type idrefs;
    const string_type notation;

    AttributeTypes() :
      cdata(string_adaptor::construct_from_utf8("CDATA")),
      nmtoken(string_adaptor::construct_from_utf8("NMTOKEN")),
      nmtokens(string_adaptor::construct_from_utf8("NMTOKENS")),
      enumeration(string_adaptor::construct_from_utf8("ENUMERATION")),
      entity(string_adaptor::construct_from_utf8("ENTITY")),
      entities(string_adaptor::construct_from_utf8("ENTITIES")),
      id(string_adaptor::construct_from_utf8("ID")),
      idref(string_adaptor::construct_from_utf8("IDREF")),
      idrefs(string_adaptor::construct_from_utf8("IDREFS")),
      notation(string_adaptor::construct_from_utf8("NOTATION"))
    {
    } // AttributeTypes
}; // struct AttributeTypes

} // namespace SAX
} // namespace Arabica

#endif
// end of file
