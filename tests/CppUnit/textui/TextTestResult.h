
#ifndef CPPUNIT_TEXTTESTRESULT_H
#define CPPUNIT_TEXTTESTRESULT_H

#include <iostream>
#include "../framework/TestResult.h"


class TextTestResult : public TestResult
{
public:
    TextTestResult(const std::string& name, bool verbose) : name_(name), verbose_(verbose) { }
    virtual void        addError      (Test *test, CppUnitException *e);
    virtual void        addFailure    (Test *test, CppUnitException *e);
    virtual void        addSkip       (Test *test, CppUnitException *e);
    virtual void        startTest     (Test *test);
    virtual void        print         (std::ostream& stream);
    virtual void        printErrors   (std::ostream& stream);
    virtual void        printFailures (std::ostream& stream);
    virtual void        printSkips    (std::ostream& stream);
    virtual void        printHeader   (std::ostream& stream);

protected:
  const std::string& name() const { return name_; }

private:
    std::string name_;
    bool verbose_;
};


/* insertion operator for easy output */
inline std::ostream& operator<< (std::ostream& stream, TextTestResult& result)
{ result.print (stream); return stream; }


#endif


