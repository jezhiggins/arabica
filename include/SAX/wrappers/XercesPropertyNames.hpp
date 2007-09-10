#ifndef ARABICA_XERCES_PROPERTYNAMES_H
#define ARABICA_XERCES_PROPERTYNAMES_H
/*
 * $Id$
 */

#include <Arabica/StringAdaptor.hpp>
#include <SAX/helpers/PropertyNames.hpp>

namespace Arabica
{
namespace SAX
{
  template<class string_type,
           class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
  struct XercesPropertyNames : public PropertyNames<string_type,
                                                    string_adaptor_type>
  {
    /** \name Xerces properties.
     * @{ */

    /** Used to set and get a fixed schema location for the
     * parser.
     *
     * The syntax is the same as for schemaLocation attributes in
     * instance documents: e.g, <code>"http://www.example.com
     * file_name.xsd"</code>. The user can specify more than one
     * XML Schema in the list.
     *
     * The XML Schema Recommendation explicitly states that the
     * inclusion of schemaLocation/ noNamespaceSchemaLocation
     * attributes in the instance document is only a hint; it does
     * not mandate that these attributes must be used to locate
     * schemas. Similar situation happens to <import>  element in
     * schema documents.  This property allows the user to specify
     * a list of schemas to use. If the targetNamespace of a
     * schema specified using this method matches the
     * targetNamespace of a schema occurring in the instance
     * document in schemaLocation attribute, or if the
     * targetNamespace matches the namespace attribute of <import>
     * element, the schema specified by the user using this
     * property will be used (i.e., the schemaLocation attribute
     * in the instance document or on the <import> element will be
     * effectively ignored).
     */
    const string_type externalSchemaLocation;
    /** Used to set and get a fixed no-namespace schema location
     * for the parser.
     *
     * The syntax is the same as for the noNamespaceSchemaLocation
     * attribute that may occur in an instance document:
     * e.g.<code>"file_name.xsd"</code>.
     *
     * The XML Schema Recommendation explicitly states that the
     * inclusion of schemaLocation/ noNamespaceSchemaLocation
     * attributes in the instance document is only a hint; it does
     * not mandate that these attributes must be used to locate
     * schemas. This property allows the user to specify the no
     * target namespace XML Schema Location externally. If
     * specified, the instance document's
     * noNamespaceSchemaLocation attribute will be effectively
     * ignored.
     */
    const string_type externalNoNamespaceSchemaLocation;

    /** @} */

    XercesPropertyNames() :
        externalSchemaLocation(string_adaptor_type::construct_from_utf8(
            "http://apache.org/xml/properties/schema/external-schemaLocation")),
        externalNoNamespaceSchemaLocation(string_adaptor_type::construct_from_utf8(
            "http://apache.org/xml/properties/schema/external-noNamespaceSchemaLocation"))
    {
    } // XercesPropertyNames()
  }; // class XercesPropertyNames
} // namespace SAX
} // namespace Arabica

#endif
// end of file

