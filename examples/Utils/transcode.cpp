// transcode.cpp 
//
#include <iostream>
#include <Utils/convert_adaptor.h>
#include <Utils/utf8iso88591codecvt.h>
#include <Utils/iso88591utf8codecvt.h>
#include <Utils/rot13codecvt.h>
#include <Utils/base64codecvt.h>
#include <Utils/utf8ucs2codecvt.h>
#include <Utils/utf16utf8codecvt.h>
#include <Utils/utf16beucs2codecvt.h>
#include <Utils/utf16leucs2codecvt.h>

using namespace Arabica::convert;

typedef iconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > Widener;
typedef oconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > Narrower;

iconvert_adaptor<char> iByteConvertor(std::cin);
Widener iCharAdaptor(iByteConvertor);

oconvert_adaptor<char> oByteConvertor(std::cout);
Narrower oCharAdaptor(oByteConvertor);

void imbueCodecvts(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
  imbueCodecvts(argc, argv);

  int count = 0;
  wchar_t c = iCharAdaptor.get();
  while(!iCharAdaptor.eof())
  {
    oCharAdaptor << c;

    if(count == 1024)
    {
      oCharAdaptor.flush();
      oByteConvertor.flush();
      count = 0;
    } // if ... 

    c = iCharAdaptor.get();
  }
  oCharAdaptor.flush();
  oByteConvertor.flush();
  
  return 0;
} // main

void imbueCodecvts(int argc, const char* argv[])
{
  oCharAdaptor.imbue(std::locale(oCharAdaptor.getloc(), new utf16beucs2codecvt()));

  for(int i = 1; i < argc; ++i)
  {
    std::string io(argv[i]);

    bool input = true;
    if(io == "-i" || io == "--input")
      input = true;
    else if(io == "-o" || io == "--output")
      input = false;
    else
    {
      std::cerr << argv[0] << " [(-i|--input) input-encoding] [(-o|--output) output-encoding] " << std::endl;
      std::exit(0);
    } // 
  
    ++i;
    if(i >= argc)
    {
      std::cerr << argv[0] << " [(-i|--input) input-encoding] [(-o|--output) output-encoding] " << std::endl;
      std::exit(0);
    } // 

    std::string cvt(argv[i]);
    if(input)
    {
      if(cvt == "rot13")
        iByteConvertor.imbue(std::locale(iByteConvertor.getloc(), new rot13codecvt()));
      else if(cvt == "base64")
        iByteConvertor.imbue(std::locale(iByteConvertor.getloc(), new base64codecvt()));
      else if(cvt == "utf8")
        iCharAdaptor.imbue(std::locale(iCharAdaptor.getloc(), new utf8ucs2codecvt()));
      else if(cvt == "utf16be")
        iCharAdaptor.imbue(std::locale(iCharAdaptor.getloc(), new utf16beucs2codecvt()));
      else if(cvt == "utf16le")
        iCharAdaptor.imbue(std::locale(iCharAdaptor.getloc(), new utf16leucs2codecvt()));
      else
      {
        std::cerr << cvt << " is not a valid input encoding." << std::endl;
        std::exit(0);
      }
    }
    else
    {
      if(cvt == "rot13")
        oByteConvertor.imbue(std::locale(oByteConvertor.getloc(), new rot13codecvt()));
      else if(cvt == "base64")
        oByteConvertor.imbue(std::locale(oByteConvertor.getloc(), new base64codecvt()));
      else if(cvt == "utf8")
        oCharAdaptor.imbue(std::locale(oCharAdaptor.getloc(), new utf8ucs2codecvt()));
      else if(cvt == "utf16be")
        oCharAdaptor.imbue(std::locale(oCharAdaptor.getloc(), new utf16beucs2codecvt()));
      else if(cvt == "utf16le")
        oCharAdaptor.imbue(std::locale(oCharAdaptor.getloc(), new utf16leucs2codecvt()));
      else 
      {
        std::cerr << cvt << " is not a valid output encoding." << std::endl;
        std::exit(0);
      }
    } 
  } // for ...
} // imbueCodeCvts

