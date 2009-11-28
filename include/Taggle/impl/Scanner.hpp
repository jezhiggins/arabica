#ifndef ARABICA_SAX_SCANNER_HPP
#define ARABICA_SAX_SCANNER_HPP

#include <istream>
#include <string>

namespace Arabica
{
namespace SAX
{

class ScanHandler;

/**
  An interface allowing Parser to invoke scanners.

  This code is derived from John Cowan's splendid TagSoup package
*/
class Scanner 
{
public:
  virtual ~Scanner() {}

	/**
  Invoke a scanner.
	@param r A source of characters to scan
	@param h A ScanHandler to report events to
	**/
	virtual void scan(std::istream& r, ScanHandler& h) = 0;

	/**
	Reset the embedded locator.
	@param publicid The publicid of the source
	@param systemid The systemid of the source
	**/
  virtual void resetDocumentLocator(const std::string& publicid, const std::string& systemid) = 0;

	/**
	Signal to the scanner to start CDATA content mode.
	**/
	virtual void startCDATA() = 0;
}; // Scanner


} // namespace SAX
} // namespace Arabica
#endif
