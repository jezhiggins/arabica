#ifndef ARABICA_XSLT_COMMENT_HANDLER_HPP
#define ARABICA_XSLT_COMMENT_HANDLER_HPP

#include "../xslt_comment.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class CommentHandler : public ItemContainerHandler<Comment<stringT, adaptorT> >
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  CommentHandler(CompilationContext<string_type, string_adaptor>& context) :
      ItemContainerHandler<Comment<string_type, string_adaptor> >(context)
  {
  } // CommentHandler

  virtual Comment<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                   const string_type& /* localName */,
                                   const string_type& /* qName */,
                                   const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(atts.getLength() != 0)
      throw SAX::SAXException("xsl:comment can not have attributes");

    return new Comment<string_type, string_adaptor>();
  } // createContainer
}; // class CommentHandler

} // namespace XSLT
} // namespace Arabica

#endif

