#ifndef ARABICA_XPATHIC_XPATH_OBJECT_H
#define ARABICA_XPATHIC_XPATH_OBJECT_H

#include <string>
#include <vector>
#include <utility>
#include <DOM/Node.h>
#include <DOM/Attr.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#ifdef __BORLANDC__
#include <math>
#endif
#include <cmath>
#include <Utils/StringAdaptor.h>
#include <Utils/normalize_whitespace.hpp>
#include "xpath_axis_enumerator.hpp"

namespace Arabica
{
namespace XPath
{

enum ValueType
{
  ANY ,
  BOOL,
  NUMBER,
  STRING,
  NODE_SET
}; // ValueType

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
namespace impl
{

template<class string_type>
DOM::Node<string_type> node_parent_or_owner(const DOM::Node<string_type>& node)
{
  if(node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
    return (static_cast<DOM::Attr<string_type> >(node)).getOwnerElement();
  return node.getParentNode();
} // node_parent_or_owner

template<class string_type>
unsigned int node_attribute_index(const DOM::Attr<string_type>& attr)
{
  DOM::NamedNodeMap<string_type> attrs = attr.getOwnerElement().getAttributes();
  unsigned int p = 0;
  for(unsigned int pe = attrs.getLength(); p != pe; ++p)
    if(attrs.item(p) == attr)
      break;
  return p;
} // node_attribute_index

template<class string_type>
unsigned int node_child_position(const DOM::Node<string_type>& node)
{
  if(node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
    return node_attribute_index(static_cast<DOM::Attr<string_type> >(node));

  unsigned int pos = 0;
  DOM::Node<string_type> n = node;
  do
  {
    n = n.getPreviousSibling();
    pos += 1000;
  } while(n != 0);
  return pos;
} // node_child_position

template<class string_type>
DOM::Node<string_type> ultimate_parent(const DOM::Node<string_type>& origin)
{
  DOM::Node<string_type> n = origin;
  DOM::Node<string_type> p = node_parent_or_owner(n);
  while(p != 0)
  {
    n = p;
    p = node_parent_or_owner(n);
  } // while ...
  return n;
} // ultimate_parent

template<class string_type>
int resolve_different_subtrees(const DOM::Node<string_type>& lhs, const DOM::Node<string_type>& rhs)
{
  // if we have something in the document, and a document fragment,
  // sort the doc ahead of the fragment
  DOM::Node<string_type> lp = ultimate_parent(lhs);
  if(lp.getNodeType() == DOM::Node_base::DOCUMENT_NODE)
    return -1;
  DOM::Node<string_type> rp = ultimate_parent(rhs);
  if(rp.getNodeType() == DOM::Node_base::DOCUMENT_NODE)
    return 1;

  // otherwise, sort the frags
  return (lp.unlying_impl() < lp.unlying_impl()) ? -1 : 1;
} // resolve_different_subtrees

template<class string_type>
std::vector<unsigned int> node_position(const DOM::Node<string_type>& node)
{
  std::vector<unsigned int> pos;
  DOM::Node<string_type> n = node;
  do
  {
    pos.push_back(node_child_position(n));
    n = node_parent_or_owner(n);
  } while(n != 0);

  return pos;
} // node_position

template<class string_type>
int compareNodes(const DOM::Node<string_type>& lhs, const DOM::Node<string_type>& rhs)
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

template<class string_type>
bool nodes_less_than(const DOM::Node<string_type>& n1, const DOM::Node<string_type>& n2) 
{ 
  return compareNodes(n1, n2) < 0; 
} // nodes_less_than

} // namespace impl

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
template<class string_type>
class NodeSet  
{
public:
  typedef typename std::vector<DOM::Node<string_type> >::const_iterator const_iterator;
  typedef typename std::vector<DOM::Node<string_type> >::iterator iterator;

  NodeSet() : 
    nodes_(), 
    forward_(true), 
    sorted_(false) 
  { 
  } // NodeSet

  NodeSet(bool forward) : 
    nodes_(), 
    forward_(forward),
    sorted_(false)
  { 
  } // NodeSet

  NodeSet(const NodeSet<string_type>& rhs) : 
    nodes_(rhs.nodes_),
    forward_(rhs.forward_), 
    sorted_(rhs.sorted_)
  { 
  } // NodeSet

  NodeSet& operator=(const NodeSet<string_type>& rhs) 
  {
    nodes_ = rhs.nodes_;
    forward_ = rhs.forward_;
    sorted_ = rhs.sorted_;
    return *this;
  } // operator=

  void swap(NodeSet& rhs) 
  {
    nodes_.swap(rhs.nodes_);
    std::swap(forward_, rhs.forward_);
    std::swap(sorted_, rhs.sorted_);
  } // swap 

  const_iterator begin() const { return nodes_.begin(); }
  const_iterator end() const { return nodes_.end(); }
  iterator begin() { return nodes_.begin(); }
  iterator end() { return nodes_.end(); }
  const DOM::Node<string_type>& operator[](size_t i) const { return nodes_[i]; }
  size_t size() const { return nodes_.size(); }
  bool empty() const { return nodes_.empty(); }

  template<typename InputIterator> 
  void insert(iterator position, InputIterator first, InputIterator last)
  {
    sorted_ = false;
    nodes_.insert(position, first, last);
  } // insert
  
  void push_back(const DOM::Node<string_type>& node) 
  {
    nodes_.push_back(node);
    sorted_ = false;
  } // push_back

  bool forward() const { return sorted_ && forward_; }
  bool reverse() const { return sorted_ && !forward_; }
  void forward(bool forward) 
  { 
    if(forward_ == forward)
      return;

    forward_ = forward; 
    sorted_ = false;
  } // forward

  void to_document_order() 
  {
    sort();

    if(!forward_)
    {
      std::reverse(nodes_.begin(), nodes_.end());
      forward_ = true;
    } // if(!forward_)
  } // to_document_order

  void sort()
  {
    if(sorted_)
      return;

    if(forward_)
      std::sort(nodes_.begin(), nodes_.end(), impl::nodes_less_than<string_type>);
    else
      std::sort(nodes_.rbegin(), nodes_.rend(), impl::nodes_less_than<string_type>);

    nodes_.erase(std::unique(nodes_.begin(), nodes_.end()), nodes_.end());
    sorted_ = true;
  } // sort

  const DOM::Node<string_type>& top()  
  {
    sort();
    if(forward_)
      return (*this)[0];
    return (*this)[nodes_.size()-1];
  } // top()

private:
  std::vector<DOM::Node<string_type> > nodes_;
  bool forward_;
  bool sorted_;
}; // NodeSet

template<class string_type>
class XPathValue
{
protected:
  XPathValue() { }

public:
  virtual ~XPathValue() { }

  virtual bool asBool() const = 0;
  virtual double asNumber() const = 0;
  virtual string_type asString() const = 0;
  virtual const NodeSet<string_type>& asNodeSet() const = 0;

  virtual ValueType type() const = 0;

private:
  XPathValue(const XPathValue&);
  bool operator==(const XPathValue&);
  XPathValue& operator=(const XPathValue&);
}; // class XPathValue

template<class string_type>
class XPathValuePtr : public boost::shared_ptr<const XPathValue<string_type> > 
{ 
public:
  explicit XPathValuePtr() : boost::shared_ptr<const XPathValue<string_type> >() { }
  explicit XPathValuePtr(const XPathValue<string_type>* v) : boost::shared_ptr<const XPathValue<string_type> >(v) { }
  XPathValuePtr(const XPathValuePtr& rhs) : boost::shared_ptr<const XPathValue<string_type> >(rhs) { }
  XPathValuePtr& operator=(const XPathValuePtr& rhs) 
  {
    boost::shared_ptr<const XPathValue<string_type> >::operator=(rhs);
    return *this;
  } // operator=
}; // class XPathValuePtr



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
const double NaN = std::sqrt(-2.0);
const double Zero = 0.0;
const double Negative_Zero = -Zero;
const double Infinity = HUGE_VAL;
const double Negative_Infinity = -Infinity;

inline bool isNaN(double value) { return (value != value); } 
inline bool isInfinity(double value) { return (value == Infinity); }
inline bool isNegativeInfinity(double value) { return (value == Negative_Infinity); }
inline bool isInfinite(double value) { return isInfinity(value) || isNegativeInfinity(value); }

namespace impl
{
inline double roundNumber(double value) 
{ 
  if(!(isNaN(value) || isInfinite(value) || (std::fabs(value) == 0)))
    if((value < 0.0) && (value > -0.5))
      value = -0.0;
    else
      value = std::floor(value + 0.5);
  return value;
} // roundNumber

template<class string_type, class string_adaptor>
double stringAsNumber(const string_type& str)
{
  try {
    return boost::lexical_cast<double>(Arabica::string::normalize_whitespace<string_type, string_adaptor>(str)); 
  } // try
  catch(const boost::bad_lexical_cast&) {
    return NaN;
  } // catch
} // stringAsNumber

template<class string_type, class string_adaptor>
string_type nodeStringValue(const DOM::Node<string_type>& node)
{
  switch(node.getNodeType())
  {
  case DOM::Node_base::DOCUMENT_NODE:
  case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
  case DOM::Node_base::ELEMENT_NODE:
    {
      std::basic_ostringstream<typename string_adaptor::value_type> os;
      AxisEnumerator<string_type, string_adaptor> ae(node, DESCENDANT);
      while(*ae != 0)
      {
        if((ae->getNodeType() == DOM::Node_base::TEXT_NODE) || 
           (ae->getNodeType() == DOM::Node_base::CDATA_SECTION_NODE))
          os << ae->getNodeValue();
        ++ae;
      } // while
      return string_adaptor::construct(os.str().c_str());
    } // case

  case DOM::Node_base::ATTRIBUTE_NODE:
  case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
  case DOM::Node_base::COMMENT_NODE:
  case DOM::Node_base::TEXT_NODE:
  case DOM::Node_base::CDATA_SECTION_NODE:
  case NAMESPACE_NODE_TYPE:
    return node.getNodeValue();

  default:
    throw std::runtime_error("Don't know how to calculate string-value of " + 
      string_adaptor().asStdString(node.getNodeName()));
  } // switch
} // nodeStringValue

template<class string_type, class string_adaptor>
double nodeNumberValue(const DOM::Node<string_type>& node)
{
  return stringAsNumber<string_type, string_adaptor>(nodeStringValue<string_type, string_adaptor>(node));
} // nodeNumberValue

} // namespace impl

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

namespace impl {
template<typename RT, typename string_type, typename string_adaptor> struct value_of_node {
  RT operator()(const DOM::Node<string_type>& node) { return nodeStringValue<string_type, string_adaptor>(node); }
};
template<typename string_type, typename string_adaptor> struct value_of_node<double, string_type, string_adaptor> {
  double operator()(const DOM::Node<string_type>& node) { return nodeNumberValue<string_type, string_adaptor>(node); }
}; 

template<class Op, class string_type, class string_adaptor>
class compareNodeWith
{
  typedef typename Op::first_argument_type T;


public:
  compareNodeWith(const T& value) : value_(value) { }
  compareNodeWith(const compareNodeWith& rhs) : value_(rhs.value_) { }

  bool operator()(const DOM::Node<string_type>& node) 
  {
    value_of_node<T, string_type, string_adaptor> nv;
    return Op()(nv(node), value_);
  } // operator()

private:
  T value_;
  bool operator==(const compareNodeWith&);
  compareNodeWith& operator=(const compareNodeWith&);
}; // class compareNodeWith

template<class string_type, class string_adaptor, class predicate1, class predicate2>
bool nodeSetsCompare(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  const NodeSet<string_type>& lns = lhs->asNodeSet();
  const NodeSet<string_type>& rns = rhs->asNodeSet();

  if((lns.size() == 0) || (rns.size() == 0))
    return false;

  std::set<string_type> values;
  typename NodeSet<string_type>::const_iterator l = lns.begin();
  string_type lvalue = nodeStringValue<string_type, string_adaptor>(*l);

  predicate1 p1;
  for(typename NodeSet<string_type>::const_iterator r = rns.begin(), rend = rns.end(); r != rend; ++r)
  {
    string_type rvalue = nodeStringValue<string_type, string_adaptor>(*r);
    if(p1(lvalue, rvalue))
      return true;
    values.insert(rvalue);
  } // for ...

  ++l;
  predicate2 p2;
  for(typename NodeSet<string_type>::const_iterator lend = lns.end(); l != lend; ++l)
    if(p2(values.find(nodeStringValue<string_type, string_adaptor>(*l)),  values.end()))
      return true;

  return false;
} // nodeSetsEqual

template<class string_type, class string_adaptor>
bool nodeSetsEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  return nodeSetsCompare<string_type, string_adaptor, 
                         std::equal_to<string_type>,
                         std::not_equal_to<typename std::set<string_type>::const_iterator> >(lhs, rhs);
}

template<class string_type, class string_adaptor>
bool nodeSetsNotEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  return nodeSetsCompare<string_type, string_adaptor, 
                         std::not_equal_to<string_type>,
                         std::equal_to<typename std::set<string_type>::const_iterator> >(lhs, rhs);
}

template<class string_type, class string_adaptor>
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
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::equal_to<string_type>, string_type, string_adaptor>(rhs->asString())) != lns.end();

  case NUMBER:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::equal_to<double>, string_type, string_adaptor>(rhs->asNumber())) != lns.end();

  default:
    throw std::runtime_error("Node set == not yet implemented for type " + boost::lexical_cast<std::string>(rhs->type()));
  } // switch
} // nodeSetAndValueEqual

template<class string_type, class string_adaptor>
bool nodeSetAndValueNotEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  const NodeSet<string_type>& lns = lhs->asNodeSet();

  switch(rhs->type())
  {
  case BOOL:
    {
      bool l = !lns.empty();
      bool r = rhs->asBool();

      return l != r;
    } // case BOOL
  case STRING:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::not_equal_to<string_type>, string_type, string_adaptor>(rhs->asString())) != lns.end();

  case NUMBER:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::not_equal_to<double>, string_type, string_adaptor>(rhs->asNumber())) != lns.end();

  default:
    throw std::runtime_error("Node set == not yet implemented for type " + boost::lexical_cast<std::string>(rhs->type()));
  } // switch
} // nodeSetAndValueNotEqual

template<class string_type, class string_adaptor> 
double minValue(const NodeSet<string_type>& ns)
{
  double v = nodeNumberValue<string_type, string_adaptor>(ns[0]);
  for(typename NodeSet<string_type>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
  {
    double vt = nodeNumberValue<string_type, string_adaptor>(*i);
    if(isNaN(vt))
      continue;
    if(!(vt > v)) // looks weird, but should account for infinity
      v = vt;
  } // for ...
  return v;
} // minValue

template<class string_type, class string_adaptor> 
double maxValue(const NodeSet<string_type>& ns)
{
  double v = nodeNumberValue<string_type, string_adaptor>(ns[0]);
  for(typename NodeSet<string_type>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
  {
    double vt = nodeNumberValue<string_type, string_adaptor>(*i);
    if(isNaN(vt))
      continue;
    if(!(vt < v))
      v = vt;
  } // for ...
  return v;
} // maxValue

template<class Op, class string_type, class string_adaptor>
bool compareNodeSets(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  return Op()(minValue<string_type, string_adaptor>(lhs->asNodeSet()), maxValue<string_type, string_adaptor>(rhs->asNodeSet()));
} // compareNodeSets

template<class Op, class string_type, class string_adaptor>
bool compareNodeSetWith(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  const NodeSet<string_type>& lns = lhs->asNodeSet();
  return std::find_if(lns.begin(), 
                      lns.end(), 
                      compareNodeWith<Op, string_type, string_adaptor>(rhs->asNumber())) != lns.end();
} // compareNodeSetAndValue

template<class string_type, class string_adaptor> 
bool areEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return nodeSetsEqual<string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return nodeSetAndValueEqual<string_type, string_adaptor>(lhs, rhs);
  if(rt == NODE_SET)
    return nodeSetAndValueEqual<string_type, string_adaptor>(rhs, lhs);

  if((lt == BOOL) || (rt == BOOL))
    return lhs->asBool() == rhs->asBool();

  if((lt == NUMBER) || (rt == NUMBER))
    return lhs->asNumber() == rhs->asNumber();

  if((lt == STRING) || (rt == STRING))
    return lhs->asString() == rhs->asString();

  return false;
} // areEqual

template<class string_type, class string_adaptor> 
bool areNotEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return nodeSetsNotEqual<string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return nodeSetAndValueNotEqual<string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return nodeSetAndValueNotEqual<string_type, string_adaptor>(rhs, lhs);

  return !areEqual<string_type, string_adaptor>(lhs, rhs);
} // areNotEqual

template<class string_type, class string_adaptor> 
bool isLessThan(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less<double>, string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less<double>, string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater<double>, string_type, string_adaptor>(rhs, lhs);

  return lhs->asNumber() < rhs->asNumber();
} // isLessThan

template<class string_type, class string_adaptor> 
bool isLessThanEquals(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  ValueType lt = lhs->type();
  ValueType rt = rhs->type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less_equal<double>, string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less_equal<double>, string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater_equal<double>, string_type, string_adaptor>(rhs, lhs);

  return lhs->asNumber() <= rhs->asNumber();
} // isLessThanEquals

template<class string_type, class string_adaptor> 
bool isGreaterThan(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  return isLessThan<string_type, string_adaptor>(rhs, lhs);
} // isGreaterThan

template<class string_type, class string_adaptor> 
bool isGreaterThanEquals(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs)
{
  return isLessThanEquals<string_type, string_adaptor>(rhs, lhs);
} // isGreaterThanEquals

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
