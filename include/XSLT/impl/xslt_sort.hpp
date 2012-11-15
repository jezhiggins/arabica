#ifndef ARABICA_XSLT_SORT_HPP
#define ARABICA_XSLT_SORT_HPP

#include <algorithm>

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Sort
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  typedef Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> XPathExpressionPtr;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;

  Sort(const XPathExpressionPtr& select,
       const XPathExpressionPtr& lang, //="language-code"
       const XPathExpressionPtr& datatype, //="text|number|qname"
       const XPathExpressionPtr& order, //="ascending|descending"
       const XPathExpressionPtr& caseorder) : //="upper-first|lower-first 
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

  void set_context(const DOMNode& node, ExecutionContext<string_type, string_adaptor>& context)
  {
    context_ = &context;
    const string_type datatype = datatype_->evaluateAsString(node, context_->xpathContext());
    const string_type order = order_->evaluateAsString(node, context_->xpathContext());
    const string_type caseorder = caseorder_->evaluateAsString(node, context_->xpathContext());

    static AllowedValues<string_type> allowed_datatypes = makeAllowedValues(SC::text, SC::number);
    static AllowedValues<string_type> allowed_orders = makeAllowedValues(SC::ascending, SC::descending);
    static AllowedValues<string_type> allowed_case_orders = makeAllowedValues(SC::upper_first, SC::lower_first);
    validate(SC::data_type, allowed_datatypes, datatype);
    validate(SC::order, allowed_orders, order);
    validate(SC::case_order, allowed_case_orders, caseorder);

    if(datatype == SC::number)
      if(order == SC::ascending)
        sort_fn_ = &Sort::numberAscending;
      else
        sort_fn_ = &Sort::numberDescending;
    else
      if(order == SC::ascending)
        sort_fn_ = &Sort::stringAscending;
      else
        sort_fn_ = &Sort::stringDescending;

    if(sub_sort_)
      sub_sort_->set_context(node, context);
  } // set_context

  bool operator()(const DOMNode& n1, const DOMNode& n2) const
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
  void validate(const string_type& name, const AllowedValues<string_type>& allowed, const string_type& value)
  {
    if(allowed.is_allowed(value))
      return;

    throw SAX::SAXException(string_adaptor::asStdString(value) + 
                            " is not an allowed value for xsl:sort/@" + 
                            string_adaptor::asStdString(name));

  } // validate

  typedef bool(Sort::*sortFn)(const DOMNode& n1, const DOMNode& n2) const;
  bool numberAscending(const DOMNode& n1, const DOMNode& n2) const
  {
    return numberSort(n1, n2, nanAscending, std::less<double>());
  } // numberAscending
  bool numberDescending(const DOMNode& n1, const DOMNode& n2) const
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
  bool numberSort(const DOMNode& n1, 
                  const DOMNode& n2, 
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
  bool stringAscending(const DOMNode& n1, const DOMNode& n2) const
  {
    return stringSort(n1, n2, std::less<string_type>());
  } // stringAscending
  bool stringDescending(const DOMNode& n1, const DOMNode& n2) const
  {
    return stringSort(n1, n2, std::greater<string_type>());
  } // stringAscending
  template<class StringCompare>
  bool stringSort(const DOMNode& n1, 
                  const DOMNode& n2, 
                  StringCompare compare) const
  {
    string_type v1 = grabAsString(n1);
    string_type v2 = grabAsString(n2);

    if((v1 == v2) && (sub_sort_))
      return (*sub_sort_)(n1, n2);

    return compare(v1, v2);
  } // stringSort

  string_type grabAsString(const DOMNode& n) const
  {
    context_->setPosition(n, 1);
    return select_->evaluateAsString(n, context_->xpathContext());
  } // grabAsString
  double grabAsNumber(const DOMNode& n) const
  {
    context_->setPosition(n, 1);
    return select_->evaluateAsNumber(n, context_->xpathContext());
  } // grabAsString

  XPathExpressionPtr select_;
  XPathExpressionPtr lang_;
  XPathExpressionPtr datatype_;
  XPathExpressionPtr order_;
  XPathExpressionPtr caseorder_;
  Sort* sub_sort_;
  ExecutionContext<string_type, string_adaptor>* context_;
  sortFn sort_fn_;

  Sort& operator=(const Sort&);
  bool operator==(const Sort&) const;
}; // class Sort

template<class string_type, class string_adaptor>
class Sortable
{
public:
  typedef Sort<string_type, string_adaptor> SortT;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;

protected:
  Sortable() :
    sort_(0)
  {
  } // Sortable

  ~Sortable()
  {
    delete sort_;
  } // ~Sortable

  void sort(const DOMNode& node, 
            NodeSet& nodes, 
            ExecutionContext<string_type, string_adaptor>& context) const
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
  void add_sort(SortT* sort)
  {
    if(!sort_)
      sort_ = sort;
    else
      sort_->add_sub_sort(sort);
  } // add_sort

private:
  SortT* sort_;

  struct SortP
  {
    SortP(SortT& sort) : sort_(sort) { }
    bool operator()(const DOMNode& n1, const DOMNode& n2)
    {
      return sort_(n1, n2);
    } // operator()

  private:
    SortT& sort_;
  }; // struct SortP
}; // class Sortable


} // namespace XSLT
} // namespace Arabica

#endif

