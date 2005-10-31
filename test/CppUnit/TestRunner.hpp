#ifndef ARABICA_TEST_RUNNER_HPP
#define ARABICA_TEST_RUNNER_HPP

#include "../CppUnit/framework/Test.h"
#include <vector>

class TestRunner
{
protected:
	bool m_wait;
	std::vector<std::pair<std::string,Test *> > m_mappings;

public:
	TestRunner() : m_wait(false) {}
	~TestRunner();

	void run(int ac, const char **av);
	void addTest(std::string name, Test *test)
	{ m_mappings.push_back(std::make_pair(name, test)); }

protected:
	void run(Test *test);
	void printBanner();
}; // TestRunner;

#endif
