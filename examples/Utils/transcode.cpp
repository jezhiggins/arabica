// transcode.cpp 
//
// Warning!  Contains ifdef hackery 
// 
///////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable: 4244 4996)
#endif

#include <iostream>
#include <io/convert_adaptor.hpp>
#include <convert/utf8iso88591codecvt.hpp>
#include <convert/iso88591utf8codecvt.hpp>
#include <convert/rot13codecvt.hpp>
#include <convert/base64codecvt.hpp>
#include <convert/utf8ucs2codecvt.hpp>
#include <convert/utf16utf8codecvt.hpp>
#include <convert/utf16beucs2codecvt.hpp>
#include <convert/utf16leucs2codecvt.hpp>

#include <fstream>
std::ifstream inputFile;
std::ofstream outputFile;

using namespace Arabica::io;
using namespace Arabica::convert;

iconvert_adaptor<char> iByteConvertor(std::cin);
oconvert_adaptor<char> oByteConvertor(std::cout);
bool needWCharIntermediary = false;

#ifndef ARABICA_NO_WCHAR_T
typedef iconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > Widener;
typedef oconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > Narrower;

Widener iCharAdaptor(iByteConvertor);
Narrower oCharAdaptor(oByteConvertor);
#endif 

void wchar_transcode();
void byte_transcode();
bool processArgs(int argc, const char* argv[]);
bool imbueInput(int& argn, int argc, const char* argv[]);
bool imbueOutput(int& argn, int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
  if(!processArgs(argc, argv))
  {
    std::cerr << argv[0] << "\n"
              << "  [(-ie|--input-encoding) input-encoding]\n" 
              << "  [(-oe|--output-encoding) output-encoding]\n" 
              << "  [(-i|--input) input-filename]\n"
              << "  [(-o|--output) output-filename]"
              << std::endl;
    return 0;
  }

  if(needWCharIntermediary)
    wchar_transcode();
  else
    byte_transcode();

  return 0;
} // main

void wchar_transcode()
{
#ifndef ARABICA_NO_WCHAR_T
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
#endif
} // wchar_transcode

void byte_transcode()
{
  int count = 0;
  char c = iByteConvertor.get();
  while(!iByteConvertor.eof())
  {
    oByteConvertor << c;

    if(count == 1024)
    {
      oByteConvertor.flush();
      count = 0;
    } // if ... 

    c = iByteConvertor.get();
  } // while

  oByteConvertor.flush();
} // byte_transcode

bool processArgs(int argc, const char* argv[])
{
  for(int i = 1; i < argc; ++i)
  {
    std::string io(argv[i]);

    if(io == "-ie" || io == "--input-encoding") 
    {
      if(!(imbueInput(i, argc, argv)))
        return false;
    }
    else if(io == "-oe" || io == "--output-encoding") 
    {
      if(!(imbueOutput(i, argc, argv)))
        return false;
    }
    else if(io == "-i" || io == "--input")
    {
      ++i;
      if(i >= argc)
        return false;
      inputFile.open(argv[i], std::ios_base::in | std::ios_base::binary);
      iByteConvertor.set_stream(inputFile);
    }  
    else if(io == "-o" || io == "--output")
    {
      ++i;
      if(i >= argc)
        return false;
      outputFile.open(argv[i], std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
      oByteConvertor.set_stream(outputFile);
    }  
    else
      return false;
  }
  return true;
} // processArgs

template<class Facet>
std::locale addFacet(const std::locale& base, Facet* facet)
{
#ifndef ARABICA_VS6_WORKAROUND
  return std::locale(base, facet);
#else
  return std::locale(std::_Addfac(base, facet));
#endif
} // addFacet
  
bool imbueInput(int& argn, int argc, const char* argv[])
{
  ++argn;
  if(argn >= argc)
    return false;

  std::string cvt(argv[argn]);

  if(cvt == "rot13")
    iByteConvertor.imbue(addFacet(iByteConvertor.getloc(), new rot13codecvt()));
  else if(cvt == "base64")
    iByteConvertor.imbue(addFacet(iByteConvertor.getloc(), new base64codecvt()));
#ifndef ARABICA_NO_WCHAR_T
  else if(cvt == "utf8")
    iCharAdaptor.imbue(addFacet(iCharAdaptor.getloc(), new utf8ucs2codecvt()));
  else if(cvt == "utf16be")
    iCharAdaptor.imbue(addFacet(iCharAdaptor.getloc(), new utf16beucs2codecvt()));
  else if(cvt == "utf16le")
    iCharAdaptor.imbue(addFacet(iCharAdaptor.getloc(), new utf16leucs2codecvt()));
#endif
  else
  {
    std::cerr << cvt << " is not a valid input encoding." << std::endl;
    return false;
  }

#ifndef ARABICA_NO_WCHAR_T
  if((cvt == "utf8") || 
      (cvt == "utf16be") || 
      (cvt == "utf16le"))
    needWCharIntermediary = true;
#endif

  return true;
} // imbueInput

bool imbueOutput(int& argn, int argc, const char* argv[])
{
  ++argn;
  if(argn >= argc)
    return false;

  std::string cvt(argv[argn]);
  if(cvt == "rot13")
    oByteConvertor.imbue(addFacet(oByteConvertor.getloc(), new rot13codecvt()));
  else if(cvt == "base64")
    oByteConvertor.imbue(addFacet(oByteConvertor.getloc(), new base64codecvt()));
#ifndef ARABICA_NO_WCHAR_T
  else if(cvt == "utf8")
    oCharAdaptor.imbue(addFacet(oCharAdaptor.getloc(), new utf8ucs2codecvt()));
  else if(cvt == "utf16be")
    oCharAdaptor.imbue(addFacet(oCharAdaptor.getloc(), new utf16beucs2codecvt()));
  else if(cvt == "utf16le")
    oCharAdaptor.imbue(addFacet(oCharAdaptor.getloc(), new utf16leucs2codecvt()));
#endif
  else 
  {
    std::cerr << cvt << " is not a valid output encoding." << std::endl;
    return false;
  }

#ifndef ARABICA_NO_WCHAR_T
    if((cvt == "utf8") || 
       (cvt == "utf16be") || 
       (cvt == "utf16le"))
      needWCharIntermediary = true;
#endif

  return true;
} // imbueOutputs

