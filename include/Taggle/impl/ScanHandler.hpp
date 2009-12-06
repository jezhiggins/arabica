#ifndef ARABICA_SCAN_HANDLER_HPP
#define ARABICA_SCAN_HANDLER_HPP

#include <string>

namespace Arabica
{

namespace SAX
{

/**
 An interface that Scanners use to report events in the input stream.
 
 This code is derived from John Cowan's splendid TagSoup package
*/
class ScanHandler
{
protected:
  ~ScanHandler() {}

public:
	/**
	Reports an attribute name without a value.
	**/
	virtual void adup(const std::string& buff) = 0;

	/**
	Reports an attribute name; a value will follow.
	**/
	virtual void aname(const std::string& buff) = 0;

	/**
	Reports an attribute value.
	**/
	virtual void aval(const std::string& buff) = 0;

	/**
	  * Reports the content of a CDATA section (not a CDATA element)
	  */
	virtual void cdsect(const std::string& buff) = 0;

	/**
   * Reports a <!....> declaration - typically a DOCTYPE
   */
	virtual void decl(const std::string& buff) = 0;

	/**
	Reports an entity reference or character reference.
	**/
	virtual void entity(const std::string& buff) = 0;

	/**
	Reports EOF.
	**/
	virtual void eof(const std::string& buff) = 0;

	/**
	Reports an end-tag.
	**/
	virtual void etag(const std::string& buff) = 0;

	/**
	Reports the general identifier (element type name) of a start-tag.
	**/
	virtual void gi(const std::string& buff) = 0;

	/**
	Reports character content.
	**/
	virtual void pcdata(const std::string& buff) = 0;

	/**
	Reports the data part of a processing instruction.
	**/
	virtual void pi(const std::string& buff) = 0;

	/**
	Reports the target part of a processing instruction.
	**/
	virtual void pitarget(const std::string& buff) = 0;

	/**
	Reports the close of a start-tag.
	**/
	virtual void stagc(const std::string& buff) = 0;

	/**
	Reports the close of an empty-tag.
	**/
	virtual void stage(const std::string& buff) = 0;

	/**
	Reports a comment.
	**/
	virtual void cmnt(const std::string& buff) = 0;

	/**
	Returns the value of the last entity or character reference reported.
	**/
	virtual int getEntity() = 0;
}; // class ScanHandler

} // namespace SAX

} // namespace Arabica

#endif
