#ifndef ARABICA_DOCUMENTHANDLER_H
#define ARABICA_DOCUMENTHANDLER_H
// SAX document handler.
// $Id$

#include <SAX/ArabicaConfig.hpp>

namespace Arabica
{
namespace SAX 
{

template<class string_type, class string_adaptor> class Locator;
template<class string_type, class string_adaptor> class AttributeList;

/**
  * Receive notification of general document events.
  *
  * This is the main interface that most SAX applications
  * implement: if the application needs to be informed of basic parsing 
  * events, it implements this interface and registers an instance with 
  * the SAX parser using the setDocumentHandler method.  The parser 
  * uses the instance to report basic document-related events like
  * the start and end of elements and character data.
  *
  * The order of events in this interface is very important, and
  * mirrors the order of information in the document itself.  For
  * example, all of an element's content (character data, processing
  * instructions, and/or subelements) will appear, in order, between
  * the startElement event and the corresponding endElement event.
  *
  * Application writers who do not want to implement the entire
  * interface can derive a class from HandlerBase, which implements
  * the default functionality; parser writers can instantiate
  * HandlerBase to obtain a default handler.  The application can find
  * the location of any document event using the Locator interface
  * supplied by the Parser through the setDocumentLocator method.
  *
  * @author Jez Higgins, jez@jezuk.co.uk
  * @version 0.1
  * @see Parser#setDocumentHandler
  * @see Locator
  * @see HandlerBase
  */
template<class string_type, class string_adaptor>
class DocumentHandler
{
public:
  typedef string_type stringT;
  typedef Locator<string_type, string_adaptor> LocatorT;
  typedef AttributeList<string_type, string_adaptor> AttributeListT;

	virtual ~DocumentHandler() { }

  virtual void setDocumentLocator(const LocatorT& locator) = 0;

  virtual void startDocument() = 0;
  virtual void endDocument() = 0;

  virtual void startElement(const stringT& name,
	                          const AttributeListT& atts)  = 0;
  virtual void endElement(const stringT& name)  = 0;

  virtual void characters(const stringT& ch) = 0;

  virtual void ignorableWhitespace(const stringT& ch) = 0;

  virtual void processingInstruction(const stringT& target,
	                                   const stringT& data) = 0;
}; // class DocumentHandler

} // namespace SAX
} // namespace Arabica

#endif
// end of file
