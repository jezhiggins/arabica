#ifndef CPPUNIT_XmlTestResult_HPP
#define CPPUNIT_XmlTestResult_HPP

#include "TextTestResult.h"

class XmlTestResult : public TextTestResult
{
public:
  XmlTestResult(const std::string& name, bool verbose) : TextTestResult(name, verbose) { }

  virtual void print(std::ostream& stream);
}; // XmlTestResult

#endif
