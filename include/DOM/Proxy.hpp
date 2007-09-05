#ifndef JEZUK_DOM_PROXY_H
#define JEZUK_DOM_PROXY_H

namespace Arabica
{
namespace DOM
{

template<class ImplementationT>
class Proxy
{
  public:
    typedef ImplementationT value_type;

    Proxy() : impl_(0) { }
    Proxy(ImplementationT* impl) : impl_(0) { setImpl(impl); }
    Proxy(const Proxy& rhs) : impl_(0) { setImpl(rhs.impl_); }
    ~Proxy() { setImpl(0); }

    Proxy& operator=(const Proxy& rhs)
    {
      setImpl(rhs.impl_);
      return *this;
    } // operator=
    Proxy& operator=(ImplementationT* const impl)
    {
      setImpl(impl);
      return *this;
    } // operator=
 
    operator bool() const { return 0 != impl_; }
    bool operator==(int dummy) const { return (dummy == 0) && (impl_ == 0); }
    bool operator!=(int dummy) const { return !(operator==(dummy)); }
    bool operator==(const Proxy& rhs) const { return (impl_ == rhs.impl_); }
    bool operator!=(const Proxy& rhs) const { return !(operator==(rhs)); }
    bool operator==(ImplementationT* const impl) const { return (impl_ == impl); }
    bool operator!=(ImplementationT* const impl) const { return !(operator==(impl)); }

    const ImplementationT* impl() const { return impl_; }
    ImplementationT* impl() { return impl_; }

    ImplementationT* operator*() const
    {
      return impl_;
    } // operator*

    ImplementationT* operator->() const
    {
      return impl_;
    } // operator->

  private:
    void setImpl(ImplementationT* const impl)
    {
      if(impl_)
      {
        impl_->releaseRef();
        impl_ = 0;
      }
      if(impl)
      {
        impl_ = impl;
        impl_->addRef();
      } // if(impl)
    } // setImpl

    // the thing that actually does the work!
    ImplementationT* impl_;
}; // class Proxy

} // namespace DOM
} // namespace Arabica

#endif

