#ifndef XSLT_XSLT_TEST_HPP
#define XSLT_XSLT_TEST_HPP

#include <map>
#include <string> 

#include <SAX/InputSource.hpp>
#include <SAX/Attributes.hpp>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <DOM/io/Stream.hpp>
#include <fstream>

class Expected;

class Loader
{
public:
  Loader(); 
  ~Loader();

  TestSuite* XSLTTest_suite(const std::string& path);
  TestSuite* ArabicaTest_suite(const std::string& path);

private:
  Expected* expected_fails_;
  std::map<std::string, Arabica::DOM::Document<std::string> > catalogs_;

  Arabica::DOM::Document<std::string> loadCatalog(const std::string& catalog_filename);
  TestSuite* suite(const std::string& path, const std::string& catalog_filename);
};

#endif
