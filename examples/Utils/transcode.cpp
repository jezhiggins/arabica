// transcode.cpp 
//
#include <iostream>
#include <Utils/convert_adaptor.h>
#include <Utils/utf8iso88591codecvt.h>
#include <Utils/iso88591utf8codecvt.h>
#include <Utils/rot13codecvt.h>
#include <Utils/utf8ucs2codecvt.h>
#include <Utils/utf16utf8codecvt.h>
#include <Utils/utf16beucs2codecvt.h>
#include <Utils/utf16leucs2codecvt.h>

int main(int argc, const char* argv[])
{
  iconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char> ia(std::cin);
  oconvert_adaptor<wchar_t, std::char_traits<wchar_t>, char> oa(std::cout);

  oa.imbue(std::locale(oa.getloc(), new utf16leucs2codecvt()));

  while(ia)
  {
    oa << static_cast<wchar_t>(ia.get());
    oa.flush();
  } // while
    
	return 0;
} // main

