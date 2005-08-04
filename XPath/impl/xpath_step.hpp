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

class StepExpression : public XPathExpression
{
public:
  StepExpression() { }
  StepExpression(std::vector<XPathExpression*> predicates) : predicates_(predicates) { }

  virtual ~StepExpression()
  { 
    for(std::vector<XPathExpression*>::iterator p = predicates_.begin(), e = predicates_.end(); p != e; ++p)
      delete *p;
  } // ~StepExpression

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const = 0;
  virtual XPathValuePtr evaluate(NodeSet& context, const ExecutionContext& executionContext) const = 0;

  bool has_predicates() const { return !predicates_.empty(); }

protected:
  NodeSet applyPredicates(NodeSet& nodes, const ExecutionContext& parentContext) const
  {
    for(std::vector<XPathExpression*>::const_iterator p = predicates_.begin(), e = predicates_.end();
        (p != e) && (!nodes.empty()); ++p)
      nodes = applyPredicate(nodes, *p, parentContext);
    return nodes;
  } // applyPredicates

private:
  NodeSet applyPredicate(NodeSet& nodes, XPathExpression* predicate, const ExecutionContext& parentContext) const
  {
    ExecutionContext executionContext(nodes.size(), parentContext);
    NodeSet results(nodes.forward());
    unsigned int position = 1;
    for(NodeSet::iterator i = nodes.begin(); i != nodes.end(); ++i, ++position)
    {
      executionContext.setPosition(position);
      XPathValuePtr v = predicate->evaluate(*i, executionContext);

      if((v->type() == NUMBER) && (position != v->asNumber()))
        continue;
      if(v->asBool() == false)
        continue;

      results.push_back(*i);
    } // for ...
    return results;
  } // applyPredicate
  
  std::vector<XPathExpression*> predicates_;
}; // StepExpression

class TestStepExpression : public StepExpression
{
public:
  TestStepExpression(Axis axis, NodeTest* test) :
      StepExpression(),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  TestStepExpression(Axis axis, NodeTest* test, std::vector<XPathExpression*> predicates) :
      StepExpression(predicates),
      axis_(axis),
      test_(test)
  {
  } // TestStepExpression

  virtual ~TestStepExpression()
  {
    delete test_;
  } // StepExpression

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    NodeSet nodes;
    enumerateOver(context, nodes, executionContext);
    return XPathValuePtr(new NodeSetValue(nodes));
  } // evaluate

  virtual XPathValuePtr evaluate(NodeSet& context, const ExecutionContext& executionContext) const
  {
    NodeSet nodes;
    for(NodeSet::iterator n = context.begin(); n != context.end(); ++n)
      enumerateOver(*n, nodes, executionContext);
    return XPathValuePtr(new NodeSetValue(nodes));
  } // evaluate

private:
  void enumerateOver(const DOM::Node<std::string>& context, NodeSet& results, 
                     const ExecutionContext& parentContext) const
  {
    AxisEnumerator enumerator(context, axis_);
    NodeSet intermediate(enumerator.forward());
    NodeSet& d = (!has_predicates()) ? results : intermediate;
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
  NodeTest* test_;
}; // class TestStepExpression

class ExprStepExpression : public StepExpression
{
public:
  ExprStepExpression(XPathExpression* expr, std::vector<XPathExpression*> predicates) :
      StepExpression(predicates),
      expr_(expr)
  {
  } // ExprStepExpression

  virtual ~ExprStepExpression()
  {
    delete expr_;
  } // ExprStepExpression

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    if(!has_predicates())
     return expr_->evaluate(context, executionContext);

    NodeSet ns = expr_->evaluate(context, executionContext)->asNodeSet();
    return XPathValuePtr(new NodeSetValue(applyPredicates(ns, executionContext)));
  } // evaluate

  virtual XPathValuePtr evaluate(NodeSet& context, const ExecutionContext& executionContext) const
  {
    DOM::Node<std::string> c = context.top();
    return evaluate(c, executionContext);
  } // evaluate

private:
  XPathExpression* expr_;
  std::vector<XPathExpression*> predicates_;
}; // class ExprStepExpression

class StepFactory
{
public:
  static StepExpression* createStep(node_iter_t& node, node_iter_t const& end, CompilationContext& context)
  {
    Axis axis = getAxis(node);
    NodeTest* test = getTest(node, context.namespaceContext());
    XPathExpression* thing = 0;
    if(!test)
      thing = compile_expression(node++, context);

    std::vector<XPathExpression*> preds;

    while((node != end) && (getNodeId(node) == Predicate_id))
    {
      node_iter_t c = node->children.begin();
      assert(getNodeId(c) == LeftSquare_id);
      ++c;
      preds.push_back(compile_expression(c, context));
      ++c;
      assert(getNodeId(c) == RightSquare_id);
      
      ++node;
    } // if ...
    if(!test)
      return new ExprStepExpression(thing, preds);
    return new TestStepExpression(axis, test, preds);
  } // createStep

  static StepExpression* createStep(node_iter_t& node, CompilationContext& context)
  {
    Axis axis = getAxis(node);
    NodeTest* test = getTest(node, context.namespaceContext());
    return new TestStepExpression(axis, test);
  } // createStep

private:
  static Axis getAxis(node_iter_t& node)
  { 
    long id = getNodeId(node);

    switch(id)
    {
      case Slash_id:
      case SelfSelect_id:
	      return SELF;   // don't advance node, SelfSelect is axis specifier and node test in one
      case ParentSelect_id:
        return PARENT;
      case SlashSlash_id:
        return DESCENDANT_OR_SELF;

      case AbbreviatedAxisSpecifier_id:
        ++node;
        return ATTRIBUTE;

      case AxisSpecifier_id:
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
      case AncestorOrSelf_id:
        return ANCESTOR_OR_SELF;
      case Ancestor_id:
        return ANCESTOR;
      case AbbreviatedAxisSpecifier_id:
      case Attribute_id:
        return ATTRIBUTE;
      case Child_id:
        return CHILD;
      case DescendantOrSelf_id:
        return DESCENDANT_OR_SELF;
      case Descendant_id:
        return DESCENDANT;
      case FollowingSibling_id:
        return FOLLOWING_SIBLING;
      case Following_id:
        return FOLLOWING;
      case Namespace_id:
        return NAMESPACE;
      case Parent_id:
        return PARENT;
      case PrecedingSibling_id:
        return PRECEDING_SIBLING;
      case Preceding_id:
        return PRECEDING;
      case Self_id:
        return SELF;
    } // switch ...
    
    assert(false);
    return CHILD;
  } // getAxis

  static NodeTest* getTest(node_iter_t& node, const NamespaceContext& namespaceContext)
  {
    long id = getNodeId(skipWhitespace(node));

    switch(id)
    {
      case NodeTest_id:
        {
          node_iter_t c = node->children.begin();
          NodeTest* t = getTest(c, namespaceContext);
          ++node;
          return t;
        } // case NodeTest_id

      case QName_id:
        {
          node_iter_t c = node->children.begin();
          std::string prefix(c->value.begin(), c->value.end());
          std::string uri = namespaceContext.namespaceURI(prefix);
          ++c;
          std::string name(c->value.begin(), c->value.end());
          ++node;
          return new QNameNodeTest(uri, name);
        } //case QName_id
      
      case NCName_id:
        {
          std::string name(node->value.begin(), node->value.end());
          ++node;
          return new NameNodeTest(name);
        } // case NameNodeTest

      case Comment_id:
        {
          ++node;
          return new CommentNodeTest();
        } // case CommentTest_id
    
      case Text_id:
        {
          ++node;
          return new TextNodeTest();
        } // case Text_id

      case ProcessingInstruction_id:
        {
          ++node;
          if(getNodeId(node) != Literal_id) // not sure if this is always safe
            return new ProcessingInstructionNodeTest();
          
          std::string target(node->value.begin(), node->value.end());
          ++node;
          return new ProcessingInstructionNodeTest(target);
        } // case ProcessingInstruction_id
      
      case SlashSlash_id:
      case Node_id:
        {
          ++node;
          return new AnyNodeTest();
        } // case Node_id

      case Slash_id:
        return new RootNodeTest();

      case AnyName_id:
  	  case SelfSelect_id:
      case ParentSelect_id:
        {
          ++node;
          return new StarNodeTest();
        } // case AnyName_id:

      case NameTest_id:
        {
          node_iter_t prefixNode = node->children.begin();
          ++node;
          std::string prefix(prefixNode->value.begin(), prefixNode->value.end());
          std::string uri = namespaceContext.namespaceURI(prefix);
          return new QStarNodeTest(uri);
        } // case 
    } // switch(id)

    return 0;
  } // getTest

  StepFactory();
}; // class StepFactory

class RelativeLocationPath : public XPathExpression
{
public:
  typedef std::vector<StepExpression*> StepList;

public:
  RelativeLocationPath(StepExpression* step) : steps_() { steps_.push_back(step); }
  RelativeLocationPath(const StepList& steps) : steps_(steps) { }

  virtual ~RelativeLocationPath()
  {
    for(StepList::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
      delete *i;
  } // ~LocationPath

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    NodeSet nodes;
    nodes.push_back(context);

    for(StepList::const_iterator i = steps_.begin(); i != steps_.end(); ++i)
    {
      XPathValuePtr v = (*i)->evaluate(nodes, executionContext);
      nodes = v->asNodeSet();
    } // for ...

    return XPathValuePtr(new NodeSetValue(nodes));
  } // do_evaluate

private:
  StepList steps_;
}; // LocationPath

class AbsoluteLocationPath : public RelativeLocationPath
{
public:
  AbsoluteLocationPath(StepExpression* step) : RelativeLocationPath(step) { }
  AbsoluteLocationPath(const RelativeLocationPath::StepList& steps) : RelativeLocationPath(steps) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
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
