#ifndef DTDHandlerH
#define DTDHandlerH

// DTDHandler.h 
// $Id$

#include <string>

namespace SAX 
{

/**
 * Receive notification of basic DTD-related events.
 *
 * <p>If a SAX application needs information about notations and
 * unparsed entities, then the application implements this 
 * interface and registers an instance with the SAX parser using 
 * the parser's setDTDHandler method.  The parser uses the 
 * instance to report notation and unparsed entity declarations to 
 * the application.</p>
 *
 * <p>Note that this interface includes only those DTD events that
 * the XML recommendation <em>requires</em> processors to report:
 * notation and unparsed entity declarations.</p>
 *
 * <p>The SAX parser may report these events in any order, regardless
 * of the order in which the notations and unparsed entities were
 * declared; however, all DTD events must be reported after the
 * document handler's startDocument event, and before the first
 * startElement event.
 * (If the {@link basic_LexicalHandler LexicalHandler} is
 * used, these events must also be reported before the endDTD event.)
 * </p>
 *
 * <p>It is up to the application to store the information for 
 * future use (perhaps in a hash table or object tree).
 * If the application encounters attributes of type "NOTATION",
 * "ENTITY", or "ENTITIES", it can use the information that it
 * obtained through this interface to find the entity and/or
 * notation corresponding with the attribute value.</p>
 *
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version $Id$
 * @see basic_XMLReader#setDTDHandler
 */
  
template<class string_type>
class basic_DTDHandler
{
public:
  typedef string_type stringT;

  virtual ~basic_DTDHandler() { }


  /**
   * Receive notification of a notation declaration event.
   *
   * <p>It is up to the application to record the notation for later
   * reference, if necessary;
   * notations may appear as attribute values and in unparsed entity
   * declarations, and are sometime used with processing instruction
   * target names.
   * When a system identifier is present, applications are responsible
   * for knowing if it is used as a URL, and absolutizing it against
   * the appropriate URI when appropriate.
   * That base URI is available from {@link basic_Locator#getSystemId} during
   * this callback, assuming the parser provides a Locator.</p>
   *
   * <p>At least one of publicId and systemId must be non-null. </p>
   *
   * <p>There is no guarantee that the notation declaration will be
   * reported before any unparsed entities that use it.</p>
   *
   * @param name The notation name.
   * @param publicId The notation's public identifier, or an empty string if
   *        none was given.
   * @param systemId The notation's system identifier, or an empty string if
   *        none was given.
   * @exception SAXException Any SAX exception.
   * @see #unparsedEntityDecl
   * @see basic_Attributes
   */
  virtual void notationDecl(const stringT& name,
                            const stringT& publicId,
                            const stringT& systemId) = 0;


  /**
   * Receive notification of an unparsed entity declaration event.
   *
   * <p>Note that the notation name corresponds to a notation
   * reported by the {@link #notationDecl notationDecl} event.  
   * It is up to the application to record the entity for later 
   * reference, if necessary;
   * unparsed entities may appear as attribute values. 
   * </p>
   *
   * <p>If the system identifier is a URL, the parser must resolve it
   * fully before passing it to the application.</p>
   *
   * @exception SAXException Any SAX exception.
   * @param name The unparsed entity's name.
   * @param publicId The entity's public identifier, or an empty string if none
   *        was given.
   * @param systemId The entity's system identifier.
   * @param notationName The name of the associated notation.
   * @see #notationDecl
   * @see basic_Attributes
   */
  virtual void unparsedEntityDecl(const stringT& name,
	                                const stringT& publicId,
                                  const stringT& systemId,
                                  const stringT& notationName) = 0;

}; // class basic_DTDHandler

typedef basic_DTDHandler<std::string> DTDHandler;
typedef basic_DTDHandler<std::wstring> wDTDHandler;

}; // namespace SAX

#endif
// end of file
