#ifndef JEZUK_DOM_TRAVERSAL_NODEFILTER_H
#define JEZUK_DOM_TRAVERSAL_NODEFILTER_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class Node;

namespace Traversal
{

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NodeFilter 
{
  public:
    typedef DOM::Node<stringT, string_adaptorT> NodeT;

  protected:
    virtual ~NodeFilter() { }

  public:
    ///////////////////////////////////////////////////////////////
    // NodeFilter methods
    enum Result
    {
      FILTER_ACCEPT = 1,
      FILTER_REJECT = 2,
      FILTER_SKIP = 3
    }; // Result

    virtual Result acceptNode(const NodeT& node) const = 0;

}; // class NodeFilter

} // namespace Traversal

} // namespace DOM
} // namespace Arabica

#endif 
// end of file

