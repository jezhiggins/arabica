#ifndef JEZUK_DOM_TRAVERSAL_IMPL_H
#define JEZUK_DOM_TRAVERSAL_IMPL_H

namespace Arabica
{
namespace DOM
{

//todo: move this class somewhere (or rename to TraversalImpl??)
class TraversalImpl
{
public:
  TraversalImpl() : refCount_(0)
  {}

  virtual ~TraversalImpl() {}

  ///////////////////////////////////////////////////////
  // Ref counting
  virtual void addRef()
  {
    ++refCount_;
  } // addRef

  virtual void releaseRef()
  {
    if(--refCount_ == 0)
      delete this;
  } // releaseRef


private:
  int refCount_;
}; //class TraversalImpl

} // namespace DOM
} // namespace Arabica

#endif //JEZUK_DOM_TRAVERSAL_IMPL_H
