#ifndef ARABICA_XPATH_RESOLVER_HOLDER_HPP
#define ARABICA_XPATH_RESOLVER_HOLDER_HPP

#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<typename ResolverT>
class ResolverHolder
{
public:
  typedef boost::shared_ptr<ResolverT> ResolverPtrT;

  ResolverHolder() :
    unowned_(0),
    shared_() 
  {
  } // ResolverHolder

  ResolverHolder(const ResolverHolder& rhs) :
    unowned_(rhs.unowned_),
    shared_(rhs.shared_)
  {
  } // ResolverHolder

  ResolverHolder& operator=(const ResolverHolder& rhs)
  {
    if(rhs == *this)
      return *this;

    unowned_ = rhs.unowned_;
    shared_ = rhs.shared_;

    return *this;
  } // operator=

  ResolverT& get() const
  {
    if(unowned_)
      return *unowned_;
    return *(shared_.get());
  } // get()

  void set(ResolverT& resolver)
  {
    unowned_ = &resolver;
    shared_.reset();
  } // set

  void set(ResolverPtrT resolver)
  {
    unowned_ = 0;
    shared_ = resolver;
  } // set

private:
  ResolverT* unowned_;
  ResolverPtrT shared_;

  bool operator==(const ResolverHolder&);
}; // ResolverHolder

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
