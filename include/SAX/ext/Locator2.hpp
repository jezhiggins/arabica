#ifndef ARABICA_LOCATOR2_H
#define ARABICA_LOCATOR2_H

// Locator2.h
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <SAX/Locator.hpp>

namespace Arabica
{
namespace SAX 
{

/**
 * SAX2 extension to augment the entity information provided though a Locator.
 * <p>
 * If an implementation supports this extension, the Locator provided in 
 * ContentHandler.setDocumentLocator()  will implement this interface, 
 * and the http://xml.org/sax/features/use-locator2 feature flag will have 
 * the value true.
 * <p>
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 */
template<class string_type, class string_adaptor>
class Locator2 : public Locator<string_type, string_adaptor>
{
public:
  typedef string_type stringT;

  virtual ~Locator2() { }

  /**
   * Returns the version of XML used for the entity. This will normally 
   * be the identifier from the current entity's <?xml version='...' ...?> 
   * declaration, or be defaulted by the parser.
   * <p>
   * At this writing, only one version ("1.0") is defined, but it seems 
   * likely that a new version will be defined which has slightly different 
   * rules about which characters are legal in XML names.
   * <p>
   * @return Identifier for the XML version being used to interpret the entity's text.
   */
  virtual stringT getXMLVersion() const = 0;

  /**
   * Returns the name of the character encoding for the entity. If the encoding was 
   * declared externally (for example, in a MIME Content-Type header), that will be 
   * the name returned. Else if there was an <?xml ...encoding='...'?> declaration at 
   * the start of the document, that encoding name will be returned. Otherwise the 
   * encoding will been inferred (norally to be UTF-8, or some UTF-16 variant), and
   * that inferred name will be returned.
   * <p>
   * Note that some recent W3C specifications require that text in some encodings 
   * be normalized, using Unicode Normalization Form C, before processing. Such 
   * normalization must be performed by applications, and would normally be triggered
   * based on the value returned by this method.
   * <p>
   * Encoding names may be those used by the underlying implementation, and 
   * comparisons should be case-insensitive.
   * 
   * @return Name of the character encoding being used to interpret the entity's text.
   */
  virtual stringT getEncoding() const = 0;
}; // class Locator2

} // namespace SAX
} // namespace Arabica

#endif
// end of file

