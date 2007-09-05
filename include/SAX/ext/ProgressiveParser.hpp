#ifndef ARABICA_PROGRESSIVE_PARSER_H
#define ARABICA_PROGRESSIVE_PARSER_H

#include <SAX/ArabicaConfig.hpp>
#include <string>

// $Id$

namespace Arabica
{
namespace SAX
{
  /** Abstract base class for the parser-specific XMLPScanToken data.
   */
  class XMLPScanTokenParserImpl
  {
    public:
      virtual ~XMLPScanTokenParserImpl() {}
  };

  /**
   * Current state of a progressive parsing operation.
   *
   * This is basically a container to hold any kind of XMLPScanTokenParserImpl a
   * parser can implement.
   */
  class XMLPScanToken
  {
    public:
      void setParserData(std::auto_ptr<XMLPScanTokenParserImpl>& data)
      {
        data_ = data;
      }
      XMLPScanTokenParserImpl* parserImpl()
      {
        return data_.get();
      }
    private:
      std::auto_ptr<XMLPScanTokenParserImpl> data_;
  }; // XMLPScanToken

  template<class string_type, class string_adaptor>
  class ProgressiveParser : public XMLReaderInterface<string_type, string_adaptor>
  {
    public:
      typedef typename XMLReaderInterface<string_type, string_adaptor>::InputSourceT InputSourceT;

      /** @name Progressive Parsing Methods */
      //@{

      /**
       * Begin a progressive parse operation.
       *
       * This method is used to start a progressive parse on an XML file.  To
       * continue parsing, subsequent calls must be to the parseNext method.
       *
       * It scans through the prolog and returns a token to be used on
       * subsequent scanNext() calls.  If the return value is true, then the
       * token is legal and ready for further use.  If it returns false, then
       * the scan of the prolog failed and the token is not going to work on
       * subsequent scanNext() calls.
       *
       * @param systemId The system identifier (URI).
       * @param toFill   A token maintaining state information to maintain
       *                 internal consistency between invocation of parseNext
       *                 calls.
       *
       * @return true if sucessful in parsing the prolog.  It indicates that the
       * user can go ahead with parsing the rest of the file.
       * @return false to indicate that the parser could not parse the prologue
       * (which means the token will not be valid).
       *
       * @see parseNext(XMLPScanToken&)
       * @see parseFirst(const InputSource&, XMLPScanToken&)
       */
      virtual bool parseFirst(const string_type &systemId,
                              XMLPScanToken &toFill) = 0;

      /**
       * Begin a progressive parse operation.
       *
       * This method is used to start a progressive parse on an XML file.  To
       * continue parsing, subsequent calls must be to the parseNext method.
       *
       * It scans through the prolog and returns a token to be used on
       * subsequent scanNext() calls.  If the return value is true, then the
       * token is legal and ready for further use.  If it returns false, then
       * the scan of the prolog failed and the token is not going to work on
       * subsequent scanNext() calls.
       *
       * @param input  The input source for the top-level of the XML document.
       * @param toFill A token maintaining state information to maintain
       *               internal consistency between invocation of parseNext
       *               calls.
       *
       * @return true if sucessful in parsing the prolog.  It indicates that the
       * user can go ahead with parsing the rest of the file.
       * @return false to indicate that the parser could not parse the prologue
       * (which means the token will not be valid).
       *
       * @see parseNext(XMLPScanToken&)
       * @see parseFirst(const string_type&, XMLPScanToken&)
       */
      virtual bool parseFirst(InputSourceT& input,
                              XMLPScanToken& toFill) = 0;

      /**
       * Continue a progressive parse operation.
       *
       * This method is used to continue with progressive parsing of XML files
       * started by a call to parseFirst method.
       *
       * It parses the XML file and stops as soon as it comes across an XML
       * token (as defined in the XML specification).  Relevant callbaqck
       * handlers are invoked as required by the SAX specification.
       *
       * @param token A token maintaining state information to maintain internal
       *              consistency between invocation of parseNext calls.  Clearly
       *              token must come from a call to parseFirst() on <b>this</b>
       *              ProgressiveParser.
       *
       * @return true if successful in parsing the next XML token.  It indicates
       *              the user can go ahead with parsing the rest of the file.
       * @return false to indicate that the parser could not find next token as
       *               per the XML specification production rule.
       *
       * @see parseFirst(const string_type&, XMLPScanToken&)
       * @see parseFirst(const InputSource&, XMLPScanToken&)
       */
      virtual bool parseNext(XMLPScanToken& token) = 0;

      /**
       * Reset the parser after a progressive parse.
       *
       * If a progressive parse loop exits before the end of the document is
       * reached, the parser has no way of knowing this. So it will leave open
       * any files or sockets or memory buffers that were in use at the time
       * that the parse loop exited.
       *
       * The next parse operation will cause these open files and such to be
       * closed, but the next parse operation might occur at some unknown future
       * point. To avoid this problem, you should reset the parser if you exit
       * the loop early.
       *
       * If you exited because of an error, then this cleanup will be done for
       * you.  Its only when you exit the file prematurely of your own accord,
       * because you've found what you wanted in the file most likely.
       *
       * @param token A token maintaing state information to maintain internal
       *              consistency between invocation of parseNext calls.  Clearly
       *              token must come from a call to parseFirst() on <b>this</b>
       *              ProgressiveParser.
       */
      virtual void parseReset(XMLPScanToken& token) = 0;
      //@}
  }; // ProgressiveParser

} // namespace SAX
} // namespace Arabica

#endif /* PROGRESSIVE_PARSER_H */
// end of file

