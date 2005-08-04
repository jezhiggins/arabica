#ifndef ARABICA_XPATHIC_XPATH_NODE_TEST_HPP
#define ARABICA_XPATHIC_XPATH_NODE_TEST_HPP

#include <DOM/Node.h>
#include "xpath_namespace_node.hpp"
#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{

class NodeTest
{
protected:
  NodeTest() { }
public:
  virtual ~NodeTest() { }
  virtual bool operator()(const DOM::Node<std::string>& node) const = 0;

private:
  NodeTest(NodeTest&);
  bool operator==(const NodeTest&);
  NodeTest& operator=(const NodeTest&);
}; // class NodeTest

class AnyNodeTest : public NodeTest
{
public:
  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return true;
  } // matches
}; // class AnyNodeTest

class NameNodeTest : public NodeTest
{
public:
  NameNodeTest(const std::string& name) : name_(name) { }

  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return (name_ == node.getNodeName()) &&
           (node.getPrefix().empty());
  } // test

private:
  std::string name_;
}; // NameNodeTest

class QNameNodeTest : public NodeTest
{
public:
  QNameNodeTest(const std::string& namespace_uri, const std::string& name) : uri_(namespace_uri), name_(name) { }

  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return (name_ == node.getLocalName()) &&
           (uri_ == node.getNamespaceURI());
  } // test

private:
  std::string uri_;
  std::string name_;
}; // QNameNodeTest

class StarNodeTest : public NodeTest
{
public:
  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    // match the primary node types on the various axis
    // fortunately they are all independent 
    int type = node.getNodeType();
    return (type == DOM::Node_base::ELEMENT_NODE ||
            type == NAMESPACE_NODE_TYPE || 
            type == DOM::Node_base::ATTRIBUTE_NODE);
  } // test
}; // class StarNodeTest

class QStarNodeTest : public NodeTest
{
public:
  QStarNodeTest(const std::string& namespace_uri) : uri_(namespace_uri) { }

  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return (uri_ == node.getNamespaceURI());
  } // test

private:
  std::string uri_;
}; // clase QStarNodeTest

class TextNodeTest : public NodeTest
{
public:
  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return node.getNodeType() == DOM::Node<std::string>::TEXT_NODE;
  } // test
}; // class TextNodeTest

class CommentNodeTest : public NodeTest
{
public:
  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    return node.getNodeType() == DOM::Node<std::string>::COMMENT_NODE;
  } // operator()
}; // CommentNodeTest

class ProcessingInstructionNodeTest : public NodeTest
{
public:
  ProcessingInstructionNodeTest() : target_() { }
  ProcessingInstructionNodeTest(const std::string& target) : target_(target) { }

  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    if(node.getNodeType() != DOM::Node<std::string>::PROCESSING_INSTRUCTION_NODE)
      return false;

    if(target_.empty())
      return true;

    return node.getNodeName() == target_;
  } // test

private:
  std::string target_;
}; // ProcessingInstructionNodeTest

class RootNodeTest : public NodeTest
{
public:
  virtual bool operator()(const DOM::Node<std::string>& node) const
  {
    int type = node.getNodeType();
    return (type == DOM::Node<std::string>::DOCUMENT_NODE) || 
           (type == DOM::Node<std::string>::DOCUMENT_FRAGMENT_NODE);

  } // operator()
}; // RootNodeTest

} // namespace XPath


} // namespace Arabica

#endif
