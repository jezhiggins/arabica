#ifndef ARABICA_XSLT_ITEM_HPP
#define ARABICA_XSLT_ITEM_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor> class ExecutionContext;

template<class string_type, class string_adaptor>
class Item
{
public:
  virtual ~Item() 
  {
  } // ~Item

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const = 0;
}; // class Item

template<class string_type, class string_adaptor>
class ItemContainer : public Item<string_type, string_adaptor>
{
protected:
  virtual ~ItemContainer() 
  { 
    for(ChildrenIterator ci = children_.begin(), ce = children_.end(); ci != ce; ++ci)
      delete *ci;
  } // ~ItemContainer

  void execute_children(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    for(ChildrenIterator ci = children_.begin(), ce = children_.end(); ci != ce; ++ci)
      (*ci)->execute(node, context);
  } // execute

public:
  void add_item(Item<string_type, string_adaptor>* child) 
  {
    children_.push_back(child);
  } // add_child

private:
  typedef std::vector<Item<string_type, string_adaptor>*> Children;
  typedef typename Children::const_iterator ChildrenIterator;

  Children children_;
}; // ItemContainer

} // namespace XSLT
} // namespace Arabica

#endif

