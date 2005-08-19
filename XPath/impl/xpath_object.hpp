#ifndef ARABICA_XPATHIC_XPATH_OBJECT_H
#define ARABICA_XPATHIC_XPATH_OBJECT_H

#include <string>
#include <vector>
#include <utility>
#include <DOM/Node.h>
#include <boost/shared_ptr.hpp>
#include <cmath>

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

int compareNodes(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2);
bool nodes_less_than(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2);

template<class string_type>
class NodeSet : public std::vector<DOM::Node<string_type> >
{
private:
  typedef std::vector<DOM::Node<string_type> > baseT;
public:
  NodeSet() : 
    std::vector<DOM::Node<string_type> >(), 
    forward_(true), 
    sorted_(false) 
  { 
  } // NodeSet

  NodeSet(bool forward) : 
    std::vector<DOM::Node<string_type> >(), 
    forward_(forward),
    sorted_(true)
  { 
  } // NodeSet

  NodeSet(const NodeSet<string_type>& rhs) : 
    std::vector<DOM::Node<string_type> >(rhs),
    forward_(rhs.forward_), 
    sorted_(rhs.sorted_)
  { 
  } // NodeSet

  NodeSet& operator=(const NodeSet<string_type>& rhs) 
  {
    forward_ = rhs.forward_;
    sorted_ = rhs.sorted_;
    std::vector<DOM::Node<string_type> >::operator=(rhs);
    return *this;
  } // operator=

  void swap(NodeSet& rhs) 
  {
    std::vector<DOM::Node<string_type> >::swap(rhs);
    std::swap(forward_, rhs.forward_);
    std::swap(sorted_, rhs.sorted_);
  } // swap 

  bool forward() const { return sorted_ && forward_; }
  bool reverse() const { return sorted_ && !forward_; }
  void forward(bool forward) { forward_ = forward; sorted_ = true; }

  void to_document_order() 
  {
    if(!sorted_)
    {
      std::sort(baseT::begin(), baseT::end(), nodes_less_than);
      sorted_ = true;
      forward_ = true;
    } // if(!sorted)

    if(!forward_)
    {
      std::reverse(baseT::begin(), baseT::end());
      forward_ = true;
    } // if(!forward_)
  } // to_document_order

  DOM::Node<string_type> top() const 
  {
    if(forward_)
      return (*this)[0];
    return (*this)[baseT::size()-1];
  } // top()

private:
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
  explicit XPathValuePtr(const XPathValue<string_type>* v) : boost::shared_ptr<const XPathValue<string_type> >(v) { }
};

const double NaN = std::sqrt(-2.0);
const double Zero = 0.0;
const double Negative_Zero = -Zero;
const double Infinity = HUGE_VAL;
const double Negative_Infinity = -Infinity;

inline bool isNaN(double value) { return (value != value); } 
inline bool isInfinity(double value) { return (value == Infinity); }
inline bool isNegativeInfinity(double value) { return (value == Negative_Infinity); }
inline bool isInfinite(double value) { return isInfinity(value) || isNegativeInfinity(value); }

inline double roundNumber(double value) 
{ 
  if(!(isNaN(value) || isInfinite(value) || (std::fabs(value) == 0)))
    if((value < 0.0) && (value > -0.5))
      value = -0.0;
    else
      value = std::floor(value + 0.5);
  return value;
} // roundNumber

template<class string_type>
double stringAsNumber(const string_type& str)
{
  try {
    return boost::lexical_cast<double>(str); 
  } // try
  catch(const boost::bad_lexical_cast&) {
    return NaN;
  } // catch
} // stringAsNumber

template<class string_type>
double nodeNumberValue(const DOM::Node<string_type>& node)
{
  return stringAsNumber(nodeStringValue(node));
} // nodeNumberValue

template<class string_type>
string_type nodeStringValue(const DOM::Node<string_type>& node)
{
  switch(node.getNodeType())
  {
  case DOM::Node_base::DOCUMENT_NODE:
  case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
  case DOM::Node_base::ELEMENT_NODE:
    {
      std::ostringstream os;
      AxisEnumerator<string_type, Arabica::default_string_adaptor<string_type> > ae(node, DESCENDANT);
      while(*ae != 0)
      {
        if((ae->getNodeType() == DOM::Node_base::TEXT_NODE) || 
           (ae->getNodeType() == DOM::Node_base::CDATA_SECTION_NODE))
          os << ae->getNodeValue();
        ++ae;
      } // while
      return os.str();
    } // case

  case DOM::Node_base::ATTRIBUTE_NODE:
  case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
  case DOM::Node_base::COMMENT_NODE:
  case DOM::Node_base::TEXT_NODE:
  case DOM::Node_base::CDATA_SECTION_NODE:
    return node.getNodeValue();

  default:
    throw std::runtime_error("Don't know how to calculate string-value of " + node.getNodeName());
  } // switch
} // nodeStringValue

template<class string_type> bool areEqual(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs);
template<class string_type> bool isLessThan(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs);
template<class string_type> bool isLessThanEquals(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs);
template<class string_type> bool isGreaterThan(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs);
template<class string_type> bool isGreaterThanEquals(const XPathValuePtr<string_type>& lhs, const XPathValuePtr<string_type>& rhs);

} // namespace XPath
} // namespace Arabica

#endif
