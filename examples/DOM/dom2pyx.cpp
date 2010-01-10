
#include <string>
#include <iostream>
#include <DOM/SAX2DOM/SAX2DOM.hpp>

void generate_pyx(Arabica::DOM::Element<std::string> element);
std::string escape(const std::string& str);

int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)

  Arabica::SAX2DOM::Parser<std::string> domParser;

  for(int i = 1; i < argc; ++i)
  {
    std::string file(argv[i]);
    Arabica::SAX::InputSource<std::string> is;
    is.setSystemId(file);
    domParser.parse(is);

    Arabica::DOM::Document<std::string> doc = domParser.getDocument();
    if(doc == 0)
    {
      std::cerr << "Error parsing " << file << std::endl;
      continue;
    }

    generate_pyx(doc.getDocumentElement());
  } 

  return 0;
} // main

void generate_pyx(Arabica::DOM::Element<std::string> element)
{
  std::cout << '(' << element.getNodeName() << std::endl;

  if(element.hasAttributes())
  {
    Arabica::DOM::NamedNodeMap<std::string> attrs = element.getAttributes();
    for(size_t a = 0; a != attrs.getLength(); ++a)
    {
      Arabica::DOM::Node<std::string> attr = attrs.item(a);
      std::cout << 'A' << attr.getNodeName() 
                << ' ' << escape(attr.getNodeValue()) 
                << std::endl;
    } // for ...
  } // if ...  

  for(Arabica::DOM::Node<std::string> n = element.getFirstChild(); n != 0; n = n.getNextSibling())
  {
    switch(n.getNodeType())
    {
      case Arabica::DOM::Node<std::string>::ELEMENT_NODE:
        generate_pyx(static_cast<Arabica::DOM::Element<std::string> >(n));
        break;
      case Arabica::DOM::Node<std::string>::TEXT_NODE:
      case Arabica::DOM::Node<std::string>::CDATA_SECTION_NODE:
        std::cout << '-' << escape(n.getNodeValue()) << std::endl;
        break;
      case Arabica::DOM::Node<std::string>::PROCESSING_INSTRUCTION_NODE:
        std::cout << '?' << n.getNodeName() 
                  << ' ' << n.getNodeValue() << std::endl;
        break;
    } // switch ...
  } // for ...

  std::cout << ')' << element.getNodeName() << std::endl;
} // generate_pyx

std::string escape(const std::string& str)
{
  std::string estr(str);
  std::string::size_type i(estr.find("\n"));
  while(i != std::string::npos)
  {
    estr.replace(i, 1, "\\n", 2);
    i = estr.find("\n", i);
  } // while ...
  return estr;
} // escape

// end of file
