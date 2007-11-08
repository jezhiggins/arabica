#ifndef ARABICA_XSLT_CONSTANTS_HPP
#define ARABICA_XSLT_CONSTANTS_HPP

namespace Arabica
{
namespace XSLT
{

struct StylesheetConstant
{
  static const std::string& NamespaceURI()
  {
    static std::string namespaceURI = "http://www.w3.org/1999/XSL/Transform";
    return namespaceURI;
  } // XSLTNamespaceURI

  static const std::string& Version()
  {
    static std::string version = "1.0";
    return version;
  } // Version
}; // struct StylesheetConstant

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

