// DOMWriter.cpp : Defines the entry point for the application.
//

#pragma warning(disable: 4786 4250 4503)

#include <iostream>
#include <string>
#include <algorithm>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <XML/UnicodeCharacters.h>

template<typename char_type, typename traits_type>
class escaper
{
  private:
    typedef char_type charT;
    typedef traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef Unicode<charT> UnicodeT;

  public:
    escaper(ostreamT& stream) : stream_(stream) { }
    void operator()(charT ch)
    {
	    if(ch == UnicodeT::LESS_THAN_SIGN)
	    {
        stream_ << UnicodeT::AMPERSAND
                  << UnicodeT::LOWERCASE_L
                  << UnicodeT::LOWERCASE_T
                  << UnicodeT::SEMI_COLON;
	      return;
      } // if(ch == UnicodeT::LESS_THAN_SIGN)
      if(ch == UnicodeT::GREATER_THAN_SIGN)
	    {
        stream_ << UnicodeT::AMPERSAND
                 << UnicodeT::LOWERCASE_G
                 << UnicodeT::LOWERCASE_T
                 << UnicodeT::SEMI_COLON;
        return;
	    } // if(ch == UnicodeT::GREATER_THAN_SIGN)
      if(ch == UnicodeT::AMPERSAND)
	    {
        stream_ << UnicodeT::AMPERSAND
                 << UnicodeT::LOWERCASE_A
                 << UnicodeT::LOWERCASE_M
                 << UnicodeT::LOWERCASE_P
                 << UnicodeT::SEMI_COLON;
	      return;
      } // if(ch == case UnicodeT::AMPERSAND)
      if(ch == UnicodeT::QUOTATION_MARK)
	    {
        stream_ << UnicodeT::AMPERSAND
                 << UnicodeT::LOWERCASE_Q
                 << UnicodeT::LOWERCASE_U
                 << UnicodeT::LOWERCASE_O
                 << UnicodeT::LOWERCASE_T
                 << UnicodeT::SEMI_COLON;
        return;
	    } // if(ch == UnicodeT::QUOTATION_MARK)
      stream_ << ch;
    } // operator()

  private:
    ostreamT& stream_;
}; // escaper

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
  typedef Unicode<charT> UnicodeT;

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
    doChildren(stream, node);
    break;
  case DOM::Node<stringT>::ELEMENT_NODE:
    {
      stream << UnicodeT::LESS_THAN_SIGN << node.getNodeName();
      DOM::NamedNodeMap<stringT> attrs = node.getAttributes();
      for(unsigned int a = 0; a < attrs.getLength(); ++a)
      {
        DOM::Node<stringT> attr = attrs.item(a);
        stream << UnicodeT::SPACE 
               << attr.getNodeName()
               << UnicodeT::EQUALS_SIGN
               << UnicodeT::QUOTATION_MARK;
        stringT value = attr.getNodeValue();
        std::for_each(value.begin(), value.end(), escaper<charT, traitsT>(stream));
        stream << UnicodeT::QUOTATION_MARK;
      }
      stream << UnicodeT::GREATER_THAN_SIGN;
      doChildren(stream, node);
      stream << UnicodeT::LESS_THAN_SIGN << UnicodeT::SLASH << node.getNodeName() << UnicodeT::GREATER_THAN_SIGN;
    }
    break;
  case DOM::Node<stringT>::TEXT_NODE:
    {
      stringT value = node.getNodeValue();
      std::for_each(value.begin(), value.end(), escaper<charT, traitsT>(stream));
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
