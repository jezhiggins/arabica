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

int main(int argc, const char* argv[])
{
  Arabica::convert::iconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > ia(std::cin);
  Arabica::convert::oconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char, std::char_traits<char> > oa(std::cout);

  ia.imbue(std::locale(ia.getloc(), new Arabica::convert::utf8ucs2codecvt()));
  oa.imbue(std::locale(oa.getloc(), new Arabica::convert::utf16beucs2codecvt()));
  while(ia)
  {
    oa << static_cast<wchar_t>(ia.get());
    oa.flush();
  } // while
    
	return 0;
} // main

