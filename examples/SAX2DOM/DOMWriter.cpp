// DOMWriter.cpp : Defines the entry point for the application.
//

#pragma warning(disable: 4786 4250 4503)

#include <iostream>
#include <string>
#include <DOM/SAX2DOM/SAX2DOM.h>

template<class stringT, class charT, class traitsT>
void doChildren(std::basic_ostream<charT, traitsT>& stream, DOM::Node<stringT>& node)
{
  DOM::Node<stringT> child = node.getFirstChild();
  while(child != 0)
  {
    stream << child;
    child = child.getNextSibling();
  } // while 
} // doChildren


template<class stringT, class charT, class traitsT>
std::basic_ostream<charT, traitsT>&
operator<<(std::basic_ostream<charT, traitsT>& stream,
           DOM::Node<stringT>& node)
{
  switch(node.getNodeType())
  {
  case DOM::Node<stringT>::DOCUMENT_NODE:
    doChildren(stream, node);
    break;
  case DOM::Node<stringT>::ELEMENT_NODE:
    stream << "<" << node.getNodeName() << ">";
    doChildren(stream, node);
    stream << "</" << node.getNodeName() << ">";
    break;
  case DOM::Node<stringT>::TEXT_NODE:
    stream << node.getNodeValue();
    break;
  } // switch

  return stream;
} // operator<<

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)

  SAX2DOM::Parser<std::string> domParser;

	for(int i = 1; i < argc; ++i)
  {
    std::string file(argv[i]);
    SAX::InputSource is;
    is.setSystemId(file);

    if(file != "-")
      domParser.parse(is);
    else
    {
      is.setSystemId("stdin");
      is.setByteStream(std::cin);

      domParser.parse(is);
    } // if(file != "-")

    DOM::Document<std::string> doc = domParser.getDocument();

    std::cout << doc;
  } // for ...
  
  return 0;
} // main

// end of file
