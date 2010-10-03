#ifndef ARABICA_DOM_UTILS_STREAM_H
#define ARABICA_DOM_UTILS_STREAM_H
///////////////////////////////////////////////////////////////////////
//
// DOM/Utils/Stream.h
// 
// Written by Jez Higgins <jez@jezuk.co.uk>
// Copyright 2003-2005 Jez UK Ltd, http://www.jezuk.co.uk
//
// Provides streaming operator<< for DOM::Nodes.  Fully parameterised so
// will work with wide and narrow char types, so long as an operator<< 
// exists for the DOM::Node's string_type.
//
// e.g.
//  Arabica::SAX2DOM::Parser<std::wstring> domParser;
//  SAX::wInputSource is;
//  ... load instance from somewhere ...
//  domParser.parse(is);
//  DOM::Document<std::wstring> doc = domParser.getDocument();
//  ... manipulate doc ...
//  std::wcout << doc;  
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <map>
#include <text/UnicodeCharacters.hpp>
#include <XML/escaper.hpp>

namespace Arabica
{
namespace DOM
{

namespace StreamImpl
{
template<class stringT, class string_adaptorT, class charT, class traitsT>
void streamChildren(std::basic_ostream<charT, traitsT>& stream, const DOM::Node<stringT, string_adaptorT>& node)
{
  DOM::Node<stringT, string_adaptorT> child = node.getFirstChild();
  while(child != 0)
  {
    stream << child;
    child = child.getNextSibling();
  } // while 
} // streamChildren

template<class stringT>
void prefix_mapper_callback(std::ios_base::event ev, std::ios_base& stream, int index)
{
  if(ev == std::ios_base::erase_event)
    delete static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));
} // boing_callback

template<class stringT>
std::pair<bool, stringT> is_uri_declared(std::vector<std::map<stringT, stringT> >* prefix_stack, const stringT& namespaceURI)
{
  stringT declared_prefix;
  for(typename std::vector<std::map<stringT, stringT> >::reverse_iterator b = prefix_stack->rbegin(), e = prefix_stack->rend();
        b != e;
        ++b)
  {
    typename std::map<stringT, stringT>::const_iterator p = b->find(namespaceURI);
    if(p != b->end())
      return std::make_pair(true, p->second);
  } // for ...

  return std::make_pair(false, stringT());
} // is_uri_declared

template<class stringT, class string_adaptorT, class charT, class traitsT>
void check_and_output_node_name(std::basic_ostream<charT, traitsT>& stream, 
                                const DOM::Node<stringT, string_adaptorT>& node, 
                                std::vector<std::map<stringT, stringT> >* prefix_stack,
				const bool is_attribute,
				const long index)
{
  std::map<stringT, stringT>& current = *(prefix_stack->rbegin());

  stringT namespaceURI = node.getNamespaceURI();
  if(!string_adaptorT::empty(namespaceURI))
  {
    std::pair<bool, stringT> prefix = is_uri_declared(prefix_stack, namespaceURI);
    
    if(!prefix.first)
    {
      current[namespaceURI] = prefix.second = node.getPrefix();
      if(is_attribute && string_adaptorT::empty(prefix.second))
      {
	std::ostringstream os;
	os << 'a' << stream.iword(index)++;
	current[namespaceURI] = prefix.second = string_adaptorT::construct_from_utf8(os.str().c_str());
      } // if ...
    } // if ...

    if(!string_adaptorT::empty(prefix.second))
      stream << prefix.second << Arabica::text::Unicode<charT>::COLON;
    stream << node.getLocalName();
  }
  else
    stream << node.getNodeName();
} // check_and_output_node_name

template<class stringT, class string_adaptorT, class charT>
bool isXmlns(const stringT& str)
{
  typedef Arabica::text::Unicode<charT> UnicodeT;

  if(string_adaptorT::length(str) != 5)
    return false;

  typename string_adaptorT::const_iterator ci = string_adaptorT::begin(str);

  if((*ci == UnicodeT::LOWERCASE_X) &&
     (*(ci+1) == UnicodeT::LOWERCASE_M) &&
     (*(ci+2) == UnicodeT::LOWERCASE_L) &&
     (*(ci+3) == UnicodeT::LOWERCASE_N) &&
     (*(ci+4) == UnicodeT::LOWERCASE_S))
    return true;
  return false;
} // isXmlns

template<class stringT, class string_adaptorT>
bool compare_nodes_by_name(const DOM::Node<stringT, string_adaptorT>& lhs, 
			   const DOM::Node<stringT, string_adaptorT>& rhs)
{
  const stringT& lhsURI = lhs.getNamespaceURI();
  const stringT& rhsURI = rhs.getNamespaceURI();
  
  if(lhsURI == rhsURI)
    return lhs.getLocalName() < rhs.getLocalName();
  return lhsURI < rhsURI;
} // class compare_nodes_by_name

template<class stringT, class string_adaptorT, class charT, class traitsT>
int prefix_mapper(std::basic_ostream<charT, traitsT>& stream,
                  const DOM::Node<stringT, string_adaptorT>& node)
{
  typedef Arabica::text::Unicode<charT> UnicodeT;

  static const int index = std::ios_base::xalloc();
  std::vector<std::map<stringT, stringT> >* prefix_stack;
  
  if(stream.pword(index) != 0)
  {
    prefix_stack = static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));
    prefix_stack->push_back(std::map<stringT, stringT>());
  }
  else
  {
    prefix_stack = new std::vector<std::map<stringT, stringT> >;
    stream.pword(index) = prefix_stack;
    stream.iword(index) = 0;

    std::map<stringT, stringT> prefixes;
    for(DOM::Node<stringT, string_adaptorT> p = node.getParentNode(); 
        p.getNodeType() == DOM::Node_base::ELEMENT_NODE; 
        p = p.getParentNode())
    {
      if(string_adaptorT::empty(p.getNamespaceURI()))
        continue;
      if(prefixes.find(p.getNamespaceURI()) == prefixes.end())
        prefixes[p.getNamespaceURI()] = p.getPrefix();
    } // for ...

    prefix_stack->push_back(prefixes);
  } // if ...

  std::map<stringT, stringT>& current = *(prefix_stack->rbegin());

  // is element namespace URI declared?
  check_and_output_node_name(stream, node, prefix_stack, false, index);
  
  const DOM::NamedNodeMap<stringT, string_adaptorT> attrs = node.getAttributes();
  std::vector<DOM::Node<stringT, string_adaptorT> > attrNodes;
  for(unsigned int a = 0; a < attrs.getLength(); ++a)
    attrNodes.push_back(attrs.item(a));
  std::sort(attrNodes.begin(), attrNodes.end(), 
  	    compare_nodes_by_name<stringT, string_adaptorT>);

  for(unsigned int a = 0; a < attrNodes.size(); ++a)
  {
    //DOM::Node<stringT, string_adaptorT> attr = attrs.getNamedItem(*a);
    const DOM::Node<stringT, string_adaptorT> attr = attrNodes[a];
    if(isXmlns<stringT, string_adaptorT, charT>(attr.getNodeName()) || 
       isXmlns<stringT, string_adaptorT, charT>(attr.getPrefix()))
      continue;
    stream << UnicodeT::SPACE;
    check_and_output_node_name(stream, attr, prefix_stack, true, index);
    stream  << UnicodeT::EQUALS_SIGN
            << UnicodeT::QUOTATION_MARK;
    stringT value = attr.getNodeValue();
    std::for_each(string_adaptorT::begin(value), 
                  string_adaptorT::end(value), 
                  Arabica::XML::attribute_escaper<charT, traitsT>(stream));
    stream << UnicodeT::QUOTATION_MARK;
  }

  for(typename std::map<stringT, stringT>::const_iterator i = current.begin(), e = current.end();
      i != e;
      ++i)
  {
    stream << UnicodeT::SPACE
           << UnicodeT::LOWERCASE_X
           << UnicodeT::LOWERCASE_M
           << UnicodeT::LOWERCASE_L
           << UnicodeT::LOWERCASE_N
           << UnicodeT::LOWERCASE_S;
    if(!(string_adaptorT::empty(i->second)))
      stream << UnicodeT::COLON << i->second;
    stream << UnicodeT::EQUALS_SIGN << UnicodeT::QUOTATION_MARK;
    std::for_each(string_adaptorT::begin(i->first), 
                  string_adaptorT::end(i->first), 
                  Arabica::XML::attribute_escaper<charT, traitsT>(stream));
    stream << UnicodeT::QUOTATION_MARK;
  } // for ...

  return index;
} // prefix_mapper

template<class stringT, class string_adaptorT, class charT, class traitsT>
void prefix_mapper_pop(std::basic_ostream<charT, traitsT>& stream,
                       const DOM::Node<stringT, string_adaptorT>& node,
                       int index, 
                       bool output)
{
  std::vector<std::map<stringT, stringT> >* prefix_stack = 
    static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));

  if(output)
    check_and_output_node_name(stream, node, prefix_stack, false, index);

  prefix_stack->pop_back();
  if(prefix_stack->empty())
  {
    delete static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));
    stream.pword(index) = 0;
  } // if ...
} // prefix_mapper_pop

} // namespace StreamImpl

template<class stringT, class string_adaptorT, class charT, class traitsT>
std::basic_ostream<charT, traitsT>&
operator<<(std::basic_ostream<charT, traitsT>& stream,
           const DOM::Node<stringT, string_adaptorT>& node)
{
  typedef Arabica::text::Unicode<charT> UnicodeT;

  switch(node.getNodeType())
  {
  case DOM::Node_base::DOCUMENT_NODE:
    stream << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::QUESTION_MARK
           << UnicodeT::LOWERCASE_X
           << UnicodeT::LOWERCASE_M
           << UnicodeT::LOWERCASE_L
           << UnicodeT::SPACE
           << UnicodeT::LOWERCASE_V
           << UnicodeT::LOWERCASE_E
           << UnicodeT::LOWERCASE_R
           << UnicodeT::LOWERCASE_S
           << UnicodeT::LOWERCASE_I
           << UnicodeT::LOWERCASE_O
           << UnicodeT::LOWERCASE_N
           << UnicodeT::EQUALS_SIGN
           << UnicodeT::QUOTATION_MARK
           << UnicodeT::NUMBER_1
           << UnicodeT::FULL_STOP
           << UnicodeT::NUMBER_0
           << UnicodeT::QUOTATION_MARK
           << UnicodeT::QUESTION_MARK
           << UnicodeT::GREATER_THAN_SIGN
           << std::endl;
  case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
    StreamImpl::streamChildren(stream, node);
    break;
  case DOM::Node_base::ELEMENT_NODE:
    {
      stream << UnicodeT::LESS_THAN_SIGN;
      int index = StreamImpl::prefix_mapper(stream, node);

      if(node.hasChildNodes())
      {
        stream << UnicodeT::GREATER_THAN_SIGN;
        StreamImpl::streamChildren(stream, node);
        stream << UnicodeT::LESS_THAN_SIGN << UnicodeT::SLASH;
        StreamImpl::prefix_mapper_pop(stream, node, index, true);
        stream << UnicodeT::GREATER_THAN_SIGN;
      }
      else
      {
        StreamImpl::prefix_mapper_pop(stream, node, index, false);
        stream << UnicodeT::SLASH << UnicodeT::GREATER_THAN_SIGN;
      }
    }
    break;
  case DOM::Node_base::TEXT_NODE:
    {
      stringT value = node.getNodeValue();
      std::for_each(string_adaptorT::begin(value), 
                    string_adaptorT::end(value), 
                    Arabica::XML::text_escaper<charT, traitsT>(stream));
    }
    break;
  case DOM::Node_base::ENTITY_REFERENCE_NODE:
    stream << UnicodeT::AMPERSAND
           << node.getNodeName()
           << UnicodeT::SEMI_COLON;
    break;
  case DOM::Node_base::CDATA_SECTION_NODE:
    stream << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::LEFT_SQUARE_BRACKET
           << UnicodeT::CAPITAL_C
           << UnicodeT::CAPITAL_D
           << UnicodeT::CAPITAL_A
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_A
           << UnicodeT::LEFT_SQUARE_BRACKET
           << node.getNodeValue()
           << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN;
    break;
  case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
    stream << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::QUESTION_MARK
           << node.getNodeName()
           << UnicodeT::SPACE
           << node.getNodeValue()
           << UnicodeT::QUESTION_MARK
           << UnicodeT::GREATER_THAN_SIGN;
    break;
  case DOM::Node_base::COMMENT_NODE:
    stream << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::HYPHEN_MINUS
           << UnicodeT::HYPHEN_MINUS
           << node.getNodeValue()
           << UnicodeT::HYPHEN_MINUS
           << UnicodeT::HYPHEN_MINUS
           << UnicodeT::GREATER_THAN_SIGN;
    break;
  default: // keep GCC quiet
	  break;
  } // switch

  return stream;
} // operator<<

} // namespace DOM
} // namespace Arabica

#endif
