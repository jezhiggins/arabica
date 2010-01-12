#ifndef ARABICA_TEST_RUNNER_HPP
#define ARABICA_TEST_RUNNER_HPP

#include "../CppUnit/framework/Test.h"
#include <vector>

class TestRunner
{
protected:
  bool m_wait;
  bool verbose_;
  std::vector<std::pair<std::string,Test *> > m_mappings;
  std::string logprefix_;

public:
  TestRunner() : m_wait(false), verbose_(false) {}
  ~TestRunner();

  bool run(int ac, const char **av);
  void addTest(std::string name, Test *test)
  { m_mappings.push_back(std::make_pair(name, test)); }
}; // TestRunner;

#endif
