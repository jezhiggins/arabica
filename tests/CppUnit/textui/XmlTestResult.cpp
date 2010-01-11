#include "XmlTestResult.hpp"

void XmlTestResult::print(std::ostream& stream)
{
  stream << "<testsuite tests='" << runTests() << "' skips='" << testSkips() << "' " << " failures='" << testFailures() << "' errors='" << testErrors() << "'>\n"
         
         << "</testsuite>";

} // print
