#ifndef ARABICA_DOM_DUALMODE_DUALMODE_HPP
#define ARABICA_DOM_DUALMODE_DUALMODE_HPP

#include <DOM/SAX2DOM/SAX2DOM.h>
#include <boost/function.hpp>

namespace Arabica
{
namespace DualMode
{
template<class stringT, 
         class string_adaptorT = Arabica::default_string_adaptor<stringT>,
         class SAX_parser = Arabica::SAX::XMLReader<stringT, string_adaptorT> >
class Parser : public Arabica::SAX2DOM::Parser<stringT, string_adaptorT, SAX_parser>
{
    typedef Arabica::SAX2DOM::Parser<stringT, string_adaptorT, SAX_parser> BaseT;
  public:
    typedef boost::function2<void, Arabica::DOM::Node<stringT, string_adaptorT> &, Arabica::DOM::Node<stringT, string_adaptorT> &> ElementHandlerT;

    void setElementEndHandler(ElementHandlerT func)
    {
      elementEndFunc_ = func;
    } // setElementEndHandler 

  protected:
    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
    {
      if(BaseT::currentNode() == 0)
        return;

      Arabica::DOM::Node<stringT, string_adaptorT> child(BaseT::currentNode());

      BaseT::endElement(namespaceURI, localName, qName);
      
      if(!!elementEndFunc_)
        elementEndFunc_(BaseT::currentNode(), child);
    } // endElement

  private:
    ElementHandlerT elementEndFunc_;
}; // class Parser

} // namespace DualMode
} // namespace Arabica

#endif
