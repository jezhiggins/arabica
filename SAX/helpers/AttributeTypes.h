#ifndef ARABICA_ATTRIBUTE_TYPES_H
#define ARABICA_ATTRIBUTE_TYPES_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
#include <Utils/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
struct AttributeTypes
{
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;
  
    const stringT cdata;
    const stringT nmtoken;
    const stringT nmtokens;
    const stringT enumeration;
    const stringT entity;
    const stringT entities;
    const stringT id;
    const stringT idref;
    const stringT idrefs;
    const stringT notation;

    AttributeTypes() :
      cdata(string_adaptorT::construct_from_utf8("CDATA")),
      nmtoken(string_adaptorT::construct_from_utf8("NMTOKEN")),
      nmtokens(string_adaptorT::construct_from_utf8("NMTOKENS")),
      enumeration(string_adaptorT::construct_from_utf8("ENUMERATION")),
      entity(string_adaptorT::construct_from_utf8("ENTITY")),
      entities(string_adaptorT::construct_from_utf8("ENTITIES")),
      id(string_adaptorT::construct_from_utf8("ID")),
      idref(string_adaptorT::construct_from_utf8("IDREF")),
      idrefs(string_adaptorT::construct_from_utf8("IDREFS")),
      notation(string_adaptorT::construct_from_utf8("NOTATION"))
    {
    } // AttributeTypes
}; // struct AttributeTypes

} // namespace SAX

#endif
// end of file
