#ifndef ARABICA_XML_FILTER_H
#define ARABICA_XML_FILTER_H

// XMLFilter.h
// $Id$

#include <string>
#include <SAX/ArabicaConfig.h>

#include <SAX/XMLReader.h>

namespace SAX
{

/**
  * Interface for an XML filter.
  *
  * <p>An XML filter is like an XML reader, except that it obtains its
  * events from another XML reader rather than a primary source like
  * an XML document or database.  Filters can modify a stream of
  * events as they pass on to the final application.</p>
  *
  * <p>The XMLFilterImpl helper class provides a convenient base
  * for creating SAX2 filters, by passing on all {@link basic_EntityResolver
  * EntityResolver}, {@link basic_DTDHandler DTDHandler},
  * {@link basic_ContentHandler ContentHandler} and {@link ErrorHandler
  * ErrorHandler} events automatically.</p>
  *
  * @since SAX 2.0
  * @author Jez Higgins, 
  *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
  * @version 2.0
  * @see basic_XMLFilterImpl
  */
template<class string_type>
class basic_XMLFilter : public basic_XMLReader<string_type>
{
public:
  typedef string_type stringT;
  typedef basic_XMLReader<stringT> XMLReaderT;

  virtual ~basic_XMLFilter() { }

  /**
   * Set the parent reader.
   *
   * <p>This method allows the application to link the filter to
   * a parent reader (which may be another filter).</p>
   *
   * @param parent The parent reader.
   */
  virtual void setParent(XMLReaderT& parent) = 0;
  /**
   * Get the parent reader.
   *
   * <p>This method allows the application to query the parent
   * reader (which may be another filter).  It is generally a
   * bad idea to perform any operations on the parent reader
   * directly: they should all pass through this filter.</p>
   *
   * @return The parent filter, or 0 if none has been set.
   */
  virtual XMLReaderT* getParent() const = 0;
}; // class basic_XMLFilter

typedef basic_XMLFilter<std::string> XMLFilter;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_XMLFilter<std::wstring> wXMLFilter;
#endif 

}; // namespace SAX

#endif
// end of file
