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

class XPathExpression;
typedef boost::shared_ptr<XPathExpression> XPathExpressionPtr;
class XPathValue;
typedef boost::shared_ptr<const XPathValue> XPathValuePtr;

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

class NodeSet : public std::vector<DOM::Node<std::string> >
{
public:
  NodeSet() : 
    std::vector<DOM::Node<std::string> >(), 
    forward_(true), 
    sorted_(false) 
  { 
  } // NodeSet

  NodeSet(bool forward) : 
    std::vector<DOM::Node<std::string> >(), 
    forward_(forward),
    sorted_(true)
  { 
  } // NodeSet

  NodeSet(const NodeSet& rhs) : 
    std::vector<DOM::Node<std::string> >(rhs),
    forward_(rhs.forward_), 
    sorted_(rhs.sorted_)
  { 
  } // NodeSet

  NodeSet& operator=(const NodeSet& rhs) 
  {
    forward_ = rhs.forward_;
    sorted_ = rhs.sorted_;
    std::vector<DOM::Node<std::string> >::operator=(rhs);
    return *this;
  } // operator=

  void swap(NodeSet& rhs) 
  {
    std::vector<DOM::Node<std::string> >::swap(rhs);
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
      std::sort(begin(), end(), nodes_less_than);
      sorted_ = true;
      forward_ = true;
    } // if(!sorted)

    if(!forward_)
    {
      std::reverse(begin(), end());
      forward_ = true;
    } // if(!forward_)
  } // to_document_order

  DOM::Node<std::string> top() const 
  {
    if(forward_)
      return (*this)[0];
    return (*this)[size()-1];
  } // top()

private:
  bool forward_;
  bool sorted_;
}; // NodeSet

class XPathValue
{
protected:
  XPathValue() { }

public:
  virtual ~XPathValue() { }

  virtual bool asBool() const = 0;
  virtual double asNumber() const = 0;
  virtual std::string asString() const = 0;
  virtual const NodeSet& asNodeSet() const = 0;

  virtual ValueType type() const = 0;

private:
  XPathValue(const XPathValue&);
  bool operator==(const XPathValue&);
  XPathValue& operator=(const XPathValue&);
}; // class XPathValue

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

double stringAsNumber(const std::string& str);
double nodeNumberValue(const DOM::Node<std::string>& node);
std::string nodeStringValue(const DOM::Node<std::string>& node);

bool areEqual(const XPathValuePtr& lhs, const XPathValuePtr& rhs);
bool isLessThan(const XPathValuePtr& lhs, const XPathValuePtr& rhs);
bool isLessThanEquals(const XPathValuePtr& lhs, const XPathValuePtr& rhs);
bool isGreaterThan(const XPathValuePtr& lhs, const XPathValuePtr& rhs);
bool isGreaterThanEquals(const XPathValuePtr& lhs, const XPathValuePtr& rhs);

} // namespace XPath
} // namespace Arabica

#endif
