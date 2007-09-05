#ifndef JEZUK_SAX2DOM_DOCUMENTTYPEIMPL_H
#define JEZUK_SAX2DOM_DOCUMENTTYPEIMPL_H

#include <DOM/Simple/DocumentTypeImpl.hpp>

namespace Arabica
{
namespace SAX2DOM
{

template<class stringT, class string_adaptorT>
class DocumentType : public Arabica::SimpleDOM::DocumentTypeImpl<stringT, string_adaptorT>
{
    typedef Arabica::SimpleDOM::DocumentTypeImpl<stringT, string_adaptorT> BaseDT;
  public:
    DocumentType(const stringT& qualifiedName,
                 const stringT& publicId,
                 const stringT& systemId) :
      BaseDT(qualifiedName, publicId, systemId)
    {
    } // DocumentType

    virtual ~DocumentType() { }

    //////////////////////////////////////////////////////
    // DOM::DOMImplementation extensions
    void addEntity(Arabica::SimpleDOM::EntityImpl<stringT, string_adaptorT>* entity)
    {
      BaseDT::addEntity(entity);
    } // addEntity

    void addNotation(Arabica::SimpleDOM::NotationImpl<stringT, string_adaptorT>* notation)
    {
      BaseDT::addNotation(notation);
    } // addNotation

    void addElement(const stringT& name)
    {
      BaseDT::addElement(new Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT>(BaseDT::ownerDoc_, name));
    } // addElement

    void addDefaultAttr(const stringT& elementName, const stringT& attributeName, const stringT& attributeValue)
    {
      Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT>* elem = dynamic_cast<Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT>*>(BaseDT::getElements()->getNamedItem(elementName));
      if(elem == 0)
      {
        addElement(elementName);
        elem = dynamic_cast<Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT>*>(BaseDT::getElements()->getNamedItem(elementName));
      }
      Arabica::SimpleDOM::AttrImpl<stringT, string_adaptorT>* attr = new Arabica::SimpleDOM::AttrImpl<stringT, string_adaptorT>(BaseDT::ownerDoc_, attributeName);
      attr->setValue(attributeValue);
      attr->setSpecified(false);
      elem->setAttributeNode(attr);
    } // addDefaultAttr

    void addElementId(const stringT& elementName)
    {
      BaseDT::addElementId(elementName);
    } // addElementId
}; // class DOMImplementation

} // namespace SAX2DOM
} // namespace Arabica

#endif
// end of file
