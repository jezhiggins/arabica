#ifndef ARABICA_XSLT_KEY_HPP
#define ARABICA_XSLT_KEY_HPP

namespace Arabica
{
namespace XSLT
{

class Key
{
public: 
  typedef std::vector<Arabica::XPath::MatchExpr<std::string> > MatchExprList;

  Key(MatchExprList& matches,
      Arabica::XPath::XPathExpression<std::string>& use) :
    matches_(matches),
    use_(use),
    populated_(false)
  {
  } // Key

  Arabica::DOM::Node<std::string> lookup(const std::string& value) const
  {
    if(!populated_)
      populate();

    NodeMap::const_iterator f = nodes_.find(value);
    if(f == nodes_.end())
      return DOM::Node<std::string>(0);

    return f->second;
  } // lookup

private:
  void populate() const
  {
    std::cerr << "Populating key map " << std::endl;
    populated_ = true;
  } // populate

  MatchExprList matches_;
  Arabica::XPath::XPathExpression<std::string> use_;
  mutable bool populated_;

  typedef std::map<std::string, Arabica::DOM::Node<std::string> > NodeMap;
  NodeMap nodes_;
}; // class Key

} // namespace XSLT
} // namespace Arabica


#endif
