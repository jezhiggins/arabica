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
//  SAX2DOM::Parser<std::wstring> domParser;
//  SAX::wInputSource is;
//  ... load instance from somewhere ...
//  domParser.parse(is);
//  DOM::Document<std::wstring> doc = domParser.getDocument();
//  ... manipulate doc ...
//  std::wcout << doc;  
//
///////////////////////////////////////////////////////////////////////
// $Id$
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <XML/UnicodeCharacters.h>
#include <XML/escaper.hpp>

namespace DOM
{

  namespace StreamImpl
  {
    template<class stringT, class charT, class traitsT>
    void streamChildren(std::basic_ostream<charT, traitsT>& stream, DOM::Node<stringT>& node)
    {
      DOM::Node<stringT> child = node.getFirstChild();
      while(child != 0)
      {
        stream << child;
        child = child.getNextSibling();
      } // while 
    } // streamChildren
  } // namespace StreamImpl

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
} // prefix_is_declared

template<class stringT, class charT, class traitsT>
void check_and_output_node_name(std::basic_ostream<charT, traitsT>& stream, 
                                DOM::Node<stringT>& node, 
                                std::vector<std::map<stringT, stringT> >* prefix_stack)
{
  std::map<stringT, stringT>& current = *(prefix_stack->rbegin());

  stringT namespaceURI = node.getNamespaceURI();
  if(!namespaceURI.empty())
  {
    std::pair<bool, stringT> prefix = is_uri_declared(prefix_stack, namespaceURI);
    
    if(!prefix.first)
      current[namespaceURI] =  prefix.second = node.getPrefix();

    if(!prefix.second.empty())
      stream << prefix.second << Arabica::Unicode<charT>::COLON;
    stream << node.getLocalName();
  }
  else
    stream << node.getNodeName();
} // check_and_output_node_name

template<class stringT, class charT>
bool isXmlns(const stringT& str)
{
  typedef Arabica::Unicode<charT> UnicodeT;

  if(str.size() != 5)
    return false;

  if((str[0] == UnicodeT::LOWERCASE_X) &&
     (str[1] == UnicodeT::LOWERCASE_M) &&
     (str[2] == UnicodeT::LOWERCASE_L) &&
     (str[3] == UnicodeT::LOWERCASE_N) &&
     (str[4] == UnicodeT::LOWERCASE_S))
    return true;
  return false;
} // isXmlns

template<class stringT, class charT, class traitsT>
int prefix_mapper(std::basic_ostream<charT, traitsT>& stream,
                   DOM::Node<stringT>& node)
{
  typedef Arabica::Unicode<charT> UnicodeT;

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

    std::map<stringT, stringT> prefixes;
    for(DOM::Node<stringT> p = node.getParentNode(); p.getNodeType() == DOM::Node_base::ELEMENT_NODE; p = p.getParentNode())
    {
      if(p.getNamespaceURI().empty())
        continue;
      if(prefixes.find(p.getNamespaceURI()) == prefixes.end())
        prefixes[p.getNamespaceURI()] = p.getPrefix();
    } // for ...

    prefix_stack->push_back(prefixes);
  } // if ...

  std::map<stringT, stringT>& current = *(prefix_stack->rbegin());

  // is element namespace URI declared?
  check_and_output_node_name(stream, node, prefix_stack);
  
  DOM::NamedNodeMap<stringT> attrs = node.getAttributes();
  std::vector<stringT> names;
  for(unsigned int a = 0; a < attrs.getLength(); ++a)
    names.push_back(attrs.item(a).getNodeName());
  std::sort(names.begin(), names.end());

  for(typename std::vector<stringT>::const_iterator a = names.begin(), ae = names.end(); a != ae; ++a)
  {
    DOM::Node<stringT> attr = attrs.getNamedItem(*a);
    if(isXmlns<stringT, charT>(attr.getNodeName()) || 
       isXmlns<stringT, charT>(attr.getPrefix()))
      continue;
    stream << UnicodeT::SPACE;
    check_and_output_node_name(stream, attr, prefix_stack);
    stream  << UnicodeT::EQUALS_SIGN
            << UnicodeT::QUOTATION_MARK;
    stringT value = attr.getNodeValue();
    std::for_each(value.begin(), value.end(), Arabica::XML::attribute_escaper<charT, traitsT>(stream));
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
    if(!(i->second.empty()))
      stream << UnicodeT::COLON << i->second;
    stream << UnicodeT::EQUALS_SIGN << UnicodeT::QUOTATION_MARK;
    std::for_each(i->first.begin(), i->first.end(), Arabica::XML::attribute_escaper<charT, traitsT>(stream));
    stream << UnicodeT::QUOTATION_MARK;
  } // for ...

  return index;
} // prefix_mapper

template<class stringT, class charT, class traitsT>
void prefix_mapper_pop(std::basic_ostream<charT, traitsT>& stream,
                       DOM::Node<stringT> node,
                       int index)
{
  std::vector<std::map<stringT, stringT> >* prefix_stack = 
    static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));

  check_and_output_node_name(stream, node, prefix_stack);

  prefix_stack->pop_back();
  if(prefix_stack->empty())
  {
    delete static_cast<std::vector<std::map<stringT, stringT> >*>(stream.pword(index));
    stream.pword(index) = 0;
  } // if ...
} // prefix_mapper_pop

template<class stringT, class charT, class traitsT>
std::basic_ostream<charT, traitsT>&
operator<<(std::basic_ostream<charT, traitsT>& stream,
           DOM::Node<stringT>& node)
{
  typedef Arabica::Unicode<charT> UnicodeT;

  switch(node.getNodeType())
  {
  case DOM::Node<stringT>::DOCUMENT_NODE:
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
    StreamImpl::streamChildren(stream, node);
    break;
  case DOM::Node<stringT>::ELEMENT_NODE:
    {
      stream << UnicodeT::LESS_THAN_SIGN;
      int index = prefix_mapper(stream, node);
      stream << UnicodeT::GREATER_THAN_SIGN;
      StreamImpl::streamChildren(stream, node);
      stream << UnicodeT::LESS_THAN_SIGN << UnicodeT::SLASH;
      prefix_mapper_pop(stream, node, index);
      stream << UnicodeT::GREATER_THAN_SIGN;
    }
    break;
  case DOM::Node<stringT>::TEXT_NODE:
    {
      stringT value = node.getNodeValue();
      std::for_each(value.begin(), value.end(), Arabica::XML::text_escaper<charT, traitsT>(stream));
    }
    break;
  case DOM::Node<stringT>::ENTITY_REFERENCE_NODE:
    stream << UnicodeT::AMPERSAND
           << node.getNodeName()
           << UnicodeT::SEMI_COLON;
    break;
  case DOM::Node<stringT>::CDATA_SECTION_NODE:
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
  case DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE:
    stream << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::QUESTION_MARK
           << node.getNodeName()
           << UnicodeT::SPACE
           << node.getNodeValue()
           << UnicodeT::QUESTION_MARK
           << UnicodeT::GREATER_THAN_SIGN;
    break;
  case DOM::Node<stringT>::COMMENT_NODE:
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
#endif
