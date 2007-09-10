#ifndef ARABICA_FEATURE_NAMES_H
#define ARABICA_FEATURE_NAMES_H
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
struct FeatureNames
{
    /** Reports whether this parser processes external general entities; always
     * true if validating.  */
    const string_type external_general;
    /** Reports whether this parser processes external parameter entities; always
     * true if validating.  */
    const string_type external_parameter;
    /** May be examined only during a parse, after the startDocument() callback has
     * been completed; read-only. The value is true if the document specified the
     * "standalone" flag in its XML declaration, and otherwise is false.  */
    const string_type is_standalone;
    /** True indicates that the LexicalHandler will report the beginning and end
     * of parameter entities.  */
    const string_type lexical_parameter;
    /** True indicates namespace URIs and unprefixed local names for element and
     * attribute names will be available.*/
    const string_type namespaces;
    /** True indicates XML 1.0 names (with prefixes) and attributes (including
     * xmlns* attributes) will be available. */
    const string_type namespace_prefixes;
    /**  A value of "true" indicates that system IDs in declarations will be
     * absolutized (relative to their base URIs) before reporting. (That is the
     * default behavior for all SAX2 XML parsers.) A value of "false" indicates
     * those IDs will not be absolutized; parsers will provide the base URI from
     * Locator.getSystemId(). This applies to system IDs passed in
     *
     * - DTDHandler.notationDecl(),
     * - DTDHandler.unparsedEntityDecl(), and
     * - DeclHandler.externalEntityDecl().
     *
     *It does not apply to EntityResolver.resolveEntity(), which is not used to
     report declarations, or to LexicalHandler.startDTD(), which already provides
     the non-absolutized URI. */
    const string_type resolve_dtd_uris;
    /** Returns true if the Attributes objects passed by this parser in
     * ContentHandler.startElement()  implement the org.xml.sax.ext.Attributes2
     * interface. That interface exposes additional DTD-related information, such
     * as whether the attribute was specified in the source text rather than
     * defaulted. */
    const string_type use_attributes2;
    /**  Returns true if the Locator objects passed by this parser in
     * ContentHandler.setDocumentLocator()  implement the org.xml.sax.ext.Locator2
     * interface. That interface exposes additional entity information, such as
     * the character encoding and XML version used. */
    const string_type use_locator2;
    /**  Controls whether the parser is reporting all validity errors; if true,
     * all external entities will be read. */
    const string_type validation;
    /**  Controls whether, when the namespace-prefixes feature is set, the parser
     * treats namespace declaration attributes as being in the
     * http://www.w3.org/2000/xmlns/ namespace. By default, SAX2 conforms to the
     * original "Namespaces in XML" Recommendation, which explicitly states that
     * such attributes are not in any namespace. Setting this optional flag to
     * true makes the SAX2 events conform to a later backwards-incompatible
     * revision of that recommendation, placing those attributes in a namespace.
     * */
    const string_type xmlns_uris;

    FeatureNames() :
      external_general(string_adaptor::construct_from_utf8("http://xml.org/sax/features/external-general-entities")),
      external_parameter(string_adaptor::construct_from_utf8("http://xml.org/sax/features/external-parameter-entities")),
      is_standalone(string_adaptor::construct_from_utf8("http://xml.org/sax/features/is-standalone")),
      lexical_parameter(string_adaptor::construct_from_utf8("http://xml.org/sax/features/lexical-handler/parameter-entities")),
      namespaces(string_adaptor::construct_from_utf8("http://xml.org/sax/features/namespaces")),
      namespace_prefixes(string_adaptor::construct_from_utf8("http://xml.org/sax/features/namespace-prefixes")),
      resolve_dtd_uris(string_adaptor::construct_from_utf8("http://xml.org/sax/features/resolve-dtd-uris")),
      use_attributes2(string_adaptor::construct_from_utf8("http://xml.org/sax/features/use-attributes2")),
      use_locator2(string_adaptor::construct_from_utf8("http://xml.org/sax/features/use-locator2")),
      validation(string_adaptor::construct_from_utf8("http://xml.org/sax/features/validation")),
      xmlns_uris(string_adaptor::construct_from_utf8("http://xml.org/sax/features/xmlns-uris"))
    {
    } // FeatureNames
}; // class FeatureNames

} // namespace SAX
} // namespace Arabica

#endif
// end of file
