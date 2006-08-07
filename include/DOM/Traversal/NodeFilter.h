#ifndef JEZUK_DOM_TRAVERSAL_NODEFILTER_H
#define JEZUK_DOM_TRAVERSAL_NODEFILTER_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

namespace DOM
{

namespace Traversal
{

template<class stringT>
class NodeFilter 
{
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

  private:
    virtual ~NodeFilter() { }
}; // class NodeFilter

} // namespace Traversal

} // namespace DOM

#endif 
// end of file