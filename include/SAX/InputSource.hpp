#ifndef ARABICA_INPUTSOURCE_H
#define ARABICA_INPUTSOURCE_H

// InputSource.h
// $Id$

#include <iosfwd>
#include <string>

#include <SAX/ArabicaConfig.hpp>
#include <SAX/IStreamHandle.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * A single input source for an XML entity.
 *
 * <p>This class allows a SAX application to encapsulate information
 * about an input source in a single object, which may include
 * a public identifier, a system identifier, a byte stream (possibly
 * with a specified encoding).</p>
 *
 * <p>There are two places that the application will deliver this
 * input source to the parser: as the argument to the Parser.parse
 * method, or as the return value of the EntityResolver.resolveEntity
 * method.</p>
 *
 * <p>The SAX parser will use the InputSource object to determine 
 * how to read XML input.  If there is a byte stream available, 
 * the parser will read that stream directly; if a byte stream is 
 * not available, the parser will attempt to open a URI connection 
 * to the resource identified by the system identifier.</p> 
 *
 * <p>An InputSource object belongs to the application: the SAX parser
 * shall never modify it in any way (it may modify a copy if 
 * necessary).</p>
 *
 * <strong>InputSource is still under active consideration, and its
 * interface may change.</strong>
 *
 * @since SAX 1.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see Parser#parse
 * @see EntityResolver#resolveEntity
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class InputSource
{
public:
  /**
   * Zero-argument default constructor.
   *
   * @see #setPublicId
   * @see #setSystemId
   * @see #setByteStream
   * @see #setEncoding
   */
  InputSource() : 
    byteStream_(),
    publicId_(),
    systemId_(),
    encoding_()
    { }
  /**
   * Create a new input source with a system identifier.
   *
   * <p>Applications may use setPublicId to include a 
   * public identifier as well, or setEncoding to specify
   * the character encoding, if known.</p>
   *
   * <p>If the system identifier is a URL, it must be full resolved.</p>
   *
   * @param systemId The system identifier (URI).
   * @see #setPublicId
   * @see #setSystemId
   * @see #setByteStream
   * @see #setEncoding
   */
  InputSource(const string_type& systemId) : 
    byteStream_(),
    publicId_(),
    systemId_(systemId), 
    encoding_()
    { }
  InputSource(const InputSource& rhs) :
    byteStream_(rhs.byteStream_),
    publicId_(rhs.publicId_),
    systemId_(rhs.systemId_),
    encoding_(rhs.encoding_)
    { }
  /**
   * Create a new input source with a byte stream.
   *
   * <p>Application writers may use setSystemId to provide a base 
   * for resolving relative URIs, setPublicId to include a 
   * public identifier, and/or setEncoding to specify the object's
   * character encoding.</p>
   *
   * @param byteStream The raw byte stream containing the document.  The
   *                   InputSource does not assume ownership of 
   *                   this byteStream.
   * @see #InputSource(std::auto_ptr<std::istream>)
   * @see #setPublicId
   * @see #setSystemId
   * @see #setEncoding
   * @see #setByteStream
   */
  InputSource(std::istream& byteStream) :
      byteStream_(byteStream),
      publicId_(),
      systemId_(),
      encoding_()
    { }


  /**
   * Create a new input source with a byte stream.
   *
   * <p>Application writers may use setSystemId to provide a base 
   * for resolving relative URIs, setPublicId to include a 
   * public identifier, and/or setEncoding to specify the object's
   * character encoding.</p>
   *
   * @param byteStream The raw byte stream containing the document.  The
   *                   InputSource assumes ownership of the byteStream 
   *                   and will delete it when no-longer required. 
   * @see InputSource(std::istream&) 
   * @see #setPublicId
   * @see #setSystemId 
   * @see #setEncoding 
   * @see #setByteStream 
   */
  InputSource(std::auto_ptr<std::istream> byteStream) :
      byteStream_(byteStream),
      publicId_(),
      systemId_(),
      encoding_()
  { }
  
  InputSource(std::auto_ptr<std::iostream> byteStream) :
      byteStream_(byteStream),
      publicId_(),
      systemId_(),
      encoding_()
  { }


  virtual ~InputSource() { }

  InputSource& operator=(const InputSource& rhs)
  {
    byteStream_ = rhs.byteStream_;
    publicId_ = rhs.publicId_;
    systemId_ = rhs.systemId_;
    encoding_ = rhs.encoding_;

    return *this;
  } // operator=

  /**
   * Set the public identifier for this input source.
   *
   * <p>The public identifier is always optional: if the application
   * writer includes one, it will be provided as part of the
   * location information.</p>
   *
   * @param publicId The public identifier as a string.
   * @see #getPublicId
   * @see Locator#getPublicId
   * @see SAXParseException#getPublicId
   */
  void setPublicId(const string_type& publicId) { publicId_ = publicId; }
  /**
   * Get the public identifier for this input source.
   *
   * @return The public identifier, or an empty string if none was supplied.
   * @see #setPublicId
   */
  const string_type& getPublicId() const { return publicId_; }

  /**
   * Set the system identifier for this input source.
   *
   * <p>The system identifier is optional if there is a byte
   * stream but it is still useful to provide one, since the
   * application can use it to resolve relative URIs and can
   * include it in error messages and warnings (the parser will
   * attempt to open a connection to the URI only if there is no
   * byte stream specified).</p>
   *
   * <p>If the application knows the character encoding of the
   * object pointed to by the system identifier, it can register
   * the encoding using the setEncoding method.</p>
   *
   * <p>If the system ID is a URL, it must be fully resolved.</p>
   *
   * @param systemId The system identifier as a string.
   * @see #setEncoding
   * @see #getSystemId
   * @see Locator#getSystemId
   * @see SAXParseException#getSystemId
   */
  void setSystemId(const string_type& systemId) { systemId_ = systemId; }
  /**
   * Get the system identifier for this input source.
   *
   * <p>The getEncoding method will return the character encoding
   * of the object pointed to, or an empty string if unknown.</p>
   *
   * <p>If the system ID is a URL, it will be fully resolved.</p>
   *
   * @return The system identifier.
   * @see #setSystemId
   * @see #getEncoding
   */
  const string_type& getSystemId() const { return systemId_; }

  /**
   * Set the byte stream for this input source.
   *
   * <p>The SAX parser will use a byte stream in preference
   * to opening a URI connection itself.</p>
   *
   * <p>If the application knows the character encoding of the
   * byte stream, it should set it with the setEncoding method.</p>
   *
   * @param byteStream A byte stream containing an XML document or
   *        other entity. The InputSource does not assume 
   *                   ownership of byteStream. 
   * @see #setByteStream(std::auto_ptr<std::istream>) To transfer ownership of 
   *                                  an std::istream to an  InputSource
   * @see #setEncoding
   * @see #getByteStream
   * @see #getEncoding
   */
  void setByteStream(std::istream& byteStream)
  {
    byteStream_ = byteStream;
  } // setByteStream

  /**
   * Set the byte stream for this input source.
   *
   * <p>The SAX parser will use a byte stream in preference to
   * opening a URI connection itself.</p>
   *
   * <p>If the application knows the character encoding of the
   * byte stream, it should set it with the setEncoding method.</p>
   *
   * @param byteStream A byte stream containing an XML document or
   *                   other entity.  The InputSource assumes 
   *                   ownership of byteStream. 
   * @see #setByteStream(std::istream&) 
   * @see #setEncoding 
   * @see #getByteStream 
   * @see #getEncoding 
   */
  void setByteStream(std::auto_ptr<std::istream> byteStream)
  {
    byteStream_ = byteStream;
  } // setByteStream

  /**
   * Get the byte stream for this input source as a <code>std::istream*</code>. 
   *
   * <p>The getEncoding method will return the character 
   * encoding for this byte stream, or an empty string if unknown.</p>
   * 
   * @return The byte stream, or null if none was supplied.  No ownership is 
   *         transfered. 
   * @see #getEncoding 
   * @see #setByteStream 
   */
  std::istream* getByteStream() const
  {
    return byteStream_.get(); 
  } // getByteStream

  /**
   * Get the byte stream for this input source as an IStreamHandle.
   *
   * <p>The getEncoding method will return the character
   * encoding for this byte stream, or null if unknown.</p>
   *
   * @return The byte stream, or null if none was supplied.  Ownership is
   *         shared between this and the client code.
   * @see #getEncoding
   * @see #setByteStream
   */
  IStreamHandle getByteStreamHandle() const
  {
    return byteStream_;
  }
  /** 
   * Set the character encoding, if known.
   *
   * <p>The encoding must be a string acceptable for an
   * XML encoding declaration (see section 4.3.3 of the XML 1.0
   * recommendation).</p>
   *
   * @param encoding A string describing the character encoding.
   * @see #setSystemId
   * @see #setByteStream
   * @see #getEncoding
   */
  void setEncoding(const string_type& encoding) { encoding_ = encoding; }
  /**
   * Get the character encoding for a byte stream or URI.
   *
   * @return The encoding, or an empty string if none was supplied.
   * @see #setByteStream
   * @see #getSystemId
   * @see #getByteStream
   */
  const string_type& getEncoding() const { return encoding_; }

  ///////////////////////////////////////////////////////////
private:
  IStreamHandle byteStream_;
	string_type publicId_;
	string_type systemId_;
	string_type encoding_;

  bool operator==(const InputSource&); // no implementation
}; // class InputSource

} // namespace SAX
} // namespace Arabica

#endif // #define InputSourceH
// end of file
