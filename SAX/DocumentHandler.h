#ifndef DocumentHandlerH
#define DocumentHandlerH
// SAX document handler.
// $Id$

namespace SAX 
{

template<class string_type> class basic_Locator;
template<class string_type> class basic_AttributeList;

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
  * @see basic_Parser#setDocumentHandler
  * @see basic_Locator
  * @see basic_HandlerBase
  */
template<class string_type>
class basic_DocumentHandler
{
public:
  typedef string_type stringT;
  typedef basic_Locator<stringT> LocatorT;
  typedef basic_AttributeList<stringT> AttributeListT;

	virtual ~basic_DocumentHandler() { }

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
}; // class basic_DocumentHandler

typedef basic_DocumentHandler<std::string> DocumentHandler;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_DocumentHandler<std::wstring> wDocumentHandler;
#endif

}; // namespace SAX

#endif
// end of file
