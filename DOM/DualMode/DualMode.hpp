#ifndef ARABICA_DOM_DUALMODE_DUALMODE_HPP
#define ARABICA_DOM_DUALMODE_DUALMODE_HPP

#include <DOM/SAX2DOM/SAX2DOM.h>
#include <boost/function.hpp>

namespace DualMode
{
template<class stringT, 
         class string_adaptorT = Arabica::default_string_adaptor<stringT>,
         class SAX_parser = SAX::XMLReader<stringT, string_adaptorT> >
class Parser : public SAX2DOM::Parser<stringT, string_adaptorT, SAX_parser>
{
    typedef SAX2DOM::Parser<stringT, string_adaptorT, SAX_parser> BaseT;
  public:
	  typedef boost::function2<void, DOM::Node<stringT> &, DOM::Node<stringT> &> ElementHandlerT;

    void setElementEndHandler(ElementHandlerT func)
	  {
		  elementEndFunc_ = func;
	  } // setElementEndHandler 

  protected:
    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
    {
      if(currentNode() == 0)
        return;

  	  DOM::Node<stringT> child(currentNode());

      BaseT::endElement(namespaceURI, localName, qName);
      
	    if(!!elementEndFunc_)
		    elementEndFunc_(currentNode(), child);
    } // endElement

  private:
  	ElementHandlerT elementEndFunc_;
}; // class Parser

} // namespace DualMode

#endif