#ifndef PROPERTYNAMES_H
#define PROPERTYNAMES_H
/*
 * $Id$
 */

#include <SAX/helpers/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = default_string_adaptor<string_type> >
struct PropertyNames
{
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;

    const stringT lexicalHandler;
    const stringT declHandler;

    PropertyNames() :
      lexicalHandler(string_adaptorT().makeStringT("http://xml.org/sax/handlers/LexicalHandler")),
      declHandler(string_adaptorT().makeStringT("http://xml.org/sax/handlers/DeclHandler"))
    {
    } // PropertyNames
}; // struct PropertyNames

} // namespace SAX

#endif
// end of file
