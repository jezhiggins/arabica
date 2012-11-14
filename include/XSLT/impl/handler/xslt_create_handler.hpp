#ifndef ARABICA_XSLT_CREATE_HANDLER_HPP
#define ARABICA_XSLT_CREATE_HANDLER_HPP

#include <SAX/XMLReader.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <XPath/XPath.hpp>

#include "../xslt_compilation_context.hpp"
#include "../xslt_compiled_stylesheet.hpp"
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class Handler, class string_type, class string_adaptor>
SAX::DefaultHandler<string_type, string_adaptor>* CreateHandler(CompilationContext<string_type, string_adaptor>& context)
{
  return new Handler(context);
} // create

template<class string_type, class string_adaptor>
class NotImplementedYetHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
public:
  NotImplementedYetHandler(CompilationContext<string_type, string_adaptor>& /* context */) { }

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& /* atts */)
  {
    throw SAX::SAXException("Haven't implemented " + string_adaptor::asStdString(qName) + " yet");
  } // startElement
}; // NotImplementedYetHandler


template<class string_type, class string_adaptor> class ChildElementsBuilder;

template<class string_type, class string_adaptor> 
class ChildElements
{
public:
  typedef SAX::DefaultHandler<string_type, string_adaptor>* (*CreateHandlerPtr)(CompilationContext<string_type, string_adaptor>&);

  static ChildElementsBuilder<string_type, string_adaptor> add(const string_type name, CreateHandlerPtr creator);

  ChildElements(const ChildElements& rhs) :
    elementCreators_(rhs.elementCreators_)
  {
  } // ChildElements

  SAX::DefaultHandler<string_type, string_adaptor>* create(const string_type& name, CompilationContext<string_type, string_adaptor>& context) const
  {
    CreatorMapIterator i = elementCreators_.find(name);
    if(i == elementCreators_.end())
      return 0;
    return i->second(context);
  } // create

private:
  void put(const string_type name, CreateHandlerPtr creator)
  {
    elementCreators_[name] = creator;
  } // put

  ChildElements() { }

  typedef std::map<string_type, CreateHandlerPtr> CreatorMap;
  typedef typename std::map<string_type, CreateHandlerPtr>::const_iterator CreatorMapIterator;
  
  CreatorMap elementCreators_;

  friend class ChildElementsBuilder<string_type, string_adaptor>;
}; // struct ChildElement

template<class string_type, class string_adaptor>
class ChildElementsBuilder
{
public:
  typedef SAX::DefaultHandler<string_type, string_adaptor>* (*CreateHandlerPtr)(CompilationContext<string_type, string_adaptor>&);
  operator ChildElements<string_type, string_adaptor>&() { return elements_; }

  ChildElementsBuilder& add(const string_type name, CreateHandlerPtr creator)
  {
    elements_.put(name, creator);
    return *this;
  } // add

private:
  ChildElementsBuilder() :
    elements_()
  { 
  } // ChildElementsBuilder

  ChildElementsBuilder(const ChildElementsBuilder& rhs) :
    elements_(rhs.elements_)
  {
  } // ChildElementsBuilder

  ChildElements<string_type, string_adaptor> elements_;

  friend class ChildElements<string_type, string_adaptor>;
}; // class ChildElementsBuilder

template<class string_type, class string_adaptor>
ChildElementsBuilder<string_type, string_adaptor> 
      ChildElements<string_type, string_adaptor>::add(const string_type name, 
                                                      typename ChildElements<string_type, string_adaptor>::CreateHandlerPtr creator)
{
  ChildElementsBuilder<string_type, string_adaptor> builder;
  builder.add(name, creator);
  return builder;
} // ChildElementsBuilder

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

