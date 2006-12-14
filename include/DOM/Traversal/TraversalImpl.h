#ifndef JEZUK_DOM_TRAVERSAL_IMPL_H
#define JEZUK_DOM_TRAVERSAL_IMPL_H

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

}; //class Impl



} // namespace DOM

#endif //JEZUK_DOM_TRAVERSAL_IMPL_H
