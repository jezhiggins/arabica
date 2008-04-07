#ifndef ARABICA_SAX_TAGGLE_SCHEMA_HPP
#define ARABICA_SAX_TAGGLE_SCHEMA_HPP

namespace Arabica
{
namespace SAX
{

class ElementType;

/**
Abstract class representing a TSSL schema.
Actual TSSL schemas are compiled into concrete subclasses of this class.

Based on code from John Cowan's super TagSoup package
**/
class Schema
{
public:
	static const int M_ANY = 0xFFFFFFFF;
	static const int M_EMPTY = 0;
	static const int M_PCDATA = 1 << 30;
	static const int M_ROOT = 1 << 31;

	static const int F_RESTART = 1;
	static const int F_CDATA = 2;
	static const int F_NOFORCE = 4;

	virtual void elementType(const std::string& name, int model, int memberOf, int flags) = 0;
	virtual ElementType& rootElementType() = 0; 
	virtual void parent(std::string name, std::string parentName) = 0;

  virtual ElementType& getElementType(const std::string& name) = 0;
  virtual int getEntity(const std::string& name) const = 0;
  virtual const std::string& getURI() const = 0;
	virtual const std::string& getPrefix() const = 0;

  virtual ~Schema() { }
}; // class Schema

} // namespace SAX

} // namespace Arabica
#endif
