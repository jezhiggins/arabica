#ifndef ATTRIBUTE_TYPES_H
#define ATTRIBUTE_TYPES_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = default_string_adaptor<string_type> >
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
      cdata(string_adaptorT().makeStringT("CDATA")),
      nmtoken(string_adaptorT().makeStringT("NMTOKEN")),
      nmtokens(string_adaptorT().makeStringT("NMTOKENS")),
      enumeration(string_adaptorT().makeStringT("ENUMERATION")),
      entity(string_adaptorT().makeStringT("ENTITY")),
      entities(string_adaptorT().makeStringT("ENTITIES")),
      id(string_adaptorT().makeStringT("ID")),
      idref(string_adaptorT().makeStringT("IDREF")),
      idrefs(string_adaptorT().makeStringT("IDREFS")),
      notation(string_adaptorT().makeStringT("NOTATION"))
    {
    } // AttributeTypes
}; // struct AttributeTypes

} // namespace SAX

#endif
// end of file
