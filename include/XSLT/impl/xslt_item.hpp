#ifndef ARABICA_XSLT_ITEM_HPP
#define ARABICA_XSLT_ITEM_HPP

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
  virtual ~ItemContainer() 
  { 
    for(Children::const_iterator ci = children_.begin(), ce = children_.end(); ci != ce; ++ci)
      delete *ci;
  } // ~ItemContainer

  void execute_children(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    for(Children::const_iterator ci = children_.begin(), ce = children_.end(); ci != ce; ++ci)
      (*ci)->execute(node, context);
  } // execute

public:
  void add_item(Item* child) 
  {
    children_.push_back(child);
  } // add_child

private:
  typedef std::vector<Item*> Children;
  Children children_;
}; // ItemContainer

} // namespace XSLT
} // namespace Arabica

#endif

