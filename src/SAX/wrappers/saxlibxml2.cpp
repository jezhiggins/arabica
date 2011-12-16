/*@
 * $Id$
 */

#ifdef _MSC_VER
#pragma warning(disable: 4786 4800)
#endif

#include <SAX/ParserConfig.hpp>

#include <SAX/SAXNotRecognizedException.hpp>

namespace Arabica
{
namespace SAX
{
namespace libxml2_wrapper_impl_tiddle
{

std::string formatErrorMsg(const char* fmt, va_list arg)
{
  char buff[4096];
  vsprintf(buff, fmt, arg);
	return std::string(buff);
} // formatErrorMsg

void lwit_startDocument(void* user_data)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->parserContext()->myDoc = xmlNewDoc(p->parserContext()->version);
  p->parserContext()->myDoc->intSubset = xmlNewDtd(p->parserContext()->myDoc, BAD_CAST "fake", NULL, NULL);
  p->SAXstartDocument();
} // lwit_startDocument

void lwit_endDocument(void* user_data)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXendDocument();
  xmlFreeDoc(p->parserContext()->myDoc);
  p->parserContext()->myDoc = 0;
} // lwit_endDocument

void lwit_startElement(void *user_data, const xmlChar* name, const xmlChar** attrs)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXstartElement(name, attrs);
} // lwit_startElement

void lwit_endElement(void *user_data, const xmlChar* name)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXendElement(name);
} // lwit_endElement

void lwit_characters(void* user_data, const xmlChar* ch, int len)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXcharacters(ch, len);
} // lwit_characters

void lwit_ignorableWhitespace(void *user_data, const xmlChar* ch, int len)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXignorableWhitespace(ch, len);
} // lwit_ignorableWhitespace

void lwit_processingInstruction(void *user_data, const xmlChar* target, const xmlChar* data)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXprocessingInstruction(target, data);
} // lwit_processingInstruction

void lwit_comment(void *user_data, const xmlChar* comment)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXcomment(comment);
} // lwit_comment

void lwit_warning(void *user_data, const char* fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  std::string msg(formatErrorMsg(fmt, arg));
  va_end(arg);

  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXwarning(msg);
} // lwit_warning

void lwit_error(void* user_data, const char* fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  std::string msg(formatErrorMsg(fmt, arg));
  va_end(arg);

  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXerror(msg);
} // lwit_error

void lwit_fatalError(void* user_data, const char* fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  std::string msg(formatErrorMsg(fmt, arg));
  va_end(arg);

  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXfatalError(msg);
} // lwit_fatalError

void lwit_locator(void* user_data, xmlSAXLocatorPtr locator)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
	p->SAXlocator(locator);
} // lwit_locator

void lwit_notationDecl(void* user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXnotationDecl(name, publicId, systemId);
} // lwit_notationDecl

void lwit_unparsedEntityDecl(void* user_data,
                           const xmlChar *name, const xmlChar *publicId,
			                     const xmlChar *systemId, const xmlChar *notationName)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXunparsedEntityDecl(name, publicId, systemId, notationName);
} // lwit_unparsedEntityDecl

void lwit_elementDecl(void* user_data, const xmlChar *name, int type, xmlElementContentPtr content)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXelementDecl(name, type, content);
} // lwit_elementDecl

void lwit_attributeDecl(void *user_data, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXattributeDecl(elem, fullname, type, def, defaultValue, tree);
} // lwit_attributeDecl

void lwit_entityDecl(void* user_data, const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  p->SAXentityDecl(name, type, publicId, systemId, content);
  xmlSAX2EntityDecl(p->parserContext(), name, type, publicId, systemId, content);
} // lwit_entityDecl

xmlParserInputPtr lwit_resolveEntity(void* user_data, const xmlChar* publicId, const xmlChar* systemId)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  return p->SAXresolveEntity(publicId, systemId);
} // lwit_resolveEntity

xmlEntityPtr lwit_getEntity(void* user_data, const xmlChar* name)
{
  libxml2_base* p = reinterpret_cast<libxml2_base*>(user_data);
  xmlEntityPtr ent = xmlSAX2GetEntity(p->parserContext(), name);
  return ent;
} // lwit_getEntity

class libxmlInitialiser 
{
public:
  libxmlInitialiser() { xmlInitParser(); }
};

static xmlSAXHandler saxHandler = {
		0,		// internalSubsetSAXFunc internalSubset;
		0,		// isStandaloneSAXFunc isStandalone;
		0,		// hasInternalSubsetSAXFunc hasInternalSubset;
		0,		// hasExternalSubsetSAXFunc hasExternalSubset;
		lwit_resolveEntity,		// resolveEntitySAXFunc resolveEntity;
		lwit_getEntity,		// getEntitySAXFunc getEntity;
		lwit_entityDecl,   	// entityDeclSAXFunc entityDecl;
		lwit_notationDecl,		// notationDeclSAXFunc notationDecl;
		lwit_attributeDecl,		// attributeDeclSAXFunc attributeDecl;
		lwit_elementDecl,		// elementDeclSAXFunc elementDecl;
		lwit_unparsedEntityDecl,		// unparsedEntityDeclSAXFunc unparsedEntityDecl;
		lwit_locator,		// setDocumentLocatorSAXFunc setDocumentLocator;
		lwit_startDocument,		// startDocumentSAXFunc startDocument;
		lwit_endDocument,		// endDocumentSAXFunc endDocument;
		lwit_startElement,		// startElementSAXFunc startElement;
		lwit_endElement,		// endElementSAXFunc endElement;
		0,		// referenceSAXFunc reference;
		lwit_characters,		// charactersSAXFunc characters;
		lwit_ignorableWhitespace,		// ignorableWhitespaceSAXFunc ignorableWhitespace;
		lwit_processingInstruction,		// processingInstructionSAXFunc processingInstruction;
		lwit_comment,		// commentSAXFunc comment;
		lwit_warning,		// warningSAXFunc warning;
		lwit_error,		// errorSAXFunc error;
		lwit_fatalError,		// fatalErrorSAXFunc fatalError;
		0,		// getParameterEntitySAXFunc getParameterEntity;
		lwit_characters,		// cdataBlockSAXFunc cdataBlock;
		0,		// externalSubsetSAXFunc externalSubset;
    0,    //  initialized;
    /* The following fields are extensions available only on version 2 */
    0,    // _private
    0,    // startElementNs
    0,    // endElementNs;
    0     // serror;
    };

xmlSAXHandler* lwit_SaxHandler() 
{ 
  static libxmlInitialiser init; 
  return &saxHandler; 
}

void lwit_setFeature(xmlParserCtxtPtr context, const char* name, bool value)
{
  int v = value;
  if(xmlSetFeature(context, name, reinterpret_cast<void*>(&v)) == -1)
  {
    std::ostringstream os; 
    os << "Feature not recognized " << name;
    throw SAX::SAXNotRecognizedException(os.str());
  } // if ...
} // lwitSetFeature

bool lwit_getFeature(xmlParserCtxtPtr context, const char* name)
{
  int v;
  if(xmlGetFeature(context, name, reinterpret_cast<void*>(&v)) == -1)
  {
    std::ostringstream os; 
    os << "Feature not recognized " << name;
    throw SAX::SAXNotRecognizedException(os.str());
  } // if ...
  return static_cast<bool>(v);
} // lwit_getFeature

} // namespace libxml2_wrapper_impl_tiddle

} // namespace SAX
} // namespace Arabica

// end of file
