#ifndef ARABICA_XML_FILTER_H
#define ARABICA_XML_FILTER_H

// XMLFilter.h

#include <string>
#include <SAX/ArabicaConfig.hpp>

#include <SAX/XMLReader.hpp>

namespace Arabica
{
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
  * for creating SAX2 filters, by passing on all {@link EntityResolver
  * EntityResolver}, {@link DTDHandler DTDHandler},
  * {@link ContentHandler ContentHandler} and {@link ErrorHandler
  * ErrorHandler} events automatically.</p>
  *
  * @since SAX 2.0
  * @author Jez Higgins, 
  *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
  * @version 2.0
  * @see XMLFilterImpl
  */
template<class string_type, class string_adaptor_type>
class XMLFilter : public XMLReaderInterface<string_type, string_adaptor_type>
{
public:
  typedef XMLReaderInterface<string_type, string_adaptor_type> XMLReaderT;
  typedef typename XMLReaderT::string_adaptor string_adaptor;

  virtual ~XMLFilter() { }

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
}; // class XMLFilter

} // namespace SAX
} // namespace Arabica

#endif
// end of file
