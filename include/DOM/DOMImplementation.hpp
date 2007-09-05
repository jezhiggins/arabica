#ifndef JEZUK_DOM_DOMIMPLEMENTATION_H
#define JEZUK_DOM_DOMIMPLEMENTATION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Proxy.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT> class Document;
template<class stringT> class DocumentType;
template<class stringT> class DOMImplementation_impl;

template<class stringT>
class DOMImplementation 
{
  public:
    DOMImplementation() : impl_(0) { }
    DOMImplementation(DOMImplementation_impl<stringT>* impl) : impl_(impl) { }
    DOMImplementation(const DOMImplementation& rhs) : impl_(rhs.impl_) { }

    operator bool() const { return impl_; }
    bool operator==(const DOMImplementation& rhs) const { return impl_ == rhs.impl_; } 
    bool operator!=(const DOMImplementation& rhs) const { return impl_ != rhs.impl_; }
    bool operator==(int dummy) const { return impl_ == dummy; }
    bool operator!=(int dummy) const { return impl_ != dummy; }

    DOMImplementation& operator=(const DOMImplementation& rhs) 
    {
      impl_ = rhs.impl_;
      return *this;
    } // operator=

    bool hasFeature(const stringT& feature, const stringT& version) const 
    {
      return impl_->hasFeature(feature, version);
    } // hasFeature

    DocumentType<stringT> createDocumentType(const stringT& qualifiedName,
                                             const stringT& publicId,
                                             const stringT& systemId)
    {
      return impl_->createDocumentType(qualifiedName, publicId, systemId);
    } // createDocumentType

    Document<stringT> createDocument(const stringT& namespaceURI,
                                     const stringT& qualifiedName,
                                     DocumentType<stringT> docType)
    {
      return impl_->createDocument(namespaceURI, qualifiedName, docType.dtImpl());
    } // createDocument

  private:
    Proxy<DOMImplementation_impl<stringT> > impl_;
}; // class DOMImplementation

/////////////////////////////////////////////////
template<class stringT> class Document_impl;
template<class stringT> class DocumentType_impl;

// derive from this class to implement your own
// DOM provider
template<class stringT>
class DOMImplementation_impl
{
  public:
    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // DOM implementation methods
    virtual bool hasFeature(const stringT& feature, const stringT& version) const = 0;

    virtual DocumentType_impl<stringT>* createDocumentType(const stringT& qualifiedName,
                                                           const stringT& publicId,
                                                           const stringT& systemId) = 0;

    virtual Document_impl<stringT>* createDocument(const stringT& namespaceURI,
                                                   const stringT& qualifiedName,
                                                   DocumentType_impl<stringT>* docType) = 0;

  protected:
    DOMImplementation_impl() { }
    virtual ~DOMImplementation_impl() { }
}; // class DOMImplementation_impl

} // namespace DOM
} // namespace Arabica

#endif // JEZUK_DOM_NODE_H
// end of file
