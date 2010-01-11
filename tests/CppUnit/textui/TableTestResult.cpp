#include "TableTestResult.hpp"

void TableTestResult::print(std::ostream& stream)
{
  stream 
    << "\n"
    << name() << "\t"
    << runTests() << "\t"
    << testFailures() << "\t"
    << testErrors() << "\t"
    << testSkips();
} // print
