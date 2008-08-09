#ifndef CPPUNIT_TableTestResult_HPP
#define CPPUNIT_TableTestResult_HPP

#include "TextTestResult.h"

class TableTestResult : public TextTestResult
{
public:
    TableTestResult(const std::string& name, bool verbose) : TextTestResult(name, verbose) { }

    virtual void print(std::ostream& stream);
};
#endif