#ifndef ARABICA_LOCATOR_IMPL_H
#define ARABICA_LOCATOR_IMPL_H

// LocatorImpl.h
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <string>
#include <Locator.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Provide an optional convenience implementation of Locator.
 *
 * <p>This class is available mainly for application writers, who
 * can use it to make a persistent snapshot of a locator at any
 * point during a document parse:</p>
 *
 * <pre>
 * Locator locator;
 * LocatorImpl startloc;
 *
 * void setLocator(const Locator& locator)
 * {
 *   // note the locator
 *   this.locator = &locator;
 * }
 *
 * void startDocument ()
 * {
 *   // save the location of the start of the document
 *   // for future use.
 *   startloc = locator;
 * }
 *</pre>
 *
 * <p>Normally, parser writers will not use this class, since it
 * is more efficient to provide location information only when
 * requested, rather than constantly updating a Locator object.</p>
 *
 * @since SAX 1.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see Locator Locator
 */
template<class string_type, class string_adaptor>
class LocatorImpl : public Locator<string_type, string_adaptor>
{
public:
  typedef Locator<string_type, string_adaptor> LocatorT;
  
  LocatorImpl() : 
    publicId_(), 
    systemId_(), 
    lineNumber_(-1), 
    columnNumber_(-1) 
  { 
  } // LocatorImpl

  LocatorImpl(const LocatorT& rhs) : 
    publicId_(rhs.getPublicId()), 
    systemId_(rhs.getSystemId()), 
    lineNumber_(rhs.getLineNumber()), 
    columnNumber_(rhs.getColumnNumber()) 
  { 
  } // LocatorImpl

  virtual ~LocatorImpl() { }

  LocatorImpl& operator=(const LocatorT& rhs)
  {
    publicId_ = rhs.getPublicId();
    systemId_ = rhs.getSystemId(); 
    lineNumber_ = rhs.getLineNumber();
    columnNumber_ = rhs.getColumnNumber();
  } // operator=

  //////////////////////////////////////////////////////////////////////
  // Implementation of Locator
  /**
   * Return the saved public identifier.
   *
   * @return The public identifier as a string, or an empty string if none
   *         is available.
   * @see Locator#getPublicId
   * @see #setPublicId
   */
  virtual string_type getPublicId() const { return publicId_; }
  /**
   * Return the saved system identifier.
   *
   * @return The system identifier as a string, or an empty string if none
   *         is available.
   * @see Locator#getSystemId
   * @see #setSystemId
   */
  virtual string_type getSystemId() const { return systemId_; }
  /**
   * Return the saved line number (1-based).
   *
   * @return The line number as an integer, or -1 if none is available.
   * @see Locator#getLineNumber
   * @see #setLineNumber
   */
  virtual int getLineNumber() const { return lineNumber_; }
  /**
   * Return the saved column number (1-based).
   *
   * @return The column number as an integer, or -1 if none is available.
   * @see Locator#getColumnNumber
   * @see #setColumnNumber
   */
  virtual int getColumnNumber() const { return columnNumber_; }

  //////////////////////////////////////////////////////////////////////
  // Setters for the properties (not in Locator)
  /**
   * Set the public identifier for this locator.
   *
   * @param publicId The new public identifier, or an empty string 
   *        if none is available.
   * @see #getPublicId
   */
  void setPublicId(const string_type& publicId) { publicId_ = publicId; }
  /**
   * Set the system identifier for this locator.
   *
   * @param systemId The new system identifier, or an empty string 
   *        if none is available.
   * @see #getSystemId
   */
  void setSystemId(const string_type& systemId) { systemId_ = systemId; }
  /**
   * Set the line number for this locator (1-based).
   *
   * @param lineNumber The line number, or -1 if none is available.
   * @see #getLineNumber
   */
  void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
  /**
   * Set the column number for this locator (1-based).
   *
   * @param columnNumber The column number, or -1 if none is available.
   * @see #getColumnNumber
   */
  void setColumnNumber(int columnNumber) { columnNumber_ =  columnNumber; }

private:
  //////////////////////////////////////////////////////////////////////
  // Internal state.
  string_type publicId_;
  string_type systemId_;
  int lineNumber_;
  int columnNumber_;

  bool operator==(const LocatorT& rhs) const;
}; // class LocatorImpl

} // namespace SAX
} // namespace Arabica 

#endif
//end of file
