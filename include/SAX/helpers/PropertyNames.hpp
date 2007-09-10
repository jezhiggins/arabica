#ifndef ARABICA_PROPERTY_NAMES_H
#define ARABICA_PROPERTY_NAMES_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.hpp>
#include <SAX/XMLReader.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/** The core SAX 2 parser properties. */
template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
struct PropertyNames
{
    /** @name SAX 2 Properties
     * @{ */
    /** Register a lexical handler.
     *
     * The Lexical Handler is used to see some syntax events that are essential 
     * in some applications: comments, CDATA delimiters, selected general 
     * entity inclusions, and the start and end of the DTD (and declaration of 
     * document element name). 
     * 
     * The value assigned must implement SAX::LexicalHandler. 
     */
    const string_type lexicalHandler;
    /** Register a Declaration Handler.
     *
     * Used to see most DTD declarations except those treated as lexical
     * ("document element name is ...") or which are mandatory for all SAX 
     * parsers (DTDHandler). 
     * 
     * The value assigned must implement SAX::DeclHandler */
    const string_type declHandler;
    /** @} */

    PropertyNames() :
    lexicalHandler(string_adaptor_type::construct_from_utf8("http://xml.org/sax/handlers/LexicalHandler")),
      declHandler(string_adaptor_type::construct_from_utf8("http://xml.org/sax/handlers/DeclHandler"))
    {
    } // PropertyNames
}; // struct PropertyNames

} // namespace SAX
} // namespace Arabica

#endif
// end of file
