#ifndef CPPUNIT_XmlTestResult_HPP
#define CPPUNIT_XmlTestResult_HPP

#include "TextTestResult.h"
#include <vector>

class XmlTestResult : public TextTestResult
{
public:
  XmlTestResult(const std::string& name, bool verbose) : TextTestResult(name, verbose) { }

  virtual void startTest(Test *test);
  virtual void addError(Test *test, CppUnitException *e);
  virtual void addFailure(Test *test, CppUnitException *e);
  virtual void addSkip(Test *test, CppUnitException *e);
  virtual void print(std::ostream& stream);

private:
  struct RunTest
  {
    Test* test_;
    CppUnitException *e_;
    int result_;

    RunTest(Test* test) :
      test_(test),
      e_(0),
      result_(0) 
    {
    } // RunTest

    RunTest(const RunTest& rhs) :
      test_(rhs.test_),
      e_(rhs.e_),
      result_(rhs.result_)
    {
    } // RunTest

    RunTest& operator=(const RunTest& rhs)
    {
      test_ = rhs.test_;
      e_ = rhs.e_;
      result_ = rhs.result_;
      return *this;
    } // operator=
  };

  std::vector<RunTest> run_;
  
}; // XmlTestResult

#endif
