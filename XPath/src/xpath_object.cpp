#include <XPath/impl/xpath_object.hpp>
#include <XPath/impl/xpath_axis_enumerator.hpp>
#include <boost/lexical_cast.hpp>
#include <set>
#include <sstream>

namespace Arabica
{
namespace XPath
{

template<class string_type>
bool nodeSetsEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  const NodeSet<string_type>& lns = lhs->asNodeSet();
  const NodeSet<string_type>& rns = rhs->asNodeSet();

  if((lns.size() == 0) || (rns.size() == 0))
    return false;

  std::set<string_type> values;
  NodeSet<string_type>::const_iterator l = lns.begin();
  string_type lvalue = nodeStringValue(*l);

  for(NodeSet<string_type>::const_iterator r = rns.begin(), rend = rns.end(); r != rend; ++r)
  {
    string_type rvalue = nodeStringValue(*r);
    if(lvalue == rvalue)
      return true;
    values.insert(rvalue);
  } // for ...

  ++l;
  for(NodeSet<string_type>::const_iterator lend = lns.end(); l != lend; ++l)
    if(values.find(nodeStringValue(*l)) != values.end())
      return true;

  return false;
} // nodeSetsEqual

template<class string_type>
bool nodeSetAndValueEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  const NodeSet<string_type>& lns = lhs->asNodeSet();

  switch(rhs->type())
  {
  case BOOL:
    {
      bool l = !lns.empty();
      bool r = rhs->asBool();

      return l == r;
    } // case BOOL
  case STRING:
    return std::find_if(lns.begin(), lns.end(), compareNodeWith<std::equal_to<string_type> >(rhs->asString())) != lns.end();

  case NUMBER:
    return std::find_if(lns.begin(), lns.end(), compareNodeWith<std::equal_to<double> >(rhs->asNumber())) != lns.end();

  default:
    throw std::runtime_error("Node set == not yet implemented for type " + boost::lexical_cast<std::string>(rhs->type()));
  } // switch
} // nodeSetAndValueEqual

template<class string_type> 
double minValue(const NodeSet<string_type>& ns)
{
  double v = nodeNumberValue(ns[0]);
  for(NodeSet<string_type>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
  {
    double vt = nodeNumberValue(*i);
    if(isNaN(vt))
      continue;
    if(!(vt > v)) // looks weird, but should account for infinity
      v = vt;
  } // for ...
  return v;
} // minValue

template<class string_type> 
double maxValue(const NodeSet<string_type>& ns)
{
  double v = nodeNumberValue(ns[0]);
  for(NodeSet<string_type>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
  {
    double vt = nodeNumberValue(*i);
    if(isNaN(vt))
      continue;
    if(!(vt < v))
      v = vt;
  } // for ...
  return v;
} // maxValue

template<class T> T nodeValue(const DOM::Node<std::string>& node);
template<> std::string nodeValue(const DOM::Node<std::string>& node) { return nodeStringValue(node); }
template<> double nodeValue(const DOM::Node<std::string>& node) { return nodeNumberValue(node); }

template<class Op>
class compareNodeWith
{
  typedef typename Op::first_argument_type T;
public:
  compareNodeWith(const T& value) : value_(value) { }
  compareNodeWith(const compareNodeWith& rhs) : value_(rhs.value_) { }

  bool operator()(const DOM::Node<std::string>& node) 
  {
    return Op()(nodeValue<T>(node), value_);
  } // operator()

private:
  T value_;
  bool operator==(const compareNodeWith&);
  compareNodeWith& operator=(const compareNodeWith&);
}; // class compareNodeWith

template<class Op>
bool compareNodeSets(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  return Op()(minValue(lhs->asNodeSet()), maxValue(rhs->asNodeSet()));
} // compareNodeSets

template<class Op>
bool compareNodeSetWith(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  const NodeSet<std::string>& lns = lhs->asNodeSet();
  return std::find_if(lns.begin(), 
                      lns.end(), 
                      compareNodeWith<Op>(rhs->asNumber())) != lns.end();
} // compareNodeSetAndValue

///////////////////////////////////////////////////
bool areEqual(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return nodeSetsEqual(lhs, rhs);

  if(lt == NODE_SET)
    return nodeSetAndValueEqual(lhs, rhs);
  if(rt == NODE_SET)
    return nodeSetAndValueEqual(rhs, lhs);

  if((lt == BOOL) || (rt == BOOL))
    return lhs->asBool() == rhs->asBool();

  if((lt == NUMBER) || (rt == NUMBER))
    return lhs->asNumber() == rhs->asNumber();

  if((lt == STRING) || (rt == STRING))
    return lhs->asString() == rhs->asString();

  return false;
} // operator==

///////////////////////////////
bool isLessThan(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less<double> >(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less<double> >(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater<double> >(rhs, lhs);

  return lhs->asNumber() < rhs->asNumber();
} // isLessThan

bool isLessThanEquals(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less_equal<double> >(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less_equal<double> >(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater_equal<double> >(rhs, lhs);

  return lhs->asNumber() <= rhs->asNumber();
} // isLessThanEquals

bool isGreaterThan(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  return isLessThan(rhs, lhs);
} // isGreaterThan

bool isGreaterThanEquals(const XPathValuePtr<std::string>& lhs, const XPathValuePtr<std::string>& rhs)
{
  return isLessThanEquals(rhs, lhs);
} // isGreaterThanEquals

////////////////////////////////////
DOM::Node<std::string> node_parent_or_owner(const DOM::Node<std::string>& node)
{
  if(node.getNodeType() == DOM::Node<std::string>::ATTRIBUTE_NODE)
    return (static_cast<DOM::Attr<std::string> >(node)).getOwnerElement();
  return node.getParentNode();
} // node_parent_or_owner

DOM::Node<std::string> ultimate_parent(const DOM::Node<std::string>& origin)
{
  DOM::Node<std::string> n = origin;
  DOM::Node<std::string> p = node_parent_or_owner(n);
  while(p != 0)
  {
    n = p;
    p = node_parent_or_owner(n);
  } // while ...
  return n;
} // ultimate_parent

unsigned int node_attribute_index(const DOM::Attr<std::string>& attr)
{
  DOM::NamedNodeMap<std::string> attrs = attr.getOwnerElement().getAttributes();
  unsigned int p = 0;
  for(unsigned int pe = attrs.getLength(); p != pe; ++p)
    if(attrs.item(p) == attr)
      break;
  return p;
} // node_attribute_index

unsigned int node_child_position(const DOM::Node<std::string>& node)
{
  if(node.getNodeType() == DOM::Node<std::string>::ATTRIBUTE_NODE)
    return node_attribute_index(static_cast<DOM::Attr<std::string> >(node));

  unsigned int pos = 0;
  DOM::Node<std::string> n = node;
  do
  {
    n = n.getPreviousSibling();
    pos += 1000;
  } while(n != 0);
  return pos;
} // node_child_position

std::vector<unsigned int> node_position(const DOM::Node<std::string>& node)
{
  std::vector<unsigned int> pos;
  DOM::Node<std::string> n = node;
  do
  {
    pos.push_back(node_child_position(n));
    n = node_parent_or_owner(n);
  } while(n != 0);

  return pos;
} // node_position

int resolve_different_subtrees(const DOM::Node<std::string>& lhs, const DOM::Node<std::string>& rhs)
{
  // if we have something in the document, and a document fragment,
  // sort the doc ahead of the fragment
  DOM::Node<std::string> lp = ultimate_parent(lhs);
  if(lp.getNodeType() == DOM::Node<std::string>::DOCUMENT_NODE)
    return -1;
  DOM::Node<std::string> rp = ultimate_parent(rhs);
  if(rp.getNodeType() == DOM::Node<std::string>::DOCUMENT_NODE)
    return 1;

  // otherwise, sort the frags
  return (lp.unlying_impl() < lp.unlying_impl()) ? -1 : 1;
} // resolve_different_subtrees

int compareNodes(const DOM::Node<std::string>& lhs, const DOM::Node<std::string>& rhs)
{
  if(lhs == rhs)
    return 0;

  // different documents
  if(lhs.getOwnerDocument() != rhs.getOwnerDocument())
    return (lhs.getOwnerDocument().unlying_impl() < rhs.getOwnerDocument().unlying_impl()) ? -1 : 1;

  // ok, nodes belong to the same document, but do they belong to the document itself, or a document fragment, 
  // or is it just floating free? if they both belong to a document fragment, is it the same fragment?
  if(ultimate_parent(lhs) != ultimate_parent(rhs))
    return resolve_different_subtrees(lhs, rhs);

  std::vector<unsigned int> pos1 = node_position(lhs);
  std::vector<unsigned int> pos2 = node_position(rhs);

  std::vector<unsigned int>::const_reverse_iterator l = pos1.rbegin(), le = pos1.rend();
  std::vector<unsigned int>::const_reverse_iterator r = pos2.rbegin(), re = pos2.rend();

  while(l != le && r != re)
  {
    if(*l != *r)
      return *l - *r;

    ++l;
    ++r;
  } // while

  if(l != le)
    return 1;
  if(r != re)
    return -1;
  return 0;
} // compareNodes

bool nodes_less_than(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) 
{ 
  return compareNodes(n1, n2) < 0; 
} // nodes_less_than

} // namespace XPath
} // namespace Arabica
