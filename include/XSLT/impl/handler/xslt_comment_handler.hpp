#ifndef ARABICA_XSLT_COMMENT_HANDLER_HPP
#define ARABICA_XSLT_COMMENT_HANDLER_HPP

#include "../xslt_comment.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class CommentHandler : public ItemContainerHandler<Comment>
{
public:
  CommentHandler(CompilationContext& context) :
      ItemContainerHandler<Comment>(context)
  {
  } // CommentHandler

  virtual Comment* createContainer(const std::string& /* namespaceURI */,
                                   const std::string& /* localName */,
                                   const std::string& /* qName */,
                                   const SAX::Attributes<std::string>& atts)
  {
    if(atts.getLength() != 0)
      throw SAX::SAXException("xsl:comment can not have attributes");

    return new Comment();
  } // createContainer
}; // class CommentHandler

} // namespace XSLT
} // namespace Arabica

#endif

