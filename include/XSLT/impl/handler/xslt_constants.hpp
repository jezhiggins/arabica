#ifndef ARABICA_XSLT_CONSTANTS_HPP
#define ARABICA_XSLT_CONSTANTS_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
struct StylesheetConstant
{
  static const string_type& NamespaceURI()
  {
    static string_type namespaceURI = "http://www.w3.org/1999/XSL/Transform";
    return namespaceURI;
  } // XSLTNamespaceURI

  static const string_type& Version()
  {
    static string_type version = "1.0";
    return version;
  } // Version
}; // struct StylesheetConstant

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

