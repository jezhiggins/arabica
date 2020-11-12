#ifndef JEZUK_SimpleDOM_DOMIMPLEMENTATIONIMPL_H
#define JEZUK_SimpleDOM_DOMIMPLEMENTATIONIMPL_H

#include <DOM/DOMException.hpp>
#include <DOM/DOMImplementation.hpp>
#include <DOM/Simple/DocumentImpl.hpp>
#include <DOM/Simple/DocumentTypeImpl.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT> class DOMImplementationImpl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class DOMImplementation
{
  public:
    static DOM::DOMImplementation<stringT, string_adaptorT> getDOMImplementation()
    {
      static DOMImplementationImpl<stringT, string_adaptorT> domImpl;
      return DOM::DOMImplementation<stringT, string_adaptorT>(&domImpl);
    } // getDOMImplementation

  private:
    DOMImplementation();
}; // class DOMImplementation

template<class stringT, class string_adaptorT>
class DOMImplementationImpl : public DOM::DOMImplementation_impl<stringT, string_adaptorT>
{
  public:
    // we don't actually need the ref count in this case
    virtual void addRef() { }
    virtual void releaseRef() { }

    ////////////////////////////////////////////////
    // DOMImplementation methods
    virtual bool hasFeature(const stringT& feature, const stringT& version) const
    {
      // need a proper case-insensitive compare here eventually
      const char* names[] = { "Core", "core", "CORE", "XML", "xml", 0 };
      for(int n = 0; names[n] != 0; ++n)
      {
        if((feature == string_adaptorT::construct_from_utf8(names[n])) &&
           (string_adaptorT::empty(version) ||
            version == string_adaptorT::construct_from_utf8("1.0") ||
            version == string_adaptorT::construct_from_utf8("2.0")))
           return true;
      } // while

      return false;
    } // hasFeature

    virtual DOM::DocumentType_impl<stringT, string_adaptorT>* createDocumentType(const stringT& qualifiedName,
                                                                                 const stringT& publicId,
                                                                                 const stringT& systemId)
    {
      DocumentTypeImpl<stringT, string_adaptorT>* di = new DocumentTypeImpl<stringT, string_adaptorT>(qualifiedName, publicId, systemId);
      di->setReadOnly(true);
      return di;
    } // createDocumentType

    virtual DOM::Document_impl<stringT, string_adaptorT>* createDocument(const stringT& namespaceURI,
                                                                         const stringT& qualifiedName,
                                                                         DOM::DocumentType_impl<stringT, string_adaptorT>* docType)
    {
      DocumentImpl<stringT, string_adaptorT>* doc = new DocumentImpl<stringT, string_adaptorT>(namespaceURI, qualifiedName, docType, this);
      doc->addRef();
      if(!string_adaptorT::empty(qualifiedName))
        doc->appendChild(doc->createElementNS(namespaceURI, qualifiedName));

      return doc;
    } // createDocument

  private:
    DOMImplementationImpl() { }
    virtual ~DOMImplementationImpl() { }

    DOMImplementationImpl(const DOMImplementationImpl&);
    DOMImplementationImpl& operator=(const DOMImplementationImpl&);
    bool operator==(const DOMImplementationImpl&) const;

    friend class DOMImplementation<stringT, string_adaptorT>;
}; // class DOMImplementationImpl

} // namespace Simple
} // namespace Arabica

#endif
// end of file
