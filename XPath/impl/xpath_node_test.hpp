#ifndef ARABICA_XPATHIC_XPATH_NODE_TEST_HPP
#define ARABICA_XPATHIC_XPATH_NODE_TEST_HPP

#include <DOM/Node.h>
#include "xpath_namespace_node.hpp"
#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type>
class NodeTest
{
protected:
  NodeTest() { }
public:
  virtual ~NodeTest() { }
  virtual bool operator()(const DOM::Node<string_type>& node) const = 0;

private:
  NodeTest(NodeTest&);
  bool operator==(const NodeTest&);
  NodeTest& operator=(const NodeTest&);
}; // class NodeTest

template<class string_type>
class AnyNodeTest : public NodeTest<string_type>
{
public:
  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return true;
  } // matches
}; // class AnyNodeTest

template<class string_type, class string_adaptor>
class NameNodeTest : public NodeTest<string_type>
{
public:
  NameNodeTest(const string_type& name) : name_(name) { }

  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return (name_ == node.getNodeName()) &&
      (string_adaptor::empty(node.getPrefix()));
  } // test

private:
  string_type name_;
}; // NameNodeTest

template<class string_type>
class QNameNodeTest : public NodeTest<string_type>
{
public:
  QNameNodeTest(const string_type& namespace_uri, const string_type& name) : uri_(namespace_uri), name_(name) { }

  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return (name_ == node.getLocalName()) &&
           (uri_ == node.getNamespaceURI());
  } // test

private:
  string_type uri_;
  string_type name_;
}; // QNameNodeTest

template<class string_type>
class StarNodeTest : public NodeTest<string_type>
{
public:
  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    // match the primary node types on the various axis
    // fortunately they are all independent 
    int type = node.getNodeType();
    return (type == DOM::Node_base::ELEMENT_NODE ||
            type == NAMESPACE_NODE_TYPE || 
            type == DOM::Node_base::ATTRIBUTE_NODE);
  } // test
}; // class StarNodeTest

template<class string_type>
class QStarNodeTest : public NodeTest<string_type>
{
public:
  QStarNodeTest(const string_type& namespace_uri) : uri_(namespace_uri) { }

  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return (uri_ == node.getNamespaceURI());
  } // test

private:
  string_type uri_;
}; // clase QStarNodeTest

template<class string_type>
class TextNodeTest : public NodeTest<string_type>
{
public:
  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return node.getNodeType() == DOM::Node<string_type>::TEXT_NODE;
  } // test
}; // class TextNodeTest

template<class string_type>
class CommentNodeTest : public NodeTest<string_type>
{
public:
  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    return node.getNodeType() == DOM::Node<string_type>::COMMENT_NODE;
  } // operator()
}; // CommentNodeTest

template<class string_type, class string_adaptor>
class ProcessingInstructionNodeTest : public NodeTest<string_type>
{
public:
  ProcessingInstructionNodeTest() : target_() { }
  ProcessingInstructionNodeTest(const string_type& target) : target_(target) { }

  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    if(node.getNodeType() != DOM::Node<string_type>::PROCESSING_INSTRUCTION_NODE)
      return false;

    if(string_adaptor::empty(target_))
      return true;

    return node.getNodeName() == target_;
  } // test

private:
  string_type target_;
}; // ProcessingInstructionNodeTest

template<class string_type>
class RootNodeTest : public NodeTest<string_type>
{
public:
  virtual bool operator()(const DOM::Node<string_type>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node<string_type>::DOCUMENT_NODE) || 
           (type == DOM::Node<string_type>::DOCUMENT_FRAGMENT_NODE);

  } // operator()
}; // RootNodeTest

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
