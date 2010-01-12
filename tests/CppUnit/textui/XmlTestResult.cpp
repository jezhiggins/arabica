#include "XmlTestResult.hpp"
#include "../framework/Test.h"

const int PASS = 0;
const int ERROR = 1;
const int FAIL = 2;
const int SKIP = 3;


void XmlTestResult::startTest(Test *test)
{
  TextTestResult::startTest(test);
  run_.push_back(test);
} // startTest

void XmlTestResult::addError(Test *test, CppUnitException *e)
{
  TextTestResult::addError(test, e);
  run_.back().e_ = e;
  run_.back().result_ = ERROR;
} // addError

void XmlTestResult::addFailure(Test *test, CppUnitException *e)
{
  TextTestResult::addFailure(test, e);
  run_.back().e_ = e;
  run_.back().result_ = FAIL;
} // addError

void XmlTestResult::addSkip(Test *test, CppUnitException *e)
{
  TextTestResult::addSkip(test, e);
  run_.back().e_ = e;
  run_.back().result_ = SKIP;
} // addError

void printException(std::ostream& stream,
		    const std::string& tag,
		    CppUnitException *e)
{
  stream << "<" << tag << " message='" << e->what() << "'>" 
	 << "line: " << e->lineNumber() << " "
	 << e->fileName() << " "
	 << "'" << e->what() << "'</" << tag << ">";
} // exception

void XmlTestResult::print(std::ostream& stream)
{
  stream << "<testsuite name='" << name() << "' tests='" << runTests() << "' skips='" << testSkips() << "' " << " failures='" << testFailures() << "' errors='" << testErrors() << "'>\n";
  for(std::vector<RunTest>::const_iterator r = run_.begin(), re = run_.end(); r != re; ++r)
  {
    stream << "  <testcase classname='" << name() << "' name='" << r->test_->name() << "'>";
    switch(r->result_)
    {
      case ERROR:
	printException(stream, "error", r->e_);
	break;
      case FAIL:
	printException(stream, "failure", r->e_);
	break;
      case SKIP:
	printException(stream, "skip", r->e_);
	break;               
    } 
    stream << "</testcase>\n";
  } 
         
  stream << "</testsuite>" << std::endl;

} // print
