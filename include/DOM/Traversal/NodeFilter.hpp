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

namespace Traversal
{

template<class stringT>
class NodeFilter 
{
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

    virtual Result acceptNode(const DOM::Node<stringT>& node) const = 0;

}; // class NodeFilter

} // namespace Traversal

} // namespace DOM
} // namespace Arabica

#endif 
// end of file

