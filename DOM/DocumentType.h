#ifndef JEZUK_DOM_DOCUMENTTYPE_H
#define JEZUK_DOM_DOCUMENTTYPE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>
#include <DOM/NamedNodeMap.h>
#include <DOM/DOMImplementation.h>

namespace DOM
{

template<class stringT> class Document_impl;
template<class stringT> class DocumentType_impl;

template<class stringT>
class DocumentType : public Node<stringT>
{
    typedef Node<stringT> NodeT;
  public:
    DocumentType() : Node<stringT>(0) { }
    DocumentType(DocumentType_impl<stringT>* impl) : Node<stringT>(impl) { }
    DocumentType(const DocumentType& rhs) : Node<stringT>(rhs) { }
    explicit DocumentType(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::DOCUMENT_TYPE_NODE)
        throw std::bad_cast();
    } // DocumentType

    stringT getName() const { return dtImpl()->getName(); }

    const NamedNodeMap<stringT> getEntities() const { return NamedNodeMap<stringT>(dtImpl()->getEntities()); }

    const NamedNodeMap<stringT> getNotations() const { return NamedNodeMap<stringT>(dtImpl()->getNotations()); }

    stringT getPublicId() const { return dtImpl()->getPublicId(); }

    stringT getSystemId() const { return dtImpl()->getSystemId(); }

    stringT getInternalSubset() const { return dtImpl()->getInternalSubset(); }

  protected:
    DocumentType_impl<stringT>* dtImpl() const { return dynamic_cast<DocumentType_impl<stringT>*>(*NodeT::impl_); }

    typedef DOMImplementation<stringT> DOMImplementationT;
    friend class DOMImplementation<stringT>;
}; // class DocumentType

//////////////////////////////////////////////////////////
template<class stringT>
class DocumentType_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~DocumentType_impl() { }

    /////////////////////////////////////////////
    // DOM::DocumentType methods
    virtual stringT getName() const = 0;

    virtual NamedNodeMap_impl<stringT>* getEntities() = 0;

    virtual NamedNodeMap_impl<stringT>* getNotations() = 0;

    virtual stringT getPublicId() const = 0;

    virtual stringT getSystemId() const = 0;

    virtual stringT getInternalSubset() const = 0;
}; // class DocumentType_impl

} // namespace DOM

#endif

