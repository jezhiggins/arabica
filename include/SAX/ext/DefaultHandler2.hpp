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
 * {@link basic_DefaultHandler} handler class to 
 * support the SAX2 {@link basic_LexicalHandler LexicalHandler}
 * and {@link basic_DeclHandler DeclHandler} extensions. 
 * The added handler methods just return; subclassers may 
 * override on a method-by-method basis.
 *
 * Note: this class might yet learn that the 
 * ContentHandler.setDocumentLocator() call might be 
 * passed a {@link basic_Locator2 Locator2} object, and 
 * that the ContentHandler.startElement() call might be 
 * passed a {@link basic_Attributes2 Attributes2} object.
 * 
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_DefaultHandler
 * @see basic_LexicalHandler
 * @see basic_DeclHandler
 */
template<class string_type>
class basic_DefaultHandler2 : public basic_DefaultHandler<string_type>
{
public:
  typedef string_type stringT;

  basic_DefaultHandler2() { }
  virtual ~basic_DefaultHandler2() { }

private:
  basic_DefaultHandler2(const basic_DefaultHandler2&);
  basic_DefaultHandler2& operator=(const basic_DefaultHandler2&);
  bool operator==(const basic_DefaultHandler2&);
}; // class basic_DefaultHandler

typedef basic_DefaultHandler2<std::string> DefaultHandler2;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_DefaultHandler2<std::wstring> wDefaultHandler2;
#endif 

} // namespace SAX
} // namespace Arabica

#endif
