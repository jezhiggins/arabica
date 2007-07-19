#ifndef ARABICA_XSLT_ITEM_HPP
#define ARABICA_XSLT_ITEM_HPP

#include <boost/ptr_container/ptr_vector.hpp>

namespace Arabica
{
namespace XSLT
{

class ExecutionContext;

class Item
{
public:
  virtual ~Item() 
  {
  } // ~Item

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const = 0;
}; // class Item

class ItemContainer : public Item
{
protected:
  typedef boost::ptr_vector<Item> Children;

  ~ItemContainer() 
  { 
  } // ~ItemContainer

  void execute_children(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    for(Children::const_iterator ci = children_begin(), ce = children_end(); ci != ce; ++ci)
      ci->execute(node, context);
  } // execute

  Children::const_iterator children_begin() const { return children_.begin(); }
  Children::const_iterator children_end() const { return children_.end(); }

public:
  void add_item(Item* child) 
  {
    children_.push_back(child);
  } // add_child

private:
  Children children_;
}; // ItemContainer

} // namespace XSLT
} // namespace Arabica

#endif

