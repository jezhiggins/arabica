#ifndef JEZUK_DOM_DOCUMENTTYPE_H
#define JEZUK_DOM_DOCUMENTTYPE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/NamedNodeMap.hpp>
#include <DOM/DOMImplementation.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class Document_impl;
template<class stringT, class string_adaptorT> class DocumentType_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class DocumentType : public Node<stringT, string_adaptorT>
{
    typedef DocumentType_impl<stringT, string_adaptorT> DocumentType_implT;
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef NamedNodeMap<stringT, string_adaptorT> NamedNodeMapT;
    typedef DOMImplementation<stringT, string_adaptorT> DOMImplementationT;

    DocumentType() : NodeT(0) { }
    DocumentType(DocumentType_implT* impl) : NodeT(impl) { }
    DocumentType(const DocumentType& rhs) : NodeT(rhs) { }
    explicit DocumentType(const NodeT& rhs) : NodeT(rhs)  
    {
      if(rhs.getNodeType() != NodeT::DOCUMENT_TYPE_NODE)
        throw std::bad_cast();
    } // DocumentType

    const stringT& getName() const { return dtImpl()->getName(); }

    const NamedNodeMapT getEntities() const { return NamedNodeMapT(dtImpl()->getEntities()); }

    const NamedNodeMapT getNotations() const { return NamedNodeMapT(dtImpl()->getNotations()); }

    stringT getPublicId() const { return dtImpl()->getPublicId(); }

    stringT getSystemId() const { return dtImpl()->getSystemId(); }

    stringT getInternalSubset() const { return dtImpl()->getInternalSubset(); }

  protected:
    DocumentType_implT* dtImpl() const { return dynamic_cast<DocumentType_implT*>(*NodeT::impl_); }

    friend class DOMImplementation<stringT, string_adaptorT>;
}; // class DocumentType

//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class DocumentType_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    typedef NamedNodeMap_impl<stringT, string_adaptorT> NamedNodeMap_implT;

    virtual ~DocumentType_impl() { }

    /////////////////////////////////////////////
    // DOM::DocumentType methods
    virtual const stringT& getName() const = 0;

    virtual NamedNodeMap_implT* getEntities() = 0;

    virtual NamedNodeMap_implT* getNotations() = 0;

    virtual stringT getPublicId() const = 0;

    virtual stringT getSystemId() const = 0;

    virtual stringT getInternalSubset() const = 0;
}; // class DocumentType_impl

} // namespace DOM
} // namespace Arabica

#endif

