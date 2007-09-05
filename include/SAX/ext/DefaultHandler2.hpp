#ifndef ARABICA_DEFAULT_HANDLER2_H
#define ARABICA_DEFAULT_HANDLER2_H

// DefaultHandler.h 
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <SAX/ext/LexicalHandler.hpp>

#pragma message("DefaultHandler2 is deprecated.  You can now use DefaultHandler instead.")

namespace Arabica
{
namespace SAX 
{

/**
 * Default base class for SAX2 event handlers.
 *
 * <p>This class extends the SAX2 base 
 * {@link DefaultHandler} handler class to 
 * support the SAX2 {@link LexicalHandler LexicalHandler}
 * and {@link DeclHandler DeclHandler} extensions. 
 * The added handler methods just return; subclassers may 
 * override on a method-by-method basis.
 *
 * Note: this class might yet learn that the 
 * ContentHandler.setDocumentLocator() call might be 
 * passed a {@link Locator2 Locator2} object, and 
 * that the ContentHandler.startElement() call might be 
 * passed a {@link Attributes2 Attributes2} object.
 * 
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see DefaultHandler
 * @see LexicalHandler
 * @see DeclHandler
 */
template<class string_type, class string_adaptor>
class DefaultHandler2 : public DefaultHandler<string_type, string_adaptor>
{
public:
  typedef string_type stringT;

  DefaultHandler2() { }
  virtual ~DefaultHandler2() { }

private:
  DefaultHandler2(const DefaultHandler2&);
  DefaultHandler2& operator=(const DefaultHandler2&);
  bool operator==(const DefaultHandler2&);
}; // class DefaultHandler

} // namespace SAX
} // namespace Arabica

#endif
