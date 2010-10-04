#ifndef ARABICA_XSLT_SORT_HPP
#define ARABICA_XSLT_SORT_HPP

#include <algorithm>

namespace Arabica
{
namespace XSLT
{

class Sort
{
public:
  Sort(const Arabica::XPath::XPathExpressionPtr<std::string>& select,
       const Arabica::XPath::XPathExpressionPtr<std::string>& lang, //="language-code"
       const Arabica::XPath::XPathExpressionPtr<std::string>& datatype, //="text|number|qname"
       const Arabica::XPath::XPathExpressionPtr<std::string>& order, //="ascending|descending"
       const Arabica::XPath::XPathExpressionPtr<std::string>& caseorder) : //="upper-first|lower-first 
    select_(select),
    lang_(lang),
    datatype_(datatype),
    order_(order),
    caseorder_(caseorder),
    sub_sort_(0)
  {
  } // Sort

  ~Sort() 
  { 
    delete sub_sort_;
  } // ~Sort

  void set_context(const DOM::Node<std::string>& node, ExecutionContext& context)
  {
    context_ = &context;
    const std::string datatype = datatype_->evaluateAsString(node, context_->xpathContext());
    const std::string order = order_->evaluateAsString(node, context_->xpathContext());
    const std::string caseorder = caseorder_->evaluateAsString(node, context_->xpathContext());

    static const char* allowed_datatypes[] = { "text", "number", 0 };
    static const char* allowed_orders[] = { "ascending", "descending", 0 };
    static const char* allowed_case_orders[] = { "upper-first", "lower-first", 0 };
    validateValues("xsl:sort", "data-type", datatype, allowed_datatypes);
    validateValues("xsl:sort", "order", order, allowed_orders);
    validateValues("xsl:sort", "case-order", caseorder, allowed_case_orders);

    if(datatype == "number")
      if(order == "ascending")
        sort_fn_ = &Sort::numberAscending;
      else
        sort_fn_ = &Sort::numberDescending;
    else
      if(order == "ascending")
        sort_fn_ = &Sort::stringAscending;
      else
        sort_fn_ = &Sort::stringDescending;

    if(sub_sort_)
      sub_sort_->set_context(node, context);
  } // set_context

  bool operator()(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const
  {
    return (this->*sort_fn_)(n1, n2);
  } // operator()

  void add_sub_sort(Sort* sort)
  {
    if(!sub_sort_)
      sub_sort_ = sort;
    else 
      sub_sort_->add_sub_sort(sort);
  } // add_sub_sort

private:
  typedef bool(Sort::*sortFn)(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const;
  bool numberAscending(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const
  {
    return numberSort(n1, n2, nanAscending, std::less<double>());
  } // numberAscending
  bool numberDescending(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const
  {
    return numberSort(n1, n2, nanDescending, std::greater<double>());
  } // numberDescending
  static bool nanAscending(bool, bool nan2) 
  {
    return !nan2;
  } // nanAscending
  static bool nanDescending(bool nan1, bool)
  {
    return !nan1;
  } // nanDescending
  template<class NanCompare, class NumberCompare>
  bool numberSort(const DOM::Node<std::string>& n1, 
                  const DOM::Node<std::string>& n2, 
                  NanCompare nanCompare, 
                  NumberCompare compare) const
  {
    double v1 = grabAsNumber(n1);
    double v2 = grabAsNumber(n2);

    bool nan1 = Arabica::XPath::isNaN(v1);
    bool nan2 = Arabica::XPath::isNaN(v2);

    if(((nan1 && nan2) || (v1 == v2)) && (sub_sort_))
      return (*sub_sort_)(n1, n2);

    if(nan1 || nan2)
      return nanCompare(nan1, nan2);

    return compare(v1, v2);
  } // numberSort
  bool stringAscending(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const
  {
    return stringSort(n1, n2, std::less<std::string>());
  } // stringAscending
  bool stringDescending(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2) const
  {
    return stringSort(n1, n2, std::greater<std::string>());
  } // stringAscending
  template<class StringCompare>
  bool stringSort(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2, StringCompare compare) const
  {
    std::string v1 = grabAsString(n1);
    std::string v2 = grabAsString(n2);

    if((v1 == v2) && (sub_sort_))
      return (*sub_sort_)(n1, n2);

    return compare(v1, v2);
  } // stringSort

  std::string grabAsString(const DOM::Node<std::string>& n) const
  {
    context_->setPosition(n, 1);
    return select_->evaluateAsString(n, context_->xpathContext());
  } // grabAsString
  double grabAsNumber(const DOM::Node<std::string>& n) const
  {
    context_->setPosition(n, 1);
    return select_->evaluateAsNumber(n, context_->xpathContext());
  } // grabAsString

  Arabica::XPath::XPathExpressionPtr<std::string> select_;
  Arabica::XPath::XPathExpressionPtr<std::string> lang_;
  Arabica::XPath::XPathExpressionPtr<std::string> datatype_;
  Arabica::XPath::XPathExpressionPtr<std::string> order_;
  Arabica::XPath::XPathExpressionPtr<std::string> caseorder_;
  Sort* sub_sort_;
  ExecutionContext* context_;
  sortFn sort_fn_;

  Sort& operator=(const Sort&);
  bool operator==(const Sort&) const;
}; // class Sort

class Sortable
{
protected:
  Sortable() :
    sort_(0)
  {
  } // Sortable

  ~Sortable()
  {
    delete sort_;
  } // ~Sortable

  void sort(const DOM::Node<std::string>& node, Arabica::XPath::NodeSet<std::string>& nodes, ExecutionContext& context) const
  {
    if(!sort_)
    {
      if(!nodes.forward())
        nodes.to_document_order();
      return;
    }

    sort_->set_context(node, context);
    std::stable_sort(nodes.begin(), nodes.end(), SortP(*sort_));
  } // sort

  bool has_sort() const { return sort_ != 0; }

public:
  void add_sort(Sort* sort)
  {
    if(!sort_)
      sort_ = sort;
    else
      sort_->add_sub_sort(sort);
  } // add_sort

private:
  Sort* sort_;

  struct SortP
  {
    SortP(Sort& sort) : sort_(sort) { }
    bool operator()(const DOM::Node<std::string>& n1, const DOM::Node<std::string>& n2)
    {
      return sort_(n1, n2);
    } // operator()

  private:
    Sort& sort_;
  }; // struct SortP
}; // class Sortable


} // namespace XSLT
} // namespace Arabica

#endif

