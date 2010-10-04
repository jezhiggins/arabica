#ifndef ARABICA_XPATHIC_XPATH_OBJECT_H
#define ARABICA_XPATHIC_XPATH_OBJECT_H

#include <string>
#include <vector>
#include <utility>
#include <DOM/Node.hpp>
#include <DOM/Attr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#ifdef __BORLANDC__
#include <math>
#endif
#include <cmath>
#include <Arabica/StringAdaptor.hpp>
#include <text/normalize_whitespace.hpp>
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

template<class string_type, class string_adaptor>
DOM::Node<string_type, string_adaptor> node_parent_or_owner(const DOM::Node<string_type, string_adaptor>& node)
{
  if(node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
    return (static_cast<DOM::Attr<string_type, string_adaptor> >(node)).getOwnerElement();
  return node.getParentNode();
} // node_parent_or_owner

template<class string_type, class string_adaptor>
unsigned int node_attribute_index(const DOM::Attr<string_type, string_adaptor>& attr)
{
  DOM::NamedNodeMap<string_type, string_adaptor> attrs = attr.getOwnerElement().getAttributes();
  unsigned int p = 0;
  for(unsigned int pe = attrs.getLength(); p != pe; ++p)
    if(attrs.item(p) == attr)
      break;
  return p+1;
} // node_attribute_index

template<class string_type, class string_adaptor>
unsigned int node_child_position(const DOM::Node<string_type, string_adaptor>& node)
{
  switch(node.getNodeType())
  {
    case NAMESPACE_NODE_TYPE:
      return 0;
    case DOM::Node_base::ATTRIBUTE_NODE:
      return node_attribute_index(static_cast<DOM::Attr<string_type, string_adaptor> >(node));
    default:
    {
      unsigned int pos = 0;
      DOM::Node<string_type, string_adaptor> n = node;
      do
      {
        n = n.getPreviousSibling();
        pos += 1000;
      } while(n != 0);
      return pos;
    } // default
  } // switch ...
} // node_child_position

template<class string_type, class string_adaptor>
DOM::Node<string_type, string_adaptor> ultimate_parent(const DOM::Node<string_type, string_adaptor>& origin)
{
  DOM::Node<string_type, string_adaptor> n = origin;
  DOM::Node<string_type, string_adaptor> p = node_parent_or_owner(n);
  while(p != 0)
  {
    n = p;
    p = node_parent_or_owner(n);
  } // while ...
  return n;
} // ultimate_parent

template<class string_type, class string_adaptor>
int resolve_different_subtrees(const DOM::Node<string_type, string_adaptor>& lhs, 
                               const DOM::Node<string_type, string_adaptor>& rhs)
{
  // if we have something in the document, and a document fragment,
  // sort the doc ahead of the fragment
  DOM::Node<string_type,string_adaptor> lp = ultimate_parent(lhs);
  if(lp.getNodeType() == DOM::Node_base::DOCUMENT_NODE)
    return -1;
  DOM::Node<string_type, string_adaptor> rp = ultimate_parent(rhs);
  if(rp.getNodeType() == DOM::Node_base::DOCUMENT_NODE)
    return 1;

  // otherwise, sort the frags
  return (lp.underlying_impl() < lp.underlying_impl()) ? -1 : 1;
} // resolve_different_subtrees

template<class string_type, class string_adaptor>
std::vector<unsigned int> node_position(const DOM::Node<string_type, string_adaptor>& node)
{
  std::vector<unsigned int> pos;
  DOM::Node<string_type, string_adaptor> n = node;
  do
  {
    pos.push_back(node_child_position(n));
    n = node_parent_or_owner(n);
  } while(n != 0);

  return pos;
} // node_position

template<class string_type, class string_adaptor>
DOM::Node<string_type, string_adaptor> get_owner_document(const DOM::Node<string_type, string_adaptor>& node)
{
  if(node.getNodeType() == DOM::Node_base::DOCUMENT_NODE)
    return node;
  return node.getOwnerDocument();
} // get_owner_document

template<class string_type, class string_adaptor>
int compareNodes(const DOM::Node<string_type, string_adaptor>& lhs, 
                 const DOM::Node<string_type, string_adaptor>& rhs)
{
  if(lhs == rhs)
    return 0;

  // different documents
  if(get_owner_document(lhs) != get_owner_document(rhs))
    return (get_owner_document(lhs).underlying_impl() < get_owner_document(rhs).underlying_impl()) ? 1 : -1;

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

template<class string_type, class string_adaptor>
bool nodes_less_than(const DOM::Node<string_type, string_adaptor>& n1, 
                     const DOM::Node<string_type, string_adaptor>& n2) 
{ 
  return compareNodes(n1, n2) < 0; 
} // nodes_less_than

} // namespace impl

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NodeSet  
{
public:
  typedef typename std::vector<DOM::Node<string_type, string_adaptor> >::const_iterator const_iterator;
  typedef typename std::vector<DOM::Node<string_type, string_adaptor> >::iterator iterator;
  typedef typename std::vector<DOM::Node<string_type, string_adaptor> >::value_type value_type;

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

  NodeSet(const NodeSet<string_type, string_adaptor>& rhs) : 
    nodes_(rhs.nodes_),
    forward_(rhs.forward_), 
    sorted_(rhs.sorted_)
  { 
  } // NodeSet

  NodeSet& operator=(const NodeSet<string_type, string_adaptor>& rhs) 
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
  const DOM::Node<string_type, string_adaptor>& operator[](size_t i) const { return nodes_[i]; }
  size_t size() const { return nodes_.size(); }
  bool empty() const { return nodes_.empty(); }

  template<typename InputIterator> 
  void insert(iterator position, InputIterator first, InputIterator last)
  {
    sorted_ = false;
    nodes_.insert(position, first, last);
  } // insert
  
  void push_back(const DOM::Node<string_type, string_adaptor>& node) 
  {
    nodes_.push_back(node);
    sorted_ = false;
  } // push_back

  void push_back(const NodeSet<string_type, string_adaptor>& nodeSet)
  {
    insert(end(), nodeSet.begin(), nodeSet.end());
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
      std::sort(nodes_.begin(), nodes_.end(), impl::nodes_less_than<string_type, string_adaptor>);
    else
      std::sort(nodes_.rbegin(), nodes_.rend(), impl::nodes_less_than<string_type, string_adaptor>);

    nodes_.erase(std::unique(nodes_.begin(), nodes_.end()), nodes_.end());
    sorted_ = true;
  } // sort

  const DOM::Node<string_type, string_adaptor>& top()  
  {
    sort();
    if(forward_)
      return (*this)[0];
    return (*this)[nodes_.size()-1];
  } // top()

private:
  std::vector<DOM::Node<string_type, string_adaptor> > nodes_;
  bool forward_;
  bool sorted_;
}; // NodeSet

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathValue_impl
{
protected:
  XPathValue_impl() { }

public:
  virtual ~XPathValue_impl() { }

  virtual bool asBool() const = 0;
  virtual double asNumber() const = 0;
  virtual string_type asString() const = 0;
  virtual const NodeSet<string_type, string_adaptor>& asNodeSet() const = 0;

  virtual ValueType type() const = 0;

private:
  XPathValue_impl(const XPathValue_impl&);
  bool operator==(const XPathValue_impl&) const;
  XPathValue_impl& operator=(const XPathValue_impl&);
}; // class XPathValue_impl

template<class string_type, class string_adaptor> class XPathValuePtr;

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathValue
{ 
public:
  explicit XPathValue() : ptr_() { }
  explicit XPathValue(const XPathValue_impl<string_type, string_adaptor>* v) : ptr_(v) { }
  XPathValue(const XPathValue& rhs) : ptr_(rhs.ptr_) { }
  XPathValue& operator=(const XPathValue& rhs) 
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=

  bool asBool() const { return ptr_->asBool(); }
  double asNumber() const { return ptr_->asNumber(); }
  string_type asString() const { return ptr_->asString(); }
  const NodeSet<string_type, string_adaptor>& asNodeSet() const { return ptr_->asNodeSet(); }

  ValueType type() const { return ptr_->type(); }

  operator bool() const { return ptr_.get() != 0; }
  bool operator==(int dummy) const { return (dummy == 0) && (ptr_.get() == 0); } 
  bool operator!=(int dummy) const { return !(operator==(dummy)); }

private:
  bool operator==(const XPathValue&) const;

  typedef boost::shared_ptr<const XPathValue_impl<string_type, string_adaptor> > ValuePtr;
  ValuePtr ptr_;

  explicit XPathValue(ValuePtr ptr) : ptr_(ptr) { }

  friend class XPathValuePtr<string_type, string_adaptor>;
}; // class XPathValue

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathValuePtr
{ 
public:
  explicit XPathValuePtr() : ptr_() { }
  explicit XPathValuePtr(const XPathValue_impl<string_type, string_adaptor>* v) : ptr_(v) { }
  XPathValuePtr(const XPathValue<string_type, string_adaptor>& rhs) : ptr_(rhs.ptr_) { }
  XPathValuePtr(const XPathValuePtr& rhs) : ptr_(rhs.ptr_) { }
  XPathValuePtr& operator=(const XPathValue<string_type, string_adaptor>& rhs) 
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=
  XPathValuePtr& operator=(const XPathValuePtr& rhs) 
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=

  const XPathValue_impl<string_type, string_adaptor>* operator->() const { return ptr_.get(); }

  operator bool() const { return (ptr_.get() != 0); }
  operator XPathValue<string_type, string_adaptor>() const { return XPathValue<string_type, string_adaptor>(ptr_); }

private:
  bool operator==(const XPathValuePtr&) const;

  typedef boost::shared_ptr<const XPathValue_impl<string_type, string_adaptor> > ValuePtr;
  ValuePtr ptr_;
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
  {
    if((value < 0.0) && (value > -0.5))
      value = -0.0;
    else
      value = std::floor(value + 0.5);
  } // if ...
  return value;
} // roundNumber

template<class string_type, class string_adaptor>
double stringAsNumber(const string_type& str)
{
  try {
    static string_type PLUS = string_adaptor::construct_from_utf8("+");

    string_type n_str = Arabica::text::normalize_whitespace<string_type, string_adaptor>(str);
    // '+1.5' is not a number according to XPath spec, counter intuitive as that is
    if(string_adaptor::find(n_str, PLUS) == 0)
      return NaN;
    
    return boost::lexical_cast<double>(n_str);
  } // try
  catch(const boost::bad_lexical_cast&) {
    return NaN;
  } // catch
} // stringAsNumber

template<class string_type, class string_adaptor>
bool nodeIsText(const DOM::Node<string_type, string_adaptor>& node)
{
  return (node.getNodeType() == DOM::Node_base::TEXT_NODE) ||
         (node.getNodeType() == DOM::Node_base::CDATA_SECTION_NODE);
} // nodeIsText

template<class string_type, class string_adaptor>
string_type nodeStringValue(const DOM::Node<string_type, string_adaptor>& node)
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
        if(nodeIsText<string_type, string_adaptor>(*ae))
          os << nodeStringValue(*ae);
        ++ae;
      } // while
      return string_adaptor::construct(os.str().c_str());
    } // case

  case DOM::Node_base::ATTRIBUTE_NODE:
  case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
  case DOM::Node_base::COMMENT_NODE:
  case NAMESPACE_NODE_TYPE:
    return node.getNodeValue();

  case DOM::Node_base::TEXT_NODE:
  case DOM::Node_base::CDATA_SECTION_NODE:
    {
      DOM::Node<string_type, string_adaptor> next = node.getNextSibling();
      if((next == 0) ||
	 !nodeIsText<string_type, string_adaptor>(next))
	return node.getNodeValue();

      std::basic_ostringstream<typename string_adaptor::value_type> os;
      os << node.getNodeValue() 
	 << nodeStringValue<string_type, string_adaptor>(next);
      return string_adaptor::construct(os.str().c_str());
    } // case

  default:
    throw std::runtime_error("Don't know how to calculate string-value of " + 
      string_adaptor().asStdString(node.getNodeName()));
  } // switch
} // nodeStringValue

template<class string_type, class string_adaptor>
double nodeNumberValue(const DOM::Node<string_type, string_adaptor>& node)
{
  return stringAsNumber<string_type, string_adaptor>(nodeStringValue<string_type, string_adaptor>(node));
} // nodeNumberValue

} // namespace impl

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

namespace impl {
template<typename RT, typename string_type, typename string_adaptor> struct value_of_node {
  RT operator()(const DOM::Node<string_type, string_adaptor>& node) { return nodeStringValue<string_type, string_adaptor>(node); }
};
template<typename string_type, typename string_adaptor> struct value_of_node<double, string_type, string_adaptor> {
  double operator()(const DOM::Node<string_type, string_adaptor>& node) { return nodeNumberValue<string_type, string_adaptor>(node); }
}; 

template<class Op, class string_type, class string_adaptor>
class compareNodeWith
{
  typedef typename Op::first_argument_type T;


public:
  compareNodeWith(const T& value) : value_(value) { }
  compareNodeWith(const compareNodeWith& rhs) : value_(rhs.value_) { }

  bool operator()(const DOM::Node<string_type, string_adaptor>& node) 
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
bool nodeSetsCompare(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  const NodeSet<string_type, string_adaptor>& lns = lhs.asNodeSet();
  const NodeSet<string_type, string_adaptor>& rns = rhs.asNodeSet();

  if((lns.size() == 0) || (rns.size() == 0))
    return false;

  std::set<string_type> values;
  typename NodeSet<string_type, string_adaptor>::const_iterator l = lns.begin();
  string_type lvalue = nodeStringValue<string_type, string_adaptor>(*l);

  predicate1 p1;
  for(typename NodeSet<string_type, string_adaptor>::const_iterator r = rns.begin(), rend = rns.end(); r != rend; ++r)
  {
    string_type rvalue = nodeStringValue<string_type, string_adaptor>(*r);
    if(p1(lvalue, rvalue))
      return true;
    values.insert(rvalue);
  } // for ...

  ++l;
  predicate2 p2;
  for(typename NodeSet<string_type, string_adaptor>::const_iterator lend = lns.end(); l != lend; ++l)
    if(p2(values.find(nodeStringValue<string_type, string_adaptor>(*l)),  values.end()))
      return true;

  return false;
} // nodeSetsEqual

template<class string_type, class string_adaptor>
bool nodeSetsEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  return nodeSetsCompare<string_type, string_adaptor, 
                         std::equal_to<string_type>,
                         std::not_equal_to<typename std::set<string_type>::const_iterator> >(lhs, rhs);
}

template<class string_type, class string_adaptor>
bool nodeSetsNotEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  return nodeSetsCompare<string_type, string_adaptor, 
                         std::not_equal_to<string_type>,
                         std::equal_to<typename std::set<string_type>::const_iterator> >(lhs, rhs);
}

template<class string_type, class string_adaptor>
bool nodeSetAndValueEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  const NodeSet<string_type, string_adaptor>& lns = lhs.asNodeSet();

  switch(rhs.type())
  {
  case BOOL:
    {
      bool l = !lns.empty();
      bool r = rhs.asBool();

      return l == r;
    } // case BOOL
  case STRING:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::equal_to<string_type>, string_type, string_adaptor>(rhs.asString())) != lns.end();

  case NUMBER:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::equal_to<double>, string_type, string_adaptor>(rhs.asNumber())) != lns.end();

  default:
    throw std::runtime_error("Node set == not yet implemented for type " + boost::lexical_cast<std::string>(rhs.type()));
  } // switch
} // nodeSetAndValueEqual

template<class string_type, class string_adaptor>
bool nodeSetAndValueNotEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  const NodeSet<string_type, string_adaptor>& lns = lhs.asNodeSet();

  switch(rhs.type())
  {
  case BOOL:
    {
      bool l = !lns.empty();
      bool r = rhs.asBool();

      return l != r;
    } // case BOOL
  case STRING:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::not_equal_to<string_type>, string_type, string_adaptor>(rhs.asString())) != lns.end();

  case NUMBER:
    return std::find_if(lns.begin(), 
                        lns.end(), 
                        compareNodeWith<std::not_equal_to<double>, string_type, string_adaptor>(rhs.asNumber())) != lns.end();

  default:
    throw std::runtime_error("Node set == not yet implemented for type " + boost::lexical_cast<std::string>(rhs.type()));
  } // switch
} // nodeSetAndValueNotEqual

template<class string_type, class string_adaptor> 
double minValue(const NodeSet<string_type, string_adaptor>& ns)
{
  double v = nodeNumberValue<string_type, string_adaptor>(ns[0]);
  for(typename NodeSet<string_type, string_adaptor>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
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
double maxValue(const NodeSet<string_type, string_adaptor>& ns)
{
  double v = nodeNumberValue<string_type, string_adaptor>(ns[0]);
  for(typename NodeSet<string_type, string_adaptor>::const_iterator i = ns.begin(), ie = ns.end(); i != ie; ++i)
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
bool compareNodeSets(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  return Op()(minValue<string_type, string_adaptor>(lhs.asNodeSet()), maxValue<string_type, string_adaptor>(rhs.asNodeSet()));
} // compareNodeSets

template<class Op, class string_type, class string_adaptor>
bool compareNodeSetWith(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  const NodeSet<string_type, string_adaptor>& lns = lhs.asNodeSet();
  return std::find_if(lns.begin(), 
                      lns.end(), 
                      compareNodeWith<Op, string_type, string_adaptor>(rhs.asNumber())) != lns.end();
} // compareNodeSetAndValue

template<class string_type, class string_adaptor> 
bool areEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  ValueType lt = lhs.type();
  ValueType rt = rhs.type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return nodeSetsEqual<string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return nodeSetAndValueEqual<string_type, string_adaptor>(lhs, rhs);
  if(rt == NODE_SET)
    return nodeSetAndValueEqual<string_type, string_adaptor>(rhs, lhs);

  if((lt == BOOL) || (rt == BOOL))
    return lhs.asBool() == rhs.asBool();

  if((lt == NUMBER) || (rt == NUMBER))
    return lhs.asNumber() == rhs.asNumber();

  if((lt == STRING) || (rt == STRING))
    return lhs.asString() == rhs.asString();

  return false;
} // areEqual

template<class string_type, class string_adaptor> 
bool areNotEqual(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  ValueType lt = lhs.type();
  ValueType rt = rhs.type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return nodeSetsNotEqual<string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return nodeSetAndValueNotEqual<string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return nodeSetAndValueNotEqual<string_type, string_adaptor>(rhs, lhs);

  return !areEqual<string_type, string_adaptor>(lhs, rhs);
} // areNotEqual

template<class string_type, class string_adaptor> 
bool isLessThan(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  ValueType lt = lhs.type();
  ValueType rt = rhs.type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less<double>, string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less<double>, string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater<double>, string_type, string_adaptor>(rhs, lhs);

  return lhs.asNumber() < rhs.asNumber();
} // isLessThan

template<class string_type, class string_adaptor> 
bool isLessThanEquals(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  ValueType lt = lhs.type();
  ValueType rt = rhs.type();

  if((lt == NODE_SET) && (rt == NODE_SET))
    return compareNodeSets<std::less_equal<double>, string_type, string_adaptor>(lhs, rhs);

  if(lt == NODE_SET)
    return compareNodeSetWith<std::less_equal<double>, string_type, string_adaptor>(lhs, rhs);

  if(rt == NODE_SET)
    return compareNodeSetWith<std::greater_equal<double>, string_type, string_adaptor>(rhs, lhs);

  return lhs.asNumber() <= rhs.asNumber();
} // isLessThanEquals

template<class string_type, class string_adaptor> 
bool isGreaterThan(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  return isLessThan<string_type, string_adaptor>(rhs, lhs);
} // isGreaterThan

template<class string_type, class string_adaptor> 
bool isGreaterThanEquals(const XPathValue<string_type, string_adaptor>& lhs, const XPathValue<string_type, string_adaptor>& rhs)
{
  return isLessThanEquals<string_type, string_adaptor>(rhs, lhs);
} // isGreaterThanEquals

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
