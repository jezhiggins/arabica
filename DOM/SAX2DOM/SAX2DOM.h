#ifndef JEZUK_SAX2DOM_PARSER_H
#define JEZUK_SAX2DOM_PARSER_H

#include <SAX/XMLReader.h>
#include <SAX/ext/DefaultHandler2.h>
#include <SAX/helpers/AttributeTypes.h>
#include <DOM/Simple/DOMImplementation.h>
#include <DOM/Simple/NotationImpl.h>
#include <DOM/Simple/EntityImpl.h>
#include <DOM/Document.h>
#include <DOM/DOMException.h>
#include <DOM/SAX2DOM/DocumentTypeImpl.h>
#include <map>
#include <SAX/helpers/FeatureNames.h>
#include <SAX/helpers/PropertyNames.h>

namespace SAX2DOM
{

template<class stringT, 
         class string_adaptorT = SAX::default_string_adaptor<stringT>,
         class SAX_parser = SAX::XMLReader<stringT> >
class Parser : private SAX::basic_DefaultHandler2<stringT>
{
    typedef SAX::basic_EntityResolver<stringT> EntityResolverT;
    typedef SAX::basic_ErrorHandler<stringT> ErrorHandlerT;
    typedef SimpleDOM::EntityImpl<stringT, string_adaptorT> EntityT;
    typedef SimpleDOM::NotationImpl<stringT, string_adaptorT> NotationT;
    typedef SimpleDOM::ElementImpl<stringT, string_adaptorT> ElementT;
    typedef typename SAX::basic_ErrorHandler<stringT>::SAXParseExceptionT SAXParseExceptionT;

  public:
    Parser() :
        entityResolver_(0),
        errorHandler_(0)
    { 
    } // Parser

    void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
    EntityResolverT* getEntityResolver() const { return entityResolver_; }

    void setErrorHandler(ErrorHandlerT& handler) { errorHandler_ = &errorHandler; }
    ErrorHandlerT* getErrorHandler() const { return errorHandler_; }

    bool parse(const stringT& systemId)
    {
      SAX::basic_InputSource<stringT> is(systemId);
      return parse(is);
    } // loadDOM

    bool parse(SAX::basic_InputSource<stringT>& source)
    {
      SAX::FeatureNames<stringT> fNames;
      SAX::PropertyNames<stringT> pNames;
      
      DOM::DOMImplementation<stringT> di = SimpleDOM::DOMImplementation<stringT, string_adaptorT>::getDOMImplementation();
      document_ = di.createDocument(SA_.makeStringT(""), SA_.makeStringT(""), 0);
      currentNode_ = document_;
      inCDATA_ = false;
      inEntity_ = 0;

      SAX_parser parser;
		  parser.setContentHandler(*this);
		  parser.setErrorHandler(*this);
      if(entityResolver_)
        parser.setEntityResolver(*entityResolver_);
      try 
      {
        parser.setProperty(pNames.lexicalHandler, static_cast<SAX::basic_LexicalHandler<stringT>&>(*this));
        parser.setProperty(pNames.declHandler, static_cast<SAX::basic_DeclHandler<stringT>&>(*this));
      }
      catch(SAX::SAXException&)
      {
      } // catch
      parser.setFeature(fNames.namespaces, true);
      parser.setFeature(fNames.namespace_prefixes, true);
      //parser.setFeature(fNames.external_general, true);

      parser.parse(source);

      return (document_ != 0);
    } // loadDOM

    DOM::Document<stringT> getDocument() const
    {
      return document_;
    } // getDocument

    void reset()
    {
      currentNode_ = 0;
      document_ = 0;
    } // reset

  private:
    // no implementations
    Parser(const Parser&);
    bool operator==(const Parser&) const;
    Parser& operator=(const Parser&);

    // instance variables
    DOM::Document<stringT> document_;
    DocumentType<stringT, string_adaptorT >* documentType_;
    DOM::Node<stringT> currentNode_;
    DOM::Node<stringT> cachedCurrent_;

    std::string lastError_;
    bool inCDATA_;
    int inEntity_;
    string_adaptorT SA_;
    std::map<stringT, EntityT*> declaredEntities_;

    EntityResolverT* entityResolver_;
    ErrorHandlerT* errorHandler_;
    SAX::AttributeTypes<stringT, string_adaptorT> attributeTypes_;

  private:
    ///////////////////////////////////////////////////////////
    // ContentHandler
    virtual void endDocument()
    {
      currentNode_ = 0;
    } // endDocument

    virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const SAX::basic_Attributes<stringT>& atts)
    {
      if(currentNode_ == 0)
        return;

      DOM::Element<stringT> elem = document_.createElementNS(namespaceURI, qName);
      currentNode_.appendChild(elem);

      // attributes here
      for(int i = 0; i < atts.getLength(); ++i)
        elem.setAttributeNS(atts.getURI(i), atts.getQName(i), atts.getValue(i));

      currentNode_ = elem;
    } // startElement

    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
    {
      if(currentNode_ == 0)
        return;

      currentNode_ = currentNode_.getParentNode();
    } // endElement

    virtual void characters(const stringT& ch)
    {
      if(currentNode_ == 0)
        return;

      if(!inCDATA_)
        currentNode_.appendChild(document_.createTextNode(ch));
      else
        currentNode_.appendChild(document_.createCDATASection(ch));
    } // characters

    virtual void processingInstruction(const stringT& target, const stringT& data)
    {
      if(currentNode_ == 0)
        return;

      currentNode_.appendChild(document_.createProcessingInstruction(target, data));
    } // processingInstruction

    virtual void skippedEntity(const stringT& name)
    {
      if(currentNode_ == 0)
        return;

      currentNode_.appendChild(document_.createEntityReference(name));
    } // skippedEntity

    ////////////////////////////////////////////////////
    // ErrorHandler
    virtual void warning(const SAXParseExceptionT& e) 
    { 
      if(errorHandler_)
        errorHandler_->warning(e);
    } // warning

    virtual void error(const SAXParseExceptionT& e) 
    {
      if(errorHandler_)
        errorHandler_->error(e);
      reset();
    } // error

    virtual void fatalError(const SAXParseExceptionT& e)
    {
      if(errorHandler_)
        errorHandler_->fatalError(e);
      reset();
    } // fatalError

    /////////////////////////////////////////////////////
    // LexicalHandler
    virtual void startDTD(const stringT& name, const stringT& publicId, const stringT& systemId)
    {
      documentType_ = new DocumentType<stringT, string_adaptorT >(name, publicId, systemId);
      document_.insertBefore(documentType_, 0);
    } // startDTD

    virtual void endDTD()
    {
      documentType_->setReadOnly(true);
    } // endDTD

    virtual void startEntity(const stringT& name)
    {
      if(currentNode_ == 0)
        return;

      if(++inEntity_ == 1)
      {
        cachedCurrent_ = currentNode_;
        currentNode_ = declaredEntities_[name];
        if(currentNode_ != 0 && currentNode_.hasChildNodes() == true) // already populated
          currentNode_ = 0;
      }
    } // startEntity

    virtual void endEntity(const stringT& name)
    {
      if(--inEntity_ == 0)
        currentNode_ = cachedCurrent_;

      currentNode_.appendChild(document_.createEntityReference(name));
    } // endEntity

    virtual void startCDATA()
    {
      inCDATA_ = true;
    } // startCDATA

    virtual void endCDATA()
    {
      inCDATA_ = false;
    } // endCDATA

    virtual void comment(const stringT& text)
    {
      if(currentNode_ == 0)
        return;

      currentNode_.appendChild(document_.createComment(text));
    } // comment

    //////////////////////////////////////////////////////////////////////
    // DeclHandler
    virtual void elementDecl(const stringT& name, const stringT& model)
    {
      documentType_->addElement(new ElementT(0, name));
    } // elementDecl

    virtual void attributeDecl(const stringT& elementName,
                               const stringT& attributeName,
                               const stringT& type,
                               const stringT& valueDefault,
                               const stringT& value)
    {
      if(!value.empty())
        documentType_->addDefaultAttr(elementName, attributeName, value);
      if(type == attributeTypes_.id)
        documentType_->addElementId(attributeName);
    } // attributeDecl

    virtual void internalEntityDecl(const stringT& name, const stringT& value)
    {
      EntityT* entity = new EntityT(0, name, SA_.makeStringT(""), SA_.makeStringT(""), SA_.makeStringT(""));
      declaredEntities_.insert(std::make_pair(name, entity));
      documentType_->addEntity(entity);
      currentNode_ = entity;
      currentNode_.appendChild(document_.createTextNode(value));
      currentNode_ = document_;
    } // internalEntityDecl

    virtual void externalEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
    {
      EntityT* entity = new EntityT(0, name, publicId, systemId, SA_.makeStringT(""));
      currentNode_ = entity;

      declaredEntities_.insert(std::make_pair(name, entity)); // we'll populate it later

      documentType_->addEntity(entity);
      currentNode_ = document_;
    } // externalEntityDecl

    /////////////////////////////////////////////////////////////////////////
    // DTDHandler
    virtual void notationDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
    {
      documentType_->addNotation(new NotationT(0, name, publicId, systemId));
    } // notationDecl

    virtual void unparsedEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId, const stringT& notationName)
    {
      documentType_->addEntity(new EntityT(0, name, publicId, systemId, notationName));
    } // unparsedEntityDecl
}; // class Parser

} // namespace

#endif

