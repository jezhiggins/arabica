#ifndef SAXInputSourceH
#define SAXInputSourceH

// InputSource.h
// $Id$

#include <iosfwd>
#include <string>

namespace SAX
{

/**
 * A single input source for an XML entity.
 *
 * <p>This class allows a SAX application to encapsulate information
 * about an input source in a single object, which may include
 * a public identifier, a system identifier, a byte stream (possibly
 * with a specified encoding), and/or a character stream.</p>
 *
 * <p>There are two places that the application will deliver this
 * input source to the parser: as the argument to the Parser.parse
 * method, or as the return value of the EntityResolver.resolveEntity
 * method.</p>
 *
 * <p>The SAX parser will use the InputSource object to determine how
 * to read XML input.  If there is a character stream available, the
 * parser will read that stream directly; if not, the parser will use
 * a byte stream, if available; if neither a character stream nor a
 * byte stream is available, the parser will attempt to open a URI
 * connection to the resource identified by the system
 * identifier.</p>
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
 * @see basic_Parser#parse
 * @see basic_EntityResolver#resolveEntity
 */
template<class string_type>
class basic_InputSource
{
public:
  typedef string_type stringT;

  /**
   * Zero-argument default constructor.
   *
   * @see #setPublicId
   * @see #setSystemId
   * @see #setByteStream
   * @see #setEncoding
   */
  basic_InputSource() : 
    byteStream_(0) { }
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
   * @see #setCharacterStream
   */
  basic_InputSource(const stringT& systemId) : 
    systemId_(systemId), byteStream_(0) { }
  basic_InputSource(const basic_InputSource& rhs) :
    publicId_(rhs.publicId_),
    systemId_(rhs.systemId_),
    byteStream_(rhs.byteStream_) { }
  /**
   * Create a new input source with a byte stream.
   *
   * <p>Application writers may use setSystemId to provide a base 
   * for resolving relative URIs, setPublicId to include a 
   * public identifier, and/or setEncoding to specify the object's
   * character encoding.</p>
   *
   * @param byteStream The raw byte stream containing the document.
   * @see #setPublicId
   * @see #setSystemId
   * @see #setEncoding
   * @see #setByteStream
   * @see #setCharacterStream
   */
  basic_InputSource(std::istream& byteStream) :
      byteStream_(&byteStream) { }

  virtual ~basic_InputSource() { }

  basic_InputSource& operator=(const basic_InputSource& rhs)
  {
    publicId_ = rhs.publicId_;
    systemId_ = rhs.systemId_;
    byteStream_ = rhs.byteStream_;

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
   * @see basic_Locator#getPublicId
   * @see basic_SAXParseException#getPublicId
   */
  void setPublicId(const stringT& publicId) { publicId_ = publicId; }
  /**
   * Get the public identifier for this input source.
   *
   * @return The public identifier, or an empty string if none was supplied.
   * @see #setPublicId
   */
  const stringT& getPublicId() const { return publicId_; }

  /**
   * Set the system identifier for this input source.
   *
   * <p>The system identifier is optional if there is a byte stream
   * or a character stream, but it is still useful to provide one,
   * since the application can use it to resolve relative URIs
   * and can include it in error messages and warnings (the parser
   * will attempt to open a connection to the URI only if
   * there is no byte stream or character stream specified).</p>
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
   * @see basic_Locator#getSystemId
   * @see basic_SAXParseException#getSystemId
   */
  void setSystemId(const stringT& systemId) { systemId_ = systemId; }
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
  const stringT& getSystemId() const { return systemId_; }

  /**
   * Set the byte stream for this input source.
   *
   * <p>The SAX parser will ignore this if there is also a character
   * stream specified, but it will use a byte stream in preference
   * to opening a URI connection itself.</p>
   *
   * <p>If the application knows the character encoding of the
   * byte stream, it should set it with the setEncoding method.</p>
   *
   * @param byteStream A byte stream containing an XML document or
   *        other entity.
   * @see #setEncoding
   * @see #getByteStream
   * @see #getEncoding
   */
  void setByteStream(std::istream& byteStream)
  {
    byteStream_ = &byteStream;
  } // setByteStream
  /**
   * Get the byte stream for this input source.
   *
   * <p>The getEncoding method will return the character
   * encoding for this byte stream, or null if unknown.</p>
   *
   * @return The byte stream, or null if none was supplied.
   * @see #getEncoding
   * @see #setByteStream
   */
  std::istream* getByteStream() const { return byteStream_ ;}

  /** 
   * Set the character encoding, if known.
   *
   * <p>The encoding must be a string acceptable for an
   * XML encoding declaration (see section 4.3.3 of the XML 1.0
   * recommendation).</p>
   *
   * <p>This method has no effect when the application provides a
   * character stream.</p>
   *
   * @param encoding A string describing the character encoding.
   * @see #setSystemId
   * @see #setByteStream
   * @see #getEncoding
   */
  void setEncoding(const stringT& encoding) { encoding_ = encoding; }
  /**
   * Get the character encoding for a byte stream or URI.
   *
   * @return The encoding, or an empty string if none was supplied.
   * @see #setByteStream
   * @see #getSystemId
   * @see #getByteStream
   */
  const stringT& getEncoding() const { return encoding_; }

  ///////////////////////////////////////////////////////////
private:
	stringT publicId_;
	stringT systemId_;
  std::istream* byteStream_;
	stringT encoding_;

  bool operator==(const basic_InputSource&); // no implementation
}; // class basic_InputSource

/* char specialization
template<>
basic_InputSource<char>::basic_InputSource(std::istream& byteStream) :
  byteStream_(&byteStream),
  charStream_(&byteStream)
{
} // basic_InputSource

template<>
basic_InputSource<char>::basic_InputSource(charStreamT& charStream, bool) :
  byteStream_(&charStream),
  charStream_(&charStream)
{
} // basic_InputSource

template<>
void basic_InputSource<char>::setByteStream(std::istream& byteStream)
{
  byteStream_ = &byteStream;
  charStream_ = &byteStream;
} // setByteStream

template<>
void basic_InputSource<char>::setCharacterStream(charStreamT& charStream)
{
  byteStream_ = &charStream;
  charStream_ = &charStream;
} // setCharStream
*/

/*
// wchar_t specializations
template<>
basic_InputSource<wchar_t>::basic_InputSource(std::istream& byteStream) :
  byteStream_(&byteStream),
  charStream_(0)
{
} // basic_InputStream

template<>
basic_InputSource<wchar_t>::basic_InputSource(charStreamT& charStream, bool) :
  byteStream_(0),
  charStream_(&charStream)
{
} // basic_InputStream

/////////////////////////////
template<class charT, class traitsT, class allocatorT>
void basic_InputSource<charT, traitsT, allocatorT>::setByteStream(std::istream& byteStream)
{
  byteStream_ = &byteStream;
  charStream_ = 0;
} // setByteStream

template<class charT, class traitsT, class allocatorT>
void basic_InputSource<charT, traitsT, allocatorT>::setCharacterStream(charStreamT& charStream)
{
  byteStream_ = 0;
  charStream_ = &charStream;
} // setCharStream
*/


typedef basic_InputSource<std::string> InputSource;
#if !(__GNUG__ && (__GNUC__ < 3))
typedef basic_InputSource<std::wstring> wInputSource;
#endif // !(__GNUG__ && (__GNUC__ < 3))

}; // namespace SAX

#endif // #define InputSourceH
// end of file
