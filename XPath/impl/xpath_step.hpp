#ifndef ARABICA_XPATHIC_XPATH_STEP_H
#define ARABICA_XPATHIC_XPATH_STEP_H

#include <DOM/Document.h>
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

class StepExpression : public XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  StepExpression() { }
  StepExpression(const std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> > *>& predicates) : predicates_(predicates) { }

  virtual ~StepExpression()
  { 
    for(std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*>::iterator p = predicates_.begin(), e = predicates_.end(); p != e; ++p)
      delete *p;
  } // ~StepExpression

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const = 0;
  virtual XPathValuePtr<std::string> evaluate(NodeSet<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const = 0;

  bool has_predicates() const { return !predicates_.empty(); }

protected:
  NodeSet<std::string> applyPredicates(NodeSet<std::string>& nodes, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& parentContext) const
  {
    for(std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*>::const_iterator p = predicates_.begin(), e = predicates_.end();
        (p != e) && (!nodes.empty()); ++p)
      nodes = applyPredicate(nodes, *p, parentContext);
    return nodes;
  } // applyPredicates

private:
  NodeSet<std::string> applyPredicate(NodeSet<std::string>& nodes, 
                                      XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* predicate, 
                                      const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& parentContext) const
  {
    ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> > executionContext(nodes.size(), parentContext);
    NodeSet<std::string> results(nodes.forward());
    unsigned int position = 1;
    for(NodeSet<std::string>::iterator i = nodes.begin(); i != nodes.end(); ++i, ++position)
    {
      executionContext.setPosition(position);
      XPathValuePtr<std::string> v = predicate->evaluate(*i, executionContext);

      if((v->type() == NUMBER) && (position != v->asNumber()))
        continue;
      if(v->asBool() == false)
        continue;

      results.push_back(*i);
    } // for ...
    return results;
  } // applyPredicate
  
  std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*> predicates_;
}; // StepExpression

class TestStepExpression : public StepExpression
{
public:
  TestStepExpression(Axis axis, NodeTest<std::string>* test) :
      StepExpression(),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  TestStepExpression(Axis axis, NodeTest<std::string>* test, 
                     const std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*>& predicates) :
      StepExpression(predicates),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  virtual ~TestStepExpression()
  {
    delete test_;
  } // StepExpression

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    NodeSet<std::string> nodes;
    enumerateOver(context, nodes, executionContext);
    return XPathValuePtr<std::string>(new NodeSetValue<std::string, Arabica::default_string_adaptor<std::string> >(nodes));
  } // evaluate

  virtual XPathValuePtr<std::string> evaluate(NodeSet<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    NodeSet<std::string> nodes;
    for(NodeSet<std::string>::iterator n = context.begin(); n != context.end(); ++n)
      enumerateOver(*n, nodes, executionContext);
    return XPathValuePtr<std::string>(new NodeSetValue<std::string, Arabica::default_string_adaptor<std::string> >(nodes));
  } // evaluate

private:
  void enumerateOver(const DOM::Node<std::string>& context, 
                     NodeSet<std::string>& results, 
                     const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& parentContext) const
  {
    AxisEnumerator enumerator(context, axis_);
    NodeSet<std::string> intermediate(enumerator.forward());
    NodeSet<std::string>& d = (!has_predicates()) ? results : intermediate;
    while(*enumerator != 0)
    {
      // if test
      DOM::Node<std::string> node = *enumerator;
      if((*test_)(node))
        d.push_back(node);
      ++enumerator;
    } // while ...
    
    if(!has_predicates())
    {
      results.forward(enumerator.forward());
      return;
    } // if ...

    intermediate = applyPredicates(intermediate, parentContext);

    results.swap(intermediate);
  } // enumerateOver

  Axis axis_;
  NodeTest<std::string>* test_;
}; // class TestStepExpression

class ExprStepExpression : public StepExpression
{
public:
  ExprStepExpression(XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* expr, 
                     const std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*>& predicates) :
      StepExpression(predicates),
      expr_(expr)
  {
  } // ExprStepExpression

  virtual ~ExprStepExpression()
  {
    delete expr_;
  } // ExprStepExpression

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    if(!has_predicates())
     return expr_->evaluate(context, executionContext);

    NodeSet<std::string> ns = expr_->evaluate(context, executionContext)->asNodeSet();
    return XPathValuePtr<std::string>(new NodeSetValue<std::string, Arabica::default_string_adaptor<std::string> >(applyPredicates(ns, executionContext)));
  } // evaluate

  virtual XPathValuePtr<std::string> evaluate(NodeSet<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    DOM::Node<std::string> c = context.top();
    return evaluate(c, executionContext);
  } // evaluate

private:
  XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* expr_;
  std::vector<XPathExpression*> predicates_;
}; // class ExprStepExpression

class StepFactory
{
public:
  static StepExpression* createStep(node_iter_t& node, 
                                    node_iter_t const& end, 
                                    CompilationContext<std::string, Arabica::default_string_adaptor<std::string> >& context)
  {
    Axis axis = getAxis(node);
    NodeTest<std::string>* test = getTest(node, context.namespaceContext());
    XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* thing = 0;
    if(!test)
      thing = XPath<std::string>::compile_expression(node++, context);

    std::vector<XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >*> preds;

    while((node != end) && (getNodeId(node) == impl::Predicate_id))
    {
      node_iter_t c = node->children.begin();
      assert(getNodeId(c) == impl::LeftSquare_id);
      ++c;
      preds.push_back(XPath<std::string>::compile_expression(c, context));
      ++c;
      assert(getNodeId(c) == impl::RightSquare_id);
      
      ++node;
    } // if ...
    if(!test)
      return new ExprStepExpression(thing, preds);
    return new TestStepExpression(axis, test, preds);
  } // createStep

  static StepExpression* createStep(node_iter_t& node, CompilationContext<std::string, Arabica::default_string_adaptor<std::string> >& context)
  {
    Axis axis = getAxis(node);
    NodeTest<std::string>* test = getTest(node, context.namespaceContext());
    return new TestStepExpression(axis, test);
  } // createStep

private:
  static Axis getAxis(node_iter_t& node)
  { 
    long id = getNodeId(node);

    switch(id)
    {
      case impl::Slash_id:
      case impl::SelfSelect_id:
	      return SELF;   // don't advance node, SelfSelect is axis specifier and node test in one
      case impl::ParentSelect_id:
        return PARENT;
      case impl::SlashSlash_id:
        return DESCENDANT_OR_SELF;

      case impl::AbbreviatedAxisSpecifier_id:
        ++node;
        return ATTRIBUTE;

      case impl::AxisSpecifier_id:
        // skip on to the next bit
        break;

      default:    
        return CHILD;
    } // switch(id)

    node_iter_t axis_node = node->children.begin();
    long axis = getNodeId(skipWhitespace(axis_node));
    ++node;
    switch(axis)
    {
      case impl::AncestorOrSelf_id:
        return ANCESTOR_OR_SELF;
      case impl::Ancestor_id:
        return ANCESTOR;
      case impl::AbbreviatedAxisSpecifier_id:
      case impl::Attribute_id:
        return ATTRIBUTE;
      case impl::Child_id:
        return CHILD;
      case impl::DescendantOrSelf_id:
        return DESCENDANT_OR_SELF;
      case impl::Descendant_id:
        return DESCENDANT;
      case impl::FollowingSibling_id:
        return FOLLOWING_SIBLING;
      case impl::Following_id:
        return FOLLOWING;
      case impl::Namespace_id:
        return NAMESPACE;
      case impl::Parent_id:
        return PARENT;
      case impl::PrecedingSibling_id:
        return PRECEDING_SIBLING;
      case impl::Preceding_id:
        return PRECEDING;
      case impl::Self_id:
        return SELF;
    } // switch ...
    
    assert(false);
    return CHILD;
  } // getAxis

  static NodeTest<std::string>* getTest(node_iter_t& node, const NamespaceContext<std::string, Arabica::default_string_adaptor<std::string> >& namespaceContext)
  {
    long id = getNodeId(skipWhitespace(node));

    switch(id)
    {
      case impl::NodeTest_id:
        {
          node_iter_t c = node->children.begin();
          NodeTest<std::string>* t = getTest(c, namespaceContext);
          ++node;
          return t;
        } // case NodeTest_id

      case impl::QName_id:
        {
          node_iter_t c = node->children.begin();
          std::string prefix(c->value.begin(), c->value.end());
          std::string uri = namespaceContext.namespaceURI(prefix);
          ++c;
          std::string name(c->value.begin(), c->value.end());
          ++node;
          return new QNameNodeTest<std::string>(uri, name);
        } //case QName_id
      
      case impl::NCName_id:
        {
          std::string name(node->value.begin(), node->value.end());
          ++node;
          return new NameNodeTest<std::string>(name);
        } // case NameNodeTest

      case impl::Comment_id:
        {
          ++node;
          return new CommentNodeTest<std::string>();
        } // case CommentTest_id
    
      case impl::Text_id:
        {
          ++node;
          return new TextNodeTest<std::string>();
        } // case Text_id

      case impl::ProcessingInstruction_id:
        {
          ++node;
          if(getNodeId(node) != impl::Literal_id) // not sure if this is always safe
            return new ProcessingInstructionNodeTest<std::string>();
          
          std::string target(node->value.begin(), node->value.end());
          ++node;
          return new ProcessingInstructionNodeTest<std::string>(target);
        } // case ProcessingInstruction_id
      
      case impl::SlashSlash_id:
      case impl::Node_id:
        {
          ++node;
          return new AnyNodeTest<std::string>();
        } // case Node_id

      case impl::Slash_id:
        return new RootNodeTest<std::string>();

      case impl::AnyName_id:
  	  case impl::SelfSelect_id:
      case impl::ParentSelect_id:
        {
          ++node;
          return new StarNodeTest<std::string>();
        } // case AnyName_id:

      case impl::NameTest_id:
        {
          node_iter_t prefixNode = node->children.begin();
          ++node;
          std::string prefix(prefixNode->value.begin(), prefixNode->value.end());
          std::string uri = namespaceContext.namespaceURI(prefix);
          return new QStarNodeTest<std::string>(uri);
        } // case 
    } // switch(id)

    return 0;
  } // getTest

  StepFactory();
}; // class StepFactory

class RelativeLocationPath : public XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  RelativeLocationPath(StepExpression* step) : steps_() { steps_.push_back(step); }
  RelativeLocationPath(const StepList& steps) : steps_(steps) { }

  virtual ~RelativeLocationPath()
  {
    for(StepList::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
      delete *i;
  } // ~LocationPath

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    NodeSet<std::string> nodes;
    nodes.push_back(context);

    for(StepList::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
    {
      XPathValuePtr<std::string> v = (*i)->evaluate(nodes, executionContext);
      nodes = v->asNodeSet();
    } // for ...

    return XPathValuePtr<std::string>(new NodeSetValue<std::string, Arabica::default_string_adaptor<std::string> >(nodes));
  } // do_evaluate

private:
  StepList steps_;
}; // LocationPath

class AbsoluteLocationPath : public RelativeLocationPath
{
public:
  AbsoluteLocationPath(StepExpression* step) : RelativeLocationPath(step) { }
  AbsoluteLocationPath(const StepList& steps) : RelativeLocationPath(steps) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    int type = context.getNodeType();
    if((type == DOM::Node<std::string>::DOCUMENT_NODE) || 
       (type == DOM::Node<std::string>::DOCUMENT_FRAGMENT_NODE))
      return RelativeLocationPath::evaluate(context, executionContext);
    
    DOM::Document<std::string> document = context.getOwnerDocument();
    return RelativeLocationPath::evaluate(document, executionContext);
  } // evaluate
}; // class AbsoluteLocationPath


} // XPath
} // Arabica
#endif
