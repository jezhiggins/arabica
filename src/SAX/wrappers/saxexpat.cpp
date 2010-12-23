/*
 * $Id$
 */

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <SAX/ParserConfig.hpp>

namespace Arabica
{
namespace SAX
{

namespace expat_wrapper_impl_mumbojumbo
{

////////////////////////////////////////////////////////////////////////
// expat callback function definition
void ewim_charHandler(void* data, const char* txt, int txtlen)
{
  expat2base* p = reinterpret_cast<expat2base*>(data);
  p->charHandler(txt, txtlen);
} // charHandler

void ewim_startElement(void* data, const char* qName, const char** atts)
{
  expat2base* p = reinterpret_cast<expat2base*>(data);
  p->startElement(qName, atts);
} // startElement

void ewim_endElement(void* data, const char* qName)
{
  expat2base* p = reinterpret_cast<expat2base*>(data);
  p->endElement(qName);
} // endElement

void ewim_processingInstruction(void* userData, const char* target, const char* data)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->processingInstruction(target, data);
} // processingInstruction

void ewim_elementDeclaration(void* userData, const XML_Char* name, XML_Content* model)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->elementDeclaration(name, model);
} // elementDeclaration

void ewim_attListDeclaration(void* userData,
                        const XML_Char* elname,
					              const XML_Char* attname,
					              const XML_Char* att_type,
					              const XML_Char* dflt,
					              int isrequired)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->attListDeclaration(elname, attname, att_type, dflt, isrequired);
} // attListDeclaration

void ewim_entityDeclaration(void* userData, 
                      const XML_Char* entityName,
                      int is_parameter_entity,
                      const XML_Char* value,
                      int value_length,
                      const XML_Char* base,
				              const XML_Char* systemId, 
                      const XML_Char* publicId, 
                      const XML_Char* notationName)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->entityDeclaration(entityName, is_parameter_entity, value, value_length,
                       base, systemId, publicId, notationName);

} // entityDeclaration

void ewim_notationDeclaration(void* userData,
					                const XML_Char* notationName,
					                const XML_Char* base,
					                const XML_Char* systemId,
					                const XML_Char* publicId)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->notationDeclaration(notationName, base, systemId, publicId);
} // notationDeclHandler

void ewim_startDoctypeDecl(void* userData,
 				                   const XML_Char* doctypeName,
				                   const XML_Char* sysid,
					                 const XML_Char* pubid,
					                 int has_internal_subset)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->startDoctypeDecl(doctypeName, sysid, pubid, has_internal_subset);
} // startDoctypeDecl

void ewim_endDoctypeDecl(void* userData)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->endDoctypeDecl();
} // endDoctypeDecl

void ewim_startCdataSection(void* userData)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->startCdataSection();
} // startCdatSection

void ewim_endCdataSection(void* userData)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->endCdataSection();
} // endCdataSection

void ewim_commentHandler(void* userData, const XML_Char* data)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->commentHandler(data);
} // commentHandler

void ewim_skippedEntityHandler(void* userData, const XML_Char* entityName, int /* is_parameter_entity */)
{
  expat2base* p = reinterpret_cast<expat2base*>(userData);
  p->skippedEntity(entityName);
} // skippedEntityHandler


int ewim_externalEntityRefHandler(XML_Parser parser, 
                                  const XML_Char* context,
                                  const XML_Char* base,
                                  const XML_Char* systemId,
                                  const XML_Char* publicId)
{
  expat2base* p = reinterpret_cast<expat2base*>(XML_GetUserData(parser));
  return p->externalEntityRefHandler(parser, context, base, systemId, publicId);
} // externalEntityRefHandler

} // namespace expat_wrapper_impl_mumbojumbo
} // namespace SAX
} // namespace Arabica

// end of file

