#ifndef JEZUK_SimpleDOM_DOMIMPLEMENTATIONIMPL_H
#define JEZUK_SimpleDOM_DOMIMPLEMENTATIONIMPL_H

#include <DOM/DOMImplementation.h>
#include <DOM/DOMException.h>
#include <DOM/Simple/DocumentImpl.h>
#include <DOM/Simple/DocumentTypeImpl.h>
#include <DOM/Simple/StringAdaptor.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT> class DOMImplementationImpl;

template<class stringT, class string_adaptorT = SimpleDOM::default_string_adaptor<stringT> >
class DOMImplementation
{
  public:
    static DOM::DOMImplementation<stringT> getDOMImplementation() 
    {
      static DOM::DOMImplementation<stringT> domImpl(new DOMImplementationImpl<stringT, string_adaptorT>());
      return domImpl;
    } // getDOMImplementation

  private:
    DOMImplementation();
}; // class DOMImplementation

template<class stringT, class string_adaptorT>
class DOMImplementationImpl : public DOM::DOMImplementation_impl<stringT>
{
  public:
    virtual void addRef() { ++refCount_; }
    virtual void releaseRef() { --refCount_; }

    ////////////////////////////////////////////////
    // DOMImplementation methods
    virtual bool hasFeature(const stringT& feature, const stringT& version) const
    {
      // need a proper case-insensitive compare here eventually
      string_adaptorT SA;
      const char* names[] = { "Core", "core", "CORE", "XML", "xml", 0 };
      for(int n = 0; names[n] != 0; ++n)
      {
        if((feature == SA.makeStringT(names[n])) &&
           (version.empty() || version == SA.makeStringT("1.0") || version == SA.makeStringT("2.0")))
           return true;
      } // while 

      return false;
    } // hasFeature

    virtual DOM::DocumentType_impl<stringT>* createDocumentType(const stringT& qualifiedName,
                                                                const stringT& publicId,
                                                                const stringT& systemId)
    {
      DocumentTypeImpl<stringT, string_adaptorT>* di = new DocumentTypeImpl<stringT, string_adaptorT>(qualifiedName, publicId, systemId);
      di->setReadOnly(true);
      return di;
    } // createDocumentType

    virtual DOM::Document_impl<stringT>* createDocument(const stringT& namespaceURI,
                                                        const stringT& qualifiedName,
                                                        DOM::DocumentType_impl<stringT>* docType)
    {
      DocumentImpl<stringT, string_adaptorT>* doc = new DocumentImpl<stringT, string_adaptorT>(namespaceURI, qualifiedName, docType, this);

      if(!qualifiedName.empty())
        doc->appendChild(doc->createElementNS(namespaceURI, qualifiedName));

      return doc;
    } // createDocument

  public:
    DOMImplementationImpl() : refCount_(0) { }
    virtual ~DOMImplementationImpl() { }

  private:
    unsigned int refCount_;

    DOMImplementationImpl(const DOMImplementationImpl&);
    DOMImplementationImpl& operator=(const DOMImplementationImpl&);
    bool operator==(const DOMImplementationImpl&) const;

    friend class DOMImplementation<stringT, string_adaptorT>;
}; // class DOMImplementationImpl

} // namespace Simple

#endif
// end of file
