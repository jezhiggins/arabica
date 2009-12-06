#ifndef JEZUK_SAX2DOM_PARSER_H
#define JEZUK_SAX2DOM_PARSER_H

#include <SAX/XMLReader.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <SAX/helpers/AttributeTypes.hpp>
#include <SAX/filter/TextCoalescer.hpp>
#include <DOM/Simple/DOMImplementation.hpp>
#include <DOM/Simple/NotationImpl.hpp>
#include <DOM/Simple/EntityImpl.hpp>
#include <DOM/Document.hpp>
#include <DOM/DOMException.hpp>
#include <DOM/SAX2DOM/DocumentTypeImpl.hpp>
#include <map>
#include <SAX/helpers/FeatureNames.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <SAX/SAXParseException.hpp>

namespace Arabica
{
namespace SAX2DOM
{

template<class string_type, class T0, class T1>
struct ParserTypes
{
  typedef typename Arabica::get_param<Arabica::string_adaptor_tag, 
                           Arabica::default_string_adaptor<string_type>, 
                           T0, 
                           T1>::type string_adaptor;
  typedef typename Arabica::get_param<Arabica::SAX::XMLReaderInterface_tag, 
                                      Arabica::SAX::XMLReader<string_type, string_adaptor>, 
                                      T1, 
                                      T0>::type SAX_parser_type;
};

template<class stringT, 
         class T0 = Arabica::nil_t,
         class T1 = Arabica::nil_t>
class Parser : protected Arabica::SAX::DefaultHandler<stringT, typename ParserTypes<stringT, T0, T1>::string_adaptor>
{
    typedef typename ParserTypes<stringT, T0, T1>::string_adaptor string_adaptorT;
    typedef typename ParserTypes<stringT, T0, T1>::SAX_parser_type SAX_parser_type;
    typedef Arabica::SAX::XMLReaderInterface<stringT, string_adaptorT> XMLReaderInterfaceT;
    typedef Arabica::SAX::TextCoalescer<stringT, string_adaptorT> TextCoalescerT;
    typedef Arabica::SAX::Attributes<stringT, string_adaptorT> AttributesT;
    typedef Arabica::SAX::EntityResolver<stringT, string_adaptorT> EntityResolverT;
    typedef Arabica::SAX::ErrorHandler<stringT, string_adaptorT> ErrorHandlerT;
    typedef Arabica::SAX::LexicalHandler<stringT, string_adaptorT> LexicalHandlerT;
    typedef Arabica::SAX::DeclHandler<stringT, string_adaptorT> DeclHandlerT;
    typedef Arabica::SAX::InputSource<stringT, string_adaptorT> InputSourceT;
    typedef Arabica::SimpleDOM::EntityImpl<stringT, string_adaptorT> EntityT;
    typedef Arabica::SimpleDOM::NotationImpl<stringT, string_adaptorT> NotationT;
    typedef Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT> ElementT;
    typedef typename ErrorHandlerT::SAXParseExceptionT SAXParseExceptionT;

  public:
    Parser() :
        documentType_(0),
        entityResolver_(0),
        errorHandler_(0)
    { 
      Arabica::SAX::FeatureNames<stringT, string_adaptorT> fNames;
      features_.insert(std::make_pair(fNames.namespaces, true));
      features_.insert(std::make_pair(fNames.namespace_prefixes, true));
      features_.insert(std::make_pair(fNames.validation, false));
    } // Parser

    void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
    EntityResolverT* getEntityResolver() const { return entityResolver_; }

    void setErrorHandler(ErrorHandlerT& handler) { errorHandler_ = &handler; }
    ErrorHandlerT* getErrorHandler() const { return errorHandler_; }

    void setFeature(const stringT& name, bool value)
    {
      typename Features::iterator f = features_.find(name);
      if(f == features_.end())
        features_.insert(std::make_pair(name, value));
      else
        f->second = value;
    } // setFeature

    bool getFeature(const stringT& name) const
    {
      typename Features::const_iterator f = features_.find(name);
      if(f == features_.end())
        throw Arabica::SAX::SAXNotRecognizedException(std::string("Feature not recognized ") + string_adaptorT::asStdString(name));
      return f->second;
    } // getFeature

    bool parse(const stringT& systemId)
    {
      InputSourceT is(systemId);
      return parse(is);
    } // loadDOM

    bool parse(InputSourceT& source)
    {
      Arabica::SAX::PropertyNames<stringT, string_adaptorT> pNames;
      
      DOM::DOMImplementation<stringT, string_adaptorT> di = Arabica::SimpleDOM::DOMImplementation<stringT, string_adaptorT>::getDOMImplementation();
      document_ = di.createDocument(string_adaptorT::construct_from_utf8(""), string_adaptorT::construct_from_utf8(""), 0);
      currentNode_ = document_;
      inCDATA_ = false;
      inDTD_ = false;
      inEntity_ = 0;

      SAX_parser_type base_parser;
      TextCoalescerT parser(base_parser);
		  parser.setContentHandler(*this);
		  parser.setErrorHandler(*this);
      if(entityResolver_)
        parser.setEntityResolver(*entityResolver_);

      parser.setLexicalHandler(*this);
      parser.setDeclHandler(*this);

      setParserFeatures(parser);

      try 
      {
        parser.parse(source);
      }
      catch(const DOM::DOMException& de)
      {
        document_ = 0;

        if(errorHandler_)
        {
          SAXParseExceptionT pe(de.what());
          errorHandler_->fatalError(pe);
        } // if ...
      } // catch

      return (document_ != 0);
    } // loadDOM

    DOM::Document<stringT, string_adaptorT> getDocument() const
    {
      return document_;
    } // getDocument

    void reset()
    {
      currentNode_ = 0;
      document_ = 0;
    } // reset

  protected:
    DOM::Node<stringT, string_adaptorT>& currentNode() { return currentNode_; }

  private:
    // no implementations
    Parser(const Parser&);
    bool operator==(const Parser&) const;
    Parser& operator=(const Parser&);

    // instance variables
    DOM::Document<stringT, string_adaptorT> document_;
    DocumentType<stringT, string_adaptorT >* documentType_;
    DOM::Node<stringT, string_adaptorT> currentNode_;
    DOM::Node<stringT, string_adaptorT> cachedCurrent_;

    typedef std::map<stringT, bool> Features;
    Features features_;

    bool inCDATA_;
    bool inDTD_;
    int inEntity_;

    std::map<stringT, EntityT*> declaredEntities_;

    EntityResolverT* entityResolver_;
    ErrorHandlerT* errorHandler_;
    Arabica::SAX::AttributeTypes<stringT, string_adaptorT> attributeTypes_;

  protected:
    void setParserFeatures(XMLReaderInterfaceT& parser) const
    {
      for(typename Features::const_iterator f = features_.begin(), e = features_.end(); f != e; ++f)
        try {
          parser.setFeature(f->first, f->second);
        }
        catch(const Arabica::SAX::SAXException&) { }
    } // setParserFeatures

    ///////////////////////////////////////////////////////////
    // ContentHandler
    virtual void endDocument()
    {
      currentNode_ = 0;
    } // endDocument

    virtual void startElement(const stringT& namespaceURI, const stringT& /*localName*/,
                              const stringT& qName, const AttributesT& atts)
    {
      if(currentNode_ == 0)
        return;

      try 
      {
        DOM::Element<stringT, string_adaptorT> elem = document_.createElementNS(namespaceURI, qName);
        currentNode_.appendChild(elem);

        // attributes here
        for(int i = 0; i < atts.getLength(); ++i)
        {
          stringT qName = atts.getQName(i);
          if(string_adaptorT::empty(qName))
            qName = atts.getLocalName(i);
          elem.setAttributeNS(atts.getURI(i), qName, atts.getValue(i));
        }

        currentNode_ = elem;
      }
      catch(const DOM::DOMException& de)
      {
        reset();

        if(errorHandler_)
        {
          SAXParseExceptionT pe(de.what());
          errorHandler_->fatalError(pe);
        } // if ...
      } // catch
    } // startElement

    virtual void endElement(const stringT& /*namespaceURI*/, const stringT& /*localName*/,
                            const stringT& /*qName*/)
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
      if(currentNode_ == 0 || inDTD_ == true)
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
      inDTD_ = true;
    } // startDTD

    virtual void endDTD()
    {
      documentType_->setReadOnly(true);
      inDTD_ = false;
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
    virtual void elementDecl(const stringT& name, const stringT& /*model*/)
    {
      if(!documentType_)
        return;
      documentType_->addElement(name);
    } // elementDecl

    virtual void attributeDecl(const stringT& elementName,
                               const stringT& attributeName,
                               const stringT& type,
                               const stringT& /*valueDefault*/,
                               const stringT& value)
    {
      if(!documentType_)
        return;
      if(!string_adaptorT::empty(value))
        documentType_->addDefaultAttr(elementName, attributeName, value);
      if(type == attributeTypes_.id)
        documentType_->addElementId(attributeName);
    } // attributeDecl

    virtual void internalEntityDecl(const stringT& name, const stringT& value)
    {
      if(!documentType_)
        return;
      EntityT* entity = new EntityT(0, name, string_adaptorT::construct_from_utf8(""), string_adaptorT::construct_from_utf8(""), string_adaptorT::construct_from_utf8(""));
      declaredEntities_.insert(std::make_pair(name, entity));
      documentType_->addEntity(entity);
      DOM::Node<stringT, string_adaptorT> n = entity;
      n.appendChild(document_.createTextNode(value));
    } // internalEntityDecl

    virtual void externalEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
    {
      if(!documentType_)
        return;
      EntityT* entity = new EntityT(0, name, publicId, systemId, string_adaptorT::construct_from_utf8(""));
      declaredEntities_.insert(std::make_pair(name, entity)); // we'll populate it later
      documentType_->addEntity(entity);
    } // externalEntityDecl

    /////////////////////////////////////////////////////////////////////////
    // DTDHandler
    virtual void notationDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
    {
      if(!documentType_)
        return;
      documentType_->addNotation(new NotationT(0, name, publicId, systemId));
    } // notationDecl

    virtual void unparsedEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId, const stringT& notationName)
    {
      if(!documentType_)
        return;
      documentType_->addEntity(new EntityT(0, name, publicId, systemId, notationName));
    } // unparsedEntityDecl
}; // class Parser

} // namespace SAX2DOM
} // namespace Arabica

#endif

