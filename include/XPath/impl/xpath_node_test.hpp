#ifndef ARABICA_XPATHIC_XPATH_NODE_TEST_HPP
#define ARABICA_XPATHIC_XPATH_NODE_TEST_HPP

#include <DOM/Node.hpp>
#include "xpath_namespace_node.hpp"
#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type, class string_adaptor>
class NodeTest
{
protected:
  NodeTest() { }
public:
  virtual ~NodeTest() { }
  virtual NodeTest* clone() const = 0;
  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const = 0;

private:
  NodeTest(NodeTest&);
  bool operator==(const NodeTest&);
  NodeTest& operator=(const NodeTest&);
}; // class NodeTest

template<class string_type, class string_adaptor>
class AnyNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new AnyNodeTest(); }
  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& /* node */) const
  {
    return true;
  } // matches
}; // class AnyNodeTest

template<class string_type, class string_adaptor>
class NodeNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new NodeNodeTest(); }
  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    int type = node.getNodeType();
    if((type == DOM::Node_base::DOCUMENT_NODE) || 
       (type == DOM::Node_base::DOCUMENT_FRAGMENT_NODE))
      return false;
    return true;
  } // matches
}; // class NodeNodeTest

template<class string_type, class string_adaptor>
class NameNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  NameNodeTest(const string_type& name) : name_(name) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new NameNodeTest(name_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node_base::ELEMENT_NODE || type == NAMESPACE_NODE_TYPE) && 
           (name_ == node.getNodeName()) &&
           (string_adaptor::empty(node.getNamespaceURI()));
  } // test

private:
  string_type name_;
}; // NameNodeTest

template<class string_type, class string_adaptor>
class AttributeNameNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  AttributeNameNodeTest(const string_type& name) : name_(name) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new AttributeNameNodeTest(name_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE &&
           (name_ == node.getNodeName()) &&
           (string_adaptor::empty(node.getNamespaceURI()));
  } // operator()

private:
  string_type name_;
}; // class AttributeNameNodeTest

template<class string_type, class string_adaptor>
class QNameNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  QNameNodeTest(const string_type& namespace_uri, const string_type& name) : 
      uri_(namespace_uri), name_(name) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new QNameNodeTest(uri_, name_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node_base::ELEMENT_NODE || type == NAMESPACE_NODE_TYPE) && 
           (name_ == node.getLocalName()) &&
           (uri_ == node.getNamespaceURI());
  } // test

private:
  string_type uri_;
  string_type name_;
}; // QNameNodeTest

template<class string_type, class string_adaptor>
class AttributeQNameNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  AttributeQNameNodeTest(const string_type& namespace_uri, const string_type& name) : 
      uri_(namespace_uri), name_(name) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new AttributeQNameNodeTest(uri_, name_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE &&
           (name_ == node.getLocalName()) &&
           (uri_ == node.getNamespaceURI());
  } // test

private:
  string_type uri_;
  string_type name_;
}; // class AttributeQNameNodeTest

template<class string_type, class string_adaptor>
class StarNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new StarNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node_base::ELEMENT_NODE ||
            type == NAMESPACE_NODE_TYPE);
  } // test
}; // class StarNodeTest

template<class string_type, class string_adaptor>
class QStarNodeTest : public StarNodeTest<string_type, string_adaptor>
{
  typedef StarNodeTest<string_type, string_adaptor> baseT;
public:
  QStarNodeTest(const string_type& namespace_uri) : baseT(), uri_(namespace_uri) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new QStarNodeTest(uri_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return (uri_ == node.getNamespaceURI()) &&
            baseT::operator()(node);
  } // test

private:
  string_type uri_;
}; // clase QStarNodeTest

template<class string_type, class string_adaptor>
class TextNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new TextNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return nodeIsText<string_type, string_adaptor>(node);
  } // test
}; // class TextNodeTest

template<class string_type, class string_adaptor>
class CommentNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new CommentNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return node.getNodeType() == DOM::Node_base::COMMENT_NODE;
  } // operator()
}; // CommentNodeTest

template<class string_type, class string_adaptor>
class AttributeNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new AttributeNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return node.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE;
  } // operator()
}; // AttributeNodeTest

template<class string_type, class string_adaptor>
class AttributeQStarNodeTest : public AttributeNodeTest<string_type, string_adaptor>
{
  typedef AttributeNodeTest<string_type, string_adaptor> baseT;
public:
  AttributeQStarNodeTest(const string_type& namespace_uri) : baseT(), uri_(namespace_uri) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new AttributeQStarNodeTest(uri_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return (uri_ == node.getNamespaceURI()) &&
            baseT::operator()(node);
  } // test

private:
  string_type uri_;
}; // clase AttributeQStarNodeTest


template<class string_type, class string_adaptor>
class NotAttributeNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new NotAttributeNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    return node.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE;
  } // operator()
}; // NotAttributeNodeTest

template<class string_type, class string_adaptor>
class ProcessingInstructionNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  ProcessingInstructionNodeTest() : target_() { }
  ProcessingInstructionNodeTest(const string_type& target) : target_(target) { }
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new ProcessingInstructionNodeTest(target_); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    if(node.getNodeType() != DOM::Node_base::PROCESSING_INSTRUCTION_NODE)
      return false;

    if(string_adaptor::empty(target_))
      return true;

    return node.getNodeName() == target_;
  } // test

private:
  string_type target_;
}; // ProcessingInstructionNodeTest

template<class string_type, class string_adaptor>
class RootNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new RootNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node_base::DOCUMENT_NODE) || 
           (type == DOM::Node_base::DOCUMENT_FRAGMENT_NODE);

  } // operator()
}; // RootNodeTest

template<class string_type, class string_adaptor>
class FailNodeTest : public NodeTest<string_type, string_adaptor>
{
public:
  virtual NodeTest<string_type, string_adaptor>* clone() const { return new FailNodeTest(); }

  virtual bool operator()(const DOM::Node<string_type, string_adaptor>&) const
  {
    return false;
  } // operator()
}; // class FailNodeTest

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
