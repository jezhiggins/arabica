

#include "TextTestResult.h"
#include "../framework/CppUnitException.h"
#include "../framework/estring.h"

using namespace std;

void TextTestResult::addError (Test *test, CppUnitException *e)
{
    TestResult::addError (test, e);
    if(verbose_)
      cerr << "E" << endl;

}

void TextTestResult::addFailure (Test *test, CppUnitException *e)
{
    TestResult::addFailure (test, e);
    if(verbose_)
      cerr << "F" << endl;
}

void TextTestResult::addSkip (Test *test, CppUnitException *e)
{
  TestResult::addSkip (test, e);
  cerr << "S" << endl;
}

void TextTestResult::startTest (Test *test)
{
    TestResult::startTest (test);
    if(verbose_)
      cerr << ".";
}


void TextTestResult::printErrors (ostream& stream)
{
    if (testErrors () != 0) {

        if (testErrors () == 1)
            stream << "There was " << testErrors () << " error: " << endl;
        else
            stream << "There were " << testErrors () << " errors: " << endl;

        int i = 1;

        for (vector<TestFailure *>::iterator it = errors ().begin (); it != errors ().end (); ++it) {
            TestFailure             *failure    = *it;
            CppUnitException        *e          = failure->thrownException ();

            stream << i 
                   << ") "
                   << "line: " << (e ? estring (e->lineNumber ()) : "") << " "
                   << (e ? e->fileName () : "") << " "
                   << "\"" << failure->thrownException ()->what () << "\""
                   << endl;
            i++;
        }
    }

}

void TextTestResult::printFailures (ostream& stream) 
{
    if (testFailures () != 0) {
        if (testFailures () == 1)
            stream << "There was " << testFailures () << " failure: " << endl;
        else
            stream << "There were " << testFailures () << " failures: " << endl;

        int i = 1;

        for (vector<TestFailure *>::iterator it = failures ().begin (); it != failures ().end (); ++it) {
            TestFailure             *failure    = *it;
            CppUnitException        *e          = failure->thrownException ();

            stream << i 
                   << ") "
                   << "line: " << (e ? estring (e->lineNumber ()) : "") << " "
                   << (e ? e->fileName () : "") << " "
                   << "\"" << failure->thrownException ()->what () << "\""
                   << endl;
            i++;
        }
    }

}

void TextTestResult::printSkips (ostream& stream) 
{
    if (testSkips () != 0) {
        if (testSkips () == 1)
            stream << "There was " << testSkips () << " skip: " << endl;
        else
            stream << "There were " << testSkips () << " skips: " << endl;

        int i = 1;

        for (vector<TestFailure *>::iterator it = skips ().begin (); it != skips ().end (); ++it) {
            TestFailure             *skip     = *it;
            CppUnitException        *e          = skip ->thrownException ();

            stream << i 
                   << ") "
                   << "line: " << (e ? estring (e->lineNumber ()) : "") << " "
                   << (e ? e->fileName () : "") << " "
                   << "\"" << skip->thrownException ()->what () << "\""
                   << endl;
            i++;
        }
    }

}

void TextTestResult::print (ostream& stream) 
{
    printHeader (stream);
    printErrors (stream);
    printFailures (stream);
    printSkips (stream);
    if(verbose_ || !wasSuccessful())
      cout << endl;
}


void TextTestResult::printHeader (ostream& stream)
{
    if (wasSuccessful ())
    {
      if(verbose_)
      {
        if(testSkips())
          cout << endl << "OK (" << runTests () << " tests, with " << testSkips() << " skips)" << endl;
      else
        cout << endl << "OK (" << runTests () << " tests)" << endl;
      }
    }
    else
        cout << endl
             << "!!!FAILURES!!!" << endl
             << "Test Results:" << endl
             << "Run:  "
             << runTests ()
             << "   Failures: "
             << testFailures ()
             << "   Errors: "
             << testErrors ()
             << "   Skips: "
             << testSkips ()
             << endl;

}
