#ifndef ARABICA_XPATHIC_XPATH_STEP_H
#define ARABICA_XPATHIC_XPATH_STEP_H

#include <DOM/Document.hpp>
#include <algorithm>
#include "xpath_object.hpp"
#include "xpath_value.hpp"
#include "xpath_axis_enumerator.hpp"
#include "xpath_node_test.hpp"
#include "xpath_ast.hpp"
#include "xpath_ast_ids.hpp"
#include "xpath_namespace_context.hpp"
#include "xpath_compile_context.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class MatchExpr;

namespace impl
{

template<class string_type, class string_adaptor>
class StepExpression : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  StepExpression() { }
  StepExpression(XPathExpression_impl<string_type, string_adaptor>* pred) { predicates_.push_back(pred); }
  StepExpression(const std::vector<XPathExpression_impl<string_type, string_adaptor> *>& predicates) : predicates_(predicates) { }

  virtual ~StepExpression()
  { 
    for(typename std::vector<XPathExpression_impl<string_type, string_adaptor>*>::iterator p = predicates_.begin(), e = predicates_.end(); p != e; ++p)
      delete *p;
  } // ~StepExpression

  virtual ValueType type() const { return NODE_SET; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;
  virtual XPathValue<string_type, string_adaptor> evaluate(NodeSet<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;

  bool has_predicates() const { return !predicates_.empty(); }

protected:
  NodeSet<string_type, string_adaptor> applyPredicates(NodeSet<string_type, string_adaptor>& nodes, const ExecutionContext<string_type, string_adaptor>& parentContext) const
  {
    for(typename std::vector<XPathExpression_impl<string_type, string_adaptor>*>::const_iterator p = predicates_.begin(), e = predicates_.end();
        (p != e) && (!nodes.empty()); ++p)
      nodes = applyPredicate(nodes, *p, parentContext);
    return nodes;
  } // applyPredicates

private:
  NodeSet<string_type, string_adaptor> applyPredicate(NodeSet<string_type, string_adaptor>& nodes, 
                                      XPathExpression_impl<string_type, string_adaptor>* predicate, 
                                      const ExecutionContext<string_type, string_adaptor>& parentContext) const
  {
    ExecutionContext<string_type, string_adaptor> executionContext(nodes.size(), parentContext);
    NodeSet<string_type, string_adaptor> results(nodes.forward());
    unsigned int position = 1;
    for(typename NodeSet<string_type, string_adaptor>::iterator i = nodes.begin(); i != nodes.end(); ++i, ++position)
    {
      executionContext.setPosition(position);
      XPathValue<string_type, string_adaptor> v = predicate->evaluate(*i, executionContext);

      if((v.type() == NUMBER) && (position != v.asNumber()))
        continue;
      if(v.asBool() == false)
        continue;

      results.push_back(*i);
    } // for ...
    return results;
  } // applyPredicate
  
  std::vector<XPathExpression_impl<string_type, string_adaptor>*> predicates_;

  friend class MatchExpr<string_type, string_adaptor>;
}; // StepExpression

template<class string_type, class string_adaptor>
class TestStepExpression : public StepExpression<string_type, string_adaptor>
{
  typedef StepExpression<string_type, string_adaptor> baseT;
public:
  TestStepExpression(Axis axis, NodeTest<string_type, string_adaptor>* test) :
      StepExpression<string_type, string_adaptor>(),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  TestStepExpression(Axis axis, NodeTest<string_type, string_adaptor>* test,
                     XPathExpression_impl<string_type, string_adaptor>* pred) :
      StepExpression<string_type, string_adaptor>(pred),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  TestStepExpression(Axis axis, NodeTest<string_type, string_adaptor>* test, 
                     const std::vector<XPathExpression_impl<string_type, string_adaptor>*>& predicates) :
      StepExpression<string_type, string_adaptor>(predicates),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  virtual ~TestStepExpression()
  {
    delete test_;
  } // StepExpression

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    NodeSet<string_type, string_adaptor> nodes;
    enumerateOver(context, nodes, executionContext);
    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(nodes));
  } // evaluate

  virtual XPathValue<string_type, string_adaptor> evaluate(NodeSet<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    NodeSet<string_type, string_adaptor> nodes;
    for(typename NodeSet<string_type, string_adaptor>::iterator n = context.begin(); n != context.end(); ++n)
      enumerateOver(*n, nodes, executionContext);
    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(nodes));
  } // evaluate

private:
  void enumerateOver(const DOM::Node<string_type, string_adaptor>& context, 
                     NodeSet<string_type, string_adaptor>& results, 
                     const ExecutionContext<string_type, string_adaptor>& parentContext) const
  {
    AxisEnumerator<string_type, string_adaptor> enumerator(context, axis_);
    results.forward(enumerator.forward());
    NodeSet<string_type, string_adaptor> intermediate(enumerator.forward());
    NodeSet<string_type, string_adaptor>& d = (!baseT::has_predicates()) ? results : intermediate;
    while(*enumerator != 0)
    {
      // if test
      DOM::Node<string_type, string_adaptor> node = *enumerator;
      if((*test_)(node))
        d.push_back(node);
      ++enumerator;
    } // while ...
    
    if(!baseT::has_predicates())
      return;

    intermediate = baseT::applyPredicates(intermediate, parentContext);

    results.insert(results.end(), intermediate.begin(), intermediate.end());
  } // enumerateOver

  Axis axis_;
  NodeTest<string_type, string_adaptor>* test_;

  friend class MatchExpr<string_type, string_adaptor>;
}; // class TestStepExpression

template<class string_type, class string_adaptor>
class ExprStepExpression : public StepExpression<string_type, string_adaptor>
{
  typedef StepExpression<string_type, string_adaptor> baseT;
public:
  ExprStepExpression(XPathExpression_impl<string_type, string_adaptor>* expr, 
                     const std::vector<XPathExpression_impl<string_type, string_adaptor>*>& predicates) :
      StepExpression<string_type, string_adaptor>(predicates),
      expr_(expr)
  {
  } // ExprStepExpression

  virtual ~ExprStepExpression()
  {
    delete expr_;
  } // ExprStepExpression

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    if(!baseT::has_predicates())
     return expr_->evaluate(context, executionContext);

    NodeSet<string_type, string_adaptor> ns = expr_->evaluate(context, executionContext).asNodeSet();
    ns.to_document_order();
    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(baseT::applyPredicates(ns, executionContext)));
  } // evaluate

  virtual XPathValue<string_type, string_adaptor> evaluate(NodeSet<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type, string_adaptor> c = context.top();
    return evaluate(c, executionContext);
  } // evaluate

private:
  XPathExpression_impl<string_type, string_adaptor>* expr_;
  std::vector<XPathExpression_impl<string_type, string_adaptor>*> predicates_;
}; // class ExprStepExpression

template<class string_type, class string_adaptor>
class StepFactory
{
public:
  static StepExpression<string_type, string_adaptor>*
                         createStep(typename types<string_adaptor>::node_iter_t& node, 
                                    typename types<string_adaptor>::node_iter_t const& end, 
                                    CompilationContext<string_type, string_adaptor>& context)
  {
    Axis axis = getAxis(node);
    return createStep(node, end, context, axis);
  } // createStep

  static StepExpression<string_type, string_adaptor>*
                         createStep(typename types<string_adaptor>::node_iter_t& node, 
                                    typename types<string_adaptor>::node_iter_t const& end, 
                                    CompilationContext<string_type, string_adaptor>& context,
                                    Axis axis,
                                    bool is_attr = false)
  {
    std::auto_ptr<NodeTest<string_type, string_adaptor> > test(getTest(node, end, !is_attr ? axis : ATTRIBUTE, context.namespaceContext()));
    std::auto_ptr<XPathExpression_impl<string_type, string_adaptor> > thing;
    if(test.get() == 0)
      thing.reset(XPath<string_type, string_adaptor>::compile_expression(node++, end, context));

    std::vector<XPathExpression_impl<string_type, string_adaptor>*> preds = createPredicates(node, end, context);

    if(test.get() == 0)
      return new ExprStepExpression<string_type, string_adaptor>(thing.release(), preds);
    return new TestStepExpression<string_type, string_adaptor>(axis, test.release(), preds);
  } // createStep

  static StepExpression<string_type, string_adaptor>* createFilter(const typename types<string_adaptor>::node_iter_t& node,
                                    CompilationContext<string_type, string_adaptor>& context)
  {
    typename types<string_adaptor>::node_iter_t c = node->children.begin();
    typename types<string_adaptor>::node_iter_t const ce = node->children.end();
    XPathExpression_impl<string_type, string_adaptor>* step = XPath<string_type, string_adaptor>::compile_expression(c, ce, context);
    ++c;
    std::vector<XPathExpression_impl<string_type, string_adaptor>*> preds = createPredicates(c, ce, context);
    return new ExprStepExpression<string_type, string_adaptor>(step, preds);
  } // createFilter

  static StepExpression<string_type, string_adaptor>* createSingleStep(typename types<string_adaptor>::node_iter_t& node, 
                                                                       typename types<string_adaptor>::node_iter_t const& end, 
                                                                       CompilationContext<string_type, string_adaptor>& context)
  {
    Axis axis = getAxis(node);
    return createSingleStep(node, end, context, axis);
  } // createStep

  static StepExpression<string_type, string_adaptor>* createSingleStep(typename types<string_adaptor>::node_iter_t& node, 
                                                                       typename types<string_adaptor>::node_iter_t const& end, 
                                                                       CompilationContext<string_type, string_adaptor>& context, 
                                                                       Axis axis)
  {
    NodeTest<string_type, string_adaptor>* test = getTest(node, end, axis, context.namespaceContext());
    return new TestStepExpression<string_type, string_adaptor>(axis, test);
    return 0;
  } // createStep

private:
  static Axis getAxis(typename types<string_adaptor>::node_iter_t& node)
  { 
    long id = getNodeId<string_adaptor>(node);

    switch(id)
    {
      case impl::Slash_id:
      case impl::SelfSelect_id:
	      return SELF;   // don't advance node, SelfSelect is axis specifier and node test in one
      case impl::ParentSelect_id:
        return PARENT;
      case impl::SlashSlash_id:
        return DESCENDANT_OR_SELF;

      case impl::AxisSpecifier_id:
        {
          typename types<string_adaptor>::node_iter_t axis_node = node->children.begin();
          skipWhitespace<string_adaptor>(axis_node);
          ++node;
          return getAxis(axis_node);
        }

      case impl::AbbreviatedAxisSpecifier_id:
      case impl::Attribute_id:
        ++node;
        return ATTRIBUTE;
      case impl::AncestorOrSelf_id:
        ++node;
        return ANCESTOR_OR_SELF;
      case impl::Ancestor_id:
        ++node;
        return ANCESTOR;
      case impl::Child_id:
        ++node;
        return CHILD;
      case impl::DescendantOrSelf_id:
        ++node;
        return DESCENDANT_OR_SELF;
      case impl::Descendant_id:
        ++node;
        return DESCENDANT;
      case impl::FollowingSibling_id:
        ++node;
        return FOLLOWING_SIBLING;
      case impl::Following_id:
        ++node;
        return FOLLOWING;
      case impl::Namespace_id:
        ++node;
        return NAMESPACE;
      case impl::Parent_id:
        ++node;
        return PARENT;
      case impl::PrecedingSibling_id:
        ++node;
        return PRECEDING_SIBLING;
      case impl::Preceding_id:
        ++node;
        return PRECEDING;
      case impl::Self_id:
        ++node;
        return SELF;

      default:    
        return CHILD;
    } // switch(id)

    return CHILD;
  } // getAxis

  static std::vector<XPathExpression_impl<string_type, string_adaptor>*> createPredicates(typename types<string_adaptor>::node_iter_t& node, 
                                    typename types<string_adaptor>::node_iter_t const& end, 
                                    CompilationContext<string_type, string_adaptor>& context)
  {
    std::vector<XPathExpression_impl<string_type, string_adaptor>*> preds;

    while((node != end) && (getNodeId<string_adaptor>(node) == impl::Predicate_id))
    {
      typename types<string_adaptor>::node_iter_t c = node->children.begin();
      assert(getNodeId<string_adaptor>(c) == impl::LeftSquare_id);
      ++c;
      preds.push_back(XPath<string_type, string_adaptor>::compile_expression(c, node->children.end(), context));
      ++c;
      assert(getNodeId<string_adaptor>(c) == impl::RightSquare_id);
      
      ++node;
    } // if ...

    return preds;
  } // createPredicates

  static NodeTest<string_type, string_adaptor>* getTest(typename types<string_adaptor>::node_iter_t& node, 
                                        typename types<string_adaptor>::node_iter_t const& end, 
                                        Axis axis, 
                                        const NamespaceContext<string_type, string_adaptor>& namespaceContext)
  {
    long id = getNodeId<string_adaptor>(skipWhitespace<string_adaptor>(node));

    switch(id)
    {
      case impl::NodeTest_id:
        {
          typename types<string_adaptor>::node_iter_t c = node->children.begin();
          NodeTest<string_type, string_adaptor>* t = getTest(c, node->children.end(), axis, namespaceContext);
          ++node;
          return t;
        } // case NodeTest_id

      case impl::QName_id:
        {
          typename types<string_adaptor>::node_iter_t c = node->children.begin();
          string_type prefix = string_adaptor::construct(c->value.begin(), c->value.end());
          string_type uri = namespaceContext.namespaceURI(prefix);
          ++c;
          string_type name = string_adaptor::construct(c->value.begin(), c->value.end());
          ++node;
          if(axis == ATTRIBUTE)
          {
            if(prefix == string_adaptor::construct_from_utf8("xmlns"))
              return new FailNodeTest<string_type, string_adaptor>();
            return new AttributeQNameNodeTest<string_type, string_adaptor>(uri, name);
          }
          return new QNameNodeTest<string_type, string_adaptor>(uri, name);
        } //case QName_id
      
      case impl::NCName_id:
        {
          string_type name = string_adaptor::construct(node->value.begin(), node->value.end());
          ++node;
          if(axis == ATTRIBUTE)
          {
            if(name == string_adaptor::construct_from_utf8("xmlns"))
              return new FailNodeTest<string_type, string_adaptor>();
            return new AttributeNameNodeTest<string_type, string_adaptor>(name);
          }
          return new NameNodeTest<string_type, string_adaptor>(name);
        } // case NameNodeTest

      case impl::Comment_id:
        {
          ++node;
          return new CommentNodeTest<string_type, string_adaptor>();
        } // case CommentTest_id
    
      case impl::Text_id:
        {
          ++node;
          return new TextNodeTest<string_type, string_adaptor>();
        } // case Text_id

      case impl::ProcessingInstruction_id:
        {
          ++node;
          if((node == end) || (getNodeId<string_adaptor>(node) != impl::Literal_id)) 
            return new ProcessingInstructionNodeTest<string_type, string_adaptor>();
          
          string_type target = string_adaptor::construct(node->value.begin(), node->value.end());
          ++node;
          return new ProcessingInstructionNodeTest<string_type, string_adaptor>(target);
        } // case ProcessingInstruction_id
      
      case impl::SlashSlash_id:
  	  case impl::SelfSelect_id:
      case impl::ParentSelect_id:
      case impl::Node_id:
        {
          ++node;
          return new AnyNodeTest<string_type, string_adaptor>();
        } // case Node_id

      case impl::NodeMatchPattern_id:
        {
          ++node;
          return new NodeNodeTest<string_type, string_adaptor>();
        } // case NodeMatchPattern_id

      case impl::Slash_id:
        return new RootNodeTest<string_type, string_adaptor>();

      case impl::AnyName_id:
        {
          ++node;
          if(axis == ATTRIBUTE)
            return new AttributeNodeTest<string_type, string_adaptor>();
          return new StarNodeTest<string_type, string_adaptor>();
        } // case AnyName_id:

      case impl::NameTest_id:
        {
          typename types<string_adaptor>::node_iter_t prefixNode = node->children.begin();
          ++node;
          string_type prefix = string_adaptor::construct(prefixNode->value.begin(), prefixNode->value.end());
          string_type uri = namespaceContext.namespaceURI(prefix);
          if(axis == ATTRIBUTE)
          {
            if(prefix == string_adaptor::construct_from_utf8("xmlns"))
              return new FailNodeTest<string_type, string_adaptor>();
            return new AttributeQStarNodeTest<string_type, string_adaptor>(uri);
          }
          return new QStarNodeTest<string_type, string_adaptor>(uri);
        } // case 
    } // switch(id)

    return 0;
  } // getTest

  StepFactory();
}; // class StepFactory

template<class string_type, class string_adaptor>
class IdKeyStepExpression : public StepExpression<string_type, string_adaptor>
{
  typedef StepExpression<string_type, string_adaptor> baseT;
public:
  IdKeyStepExpression(XPathExpression_impl<string_type, string_adaptor>* expr) :
      expr_(expr)
  {
  } // IdKeyStepExpression

  virtual ~IdKeyStepExpression()
  {
    delete expr_;
  } // ~IdKeyStepExpression

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                                           const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    NodeSet<string_type, string_adaptor> ns;

    NodeSet<string_type, string_adaptor> nodes = expr_->evaluate(context, executionContext).asNodeSet();
    for(typename NodeSet<string_type, string_adaptor>::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
      if(context == *n)
      {
        ns.push_back(context);
        break;
      } // if ...

    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(ns));
  } // evaluate

  virtual XPathValue<string_type, string_adaptor> evaluate(NodeSet<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type, string_adaptor> c = context.top();
    return evaluate(c, executionContext);
  } // evaluate

private:
  XPathExpression_impl<string_type, string_adaptor>* expr_;
}; // class IdKeyStepExpression

template<class string_type, class string_adaptor>
class RelativeLocationPath : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  RelativeLocationPath(StepExpression<string_type, string_adaptor>* step) : steps_() { steps_.push_back(step); }
  RelativeLocationPath(const StepList<string_type, string_adaptor>& steps) : steps_(steps) { }

  virtual ~RelativeLocationPath()
  {
    for(typename StepList<string_type, string_adaptor>::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
      delete *i;
  } // ~RelativeLocationPath

  virtual ValueType type() const { return NODE_SET; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    NodeSet<string_type, string_adaptor> nodes;
    nodes.push_back(context);

    for(typename StepList<string_type, string_adaptor>::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
    {
      XPathValue<string_type, string_adaptor> v = (*i)->evaluate(nodes, executionContext);
      nodes = v.asNodeSet();
    } // for ...

    nodes.sort();

    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(nodes));
  } // evaluate

private:
  StepList<string_type, string_adaptor> steps_;

  friend class MatchExpr<string_type, string_adaptor>;
}; // RelativeLocationPath

template<class string_type, class string_adaptor>
class AbsoluteLocationPath : public RelativeLocationPath<string_type, string_adaptor>
{
public:
  AbsoluteLocationPath(StepExpression<string_type, string_adaptor>* step) : RelativeLocationPath<string_type, string_adaptor>(step) { }
  AbsoluteLocationPath(const StepList<string_type, string_adaptor>& steps) : RelativeLocationPath<string_type, string_adaptor>(steps) { }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    int type = context.getNodeType();
    if((type == DOM::Node_base::DOCUMENT_NODE) || 
       (type == DOM::Node_base::DOCUMENT_FRAGMENT_NODE))
      return RelativeLocationPath<string_type, string_adaptor>::evaluate(context, executionContext);
    
    DOM::Document<string_type, string_adaptor> document = context.getOwnerDocument();
    return RelativeLocationPath<string_type, string_adaptor>::evaluate(document, executionContext);
  } // evaluate
}; // class AbsoluteLocationPath

} // impl
} // XPath
} // Arabica
#endif
