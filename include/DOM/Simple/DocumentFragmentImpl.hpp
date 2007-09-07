#ifndef JEZUK_SimpleDOM_DOCUMENTFRAGMENTIMPL_H
#define JEZUK_SimpleDOM_DOCUMENTFRAGMENTIMPL_H

#include <DOM/DocumentFragment.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class DocumentFragmentImpl : public DOM::DocumentFragment_impl<stringT, string_adaptorT>,
                             public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
  public:
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    DocumentFragmentImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc) : 
        DOM::DocumentFragment_impl<stringT, string_adaptorT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc)
    { 
    } // DocumentFragmentImpl

    virtual ~DocumentFragmentImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const 
    { 
      return DOM::Node_base::DOCUMENT_FRAGMENT_NODE; 
    } // getNodeType

    virtual DOMNode_implT* cloneNode(bool deep) const
    {
      DOMNode_implT* clone = NodeT::ownerDoc_->createDocumentFragment();
      if(deep)
        for(DOMNode_implT* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
          clone->appendChild(c->cloneNode(true));
      return clone;
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT frag = string_adaptorT::construct_from_utf8("#document-fragment");
      return frag;
    } // getNodeName

    virtual DOMNode_implT* getParentNode() const 
    { 
      return 0; 
    } // getParentNode

  private:
    virtual void checkChildType(DOMNode_implT* child)
    {
      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::ELEMENT_NODE) && 
         (type != DOM::Node_base::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node_base::COMMENT_NODE) && 
         (type != DOM::Node_base::TEXT_NODE) && 
         (type != DOM::Node_base::CDATA_SECTION_NODE) && 
         (type != DOM::Node_base::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType
}; // class DocumentFragmentImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

