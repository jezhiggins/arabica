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
  iconvert_adaptor<char> ia(std::cin);
  oconvert_adaptor<char> oa(std::cout);

  //ia.imbue(std::locale(ia.getloc(), new base64codecvt()));
  //oa.imbue(std::locale(oa.getloc(), new base64codecvt()));
  while(ia)
  {
    oa << static_cast<char>(ia.get());
    oa.flush();
  } // while
    
	return 0;
} // main

