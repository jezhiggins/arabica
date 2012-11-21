#ifdef _MSC_VER
#pragma warning(disable: 4250)
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"

#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"

#include <XSLT/XSLT.hpp>

//#include <elephant/newdelete.h>
//#include <elephant/memorymonitorholder.h>
//#include <elephant/leakdetector.h>
//#include <elephant/leakdisplayfunc.h>

#include <map>
#include <string> 

#include <fstream>

class Expected;

template<class string_type, class string_adaptor>
class Loader
{
public:
  Loader(); 
  ~Loader();

  TestSuite* XSLTTest_suite(const std::string& path);
  TestSuite* ArabicaTest_suite(const std::string& path);

private:
  Expected* expected_fails_;
  std::map<std::string, Arabica::DOM::Document<std::string> > catalogs_;

  Arabica::DOM::Document<std::string> loadCatalog(const std::string& catalog_filename);
  TestSuite* suite(const std::string& path, const std::string& catalog_filename);
};

#ifdef ARABICA_WINDOWS
const std::string PATH_PREFIX="../tests/XSLT/testsuite/TESTS/";
const std::string SEPERATOR = "/";
#else
#include "test_path.hpp"
const std::string PATH_PREFIX=test_path;
const std::string SEPERATOR = "/";
#endif
  
template<class string_type, class string_adaptor>
Arabica::DOM::Document<string_type, string_adaptor> buildDOM(const std::string& filename)
{
  Arabica::SAX::InputSource<string_type, string_adaptor> is(string_adaptor::construct(filename));
  Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
  parser.parse(is);       

  Arabica::DOM::Document<string_type, string_adaptor> d = parser.getDocument();
  if(d != 0)
    d.normalize();
  return d;
} // buildDOM

template<class string_type, class string_adaptor>
Arabica::DOM::Document<string_type, string_adaptor> buildDOMFromString(const std::string& xml)
{
  std::stringstream ss;
  ss << xml;
  Arabica::SAX::InputSource<string_type, string_adaptor> is(ss);

  Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
  parser.parse(is);       

  Arabica::DOM::Document<string_type, string_adaptor> d = parser.getDocument();
  if(d != 0)
    d.normalize();
  return d;
} // buildDOMFromString

std::string readFile(const std::string& filename)
{
  std::ifstream in(filename.c_str());
  std::string file = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  if((file[0] == (char)0xff) && (file[1] == (char)0xfe)) // UTF16 BOM
  {
    // this is absolutely not a sensible thing to do
    // in this case, I know it's ok for the test data but in the general case don't even think about it
    file.erase(0, 2);
    for(std::string::size_type i = file.length() - 1; i != std::string::npos; i -= 2)
      file.erase(i, 1);
  } // if ...
  if((file[0] == (char)0xef) && (file[1] == (char)0xbb) && (file[2] == (char)0xbf)) // UTF-8 BOM
    file.erase(0, 3);
  return file;
} // readFile

std::string readFragment(const std::string& filename)
{
  std::string frag = readFile(filename);
  if(frag.find("<?xml") == 0)
    frag.erase(0, frag.find("?>") + 2);

  return frag;
} // readFragment

template<class string_type, class string_adaptor>
Arabica::XPath::NodeSet<string_type, string_adaptor> selectNodes(const char* path, 
                                                                 const Arabica::DOM::Node<string_type, string_adaptor>& node)
{
  Arabica::XPath::XPath<string_type, string_adaptor> xpath;
  return xpath.evaluate(string_adaptor::construct(path), node).asNodeSet();
} // selectNodes

template<class string_type, class string_adaptor>
Arabica::DOM::Node<string_type, string_adaptor> selectNode(const char* path, 
                                           const Arabica::DOM::Node<string_type, string_adaptor>& node)
{
  return selectNodes(path, node)[0];
} // selectNode

std::string selectString(const std::string& path, const Arabica::DOM::Node<std::string>& node)
{
  Arabica::XPath::XPath<std::string> xpath;
  return xpath.evaluate_expr(path, node).asString();
} // selectString

std::string make_path(const std::string& path, const std::string& filename)
{
  return PATH_PREFIX + path + SEPERATOR + filename;
} // make_path

class SkipTest : public TestCase
{
public:
  SkipTest(const std::string& name, 
           const std::string& reason) :
    TestCase(name),
    reason_(reason)
  {
  } // SkipTest

protected:
  virtual void runTest()
  {
    throw SkipException(reason_);
  } // runTest

private:
  std::string reason_;
}; // class SkipTest

template<class string_type, class string_adaptor>
class CompileFailsTest : public TestCase
{
public:
  CompileFailsTest(const std::string& name,
                   const std::string& input_xslt,
                   const std::string& reason) :
    TestCase(name),
    input_xslt_(input_xslt),
    reason_(reason)
  {
  } // CompileFailsTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    Arabica::SAX::InputSource<string_type, string_adaptor> source(string_adaptor::construct(input_xslt_));
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() != 0)
      assertImplementation(false, "Expected " + input_xslt_ + " not to compile.  But it did :o");
    throw SkipException(reason_ + " : " + compiler.error());
  } // runTest

private:
  std::string input_xslt_;
  std::string reason_;
}; // CompileFailsTest

template<class string_type, class string_adaptor>
class RunFailsTest : public TestCase
{
public:
  RunFailsTest(const std::string& name,
               const std::string& input_xml,
               const std::string& input_xslt,
               const std::string& reason) :
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt),
    reason_(reason)
  {
  } // RunFailsTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    Arabica::SAX::InputSource<string_type, string_adaptor> source(string_adaptor::construct(input_xslt_));
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink<string_type, string_adaptor> output;
    stylesheet->set_output(output);

    std::basic_ostringstream<typename string_adaptor::value_type> errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<string_type, string_adaptor> document = buildDOM<string_type, string_adaptor>(input_xml_); 
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      throw SkipException(reason_ + " : " + e.what());
    }
    assertImplementation(false, "Expected " + input_xslt_ + " to fail to execute.  But it did :o");
  } // runTest

private:
  std::string input_xml_;
  std::string input_xslt_;
  std::string reason_;
}; // RunFailsTest

template<class string_type, class string_adaptor>
class ExecutionErrorTest : public TestCase
{
public:
  ExecutionErrorTest(const std::string& name,
                     const std::string& input_xml,
                     const std::string& input_xslt) :
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt)
  {
  } // ExecutionErrorTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    string_type input = string_adaptor::construct(input_xslt_);
    Arabica::SAX::InputSource<string_type, string_adaptor> source(input);
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      return;

    Arabica::XSLT::DOMSink<string_type, string_adaptor> output;
    stylesheet->set_output(output);

    std::basic_ostringstream<typename string_adaptor::value_type> errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<string_type, string_adaptor> document = buildDOM<string_type, string_adaptor>(input_xml_); 
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception&) {
      return;
    }
    assertImplementation(false, "Marked in catalog.xml as an execution error, but actually ran.");
  } // runTest

private:
  std::string input_xml_;
  std::string input_xslt_;
}; // ExecutionErrorTest

template<class string_type, class string_adaptor>
class CompareAsTextXSLTTest : public TestCase
{
public:
  CompareAsTextXSLTTest(const std::string& name,
                        const std::string& input_xml,
                        const std::string& input_xslt,
                        const std::string& output_xml) :
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt),
    output_xml_(output_xml)
  {
  } // CompareAsTextXSLTTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    Arabica::SAX::InputSource<string_type, string_adaptor> source(string_adaptor::construct(input_xslt_));
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    std::basic_ostringstream<typename string_adaptor::value_type> xml_output;
    Arabica::XSLT::StreamSink<string_type, string_adaptor> output(xml_output);
    stylesheet->set_output(output);

    std::basic_ostringstream<typename string_adaptor::value_type> errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<string_type, string_adaptor> document = buildDOM<string_type, string_adaptor>(input_xml_);
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      assertImplementation(false, "Failed to run " + input_xslt_ + " : " + e.what());
    } // catch

    std::string ref = readFile(output_xml_);
    std::string out = string_adaptor::asStdString(string_adaptor::construct(xml_output.str()));

    if(ref == out)
      return;

    std::string refs = trimXMLDecl(ref);
    std::string outs = trimXMLDecl(out);

    if(refs == outs)
      return;

    refs = stripWhitespace(refs);
    outs = stripWhitespace(outs);
    
    if(refs == outs)
      return;

    assertImplementation(false, "Expected text:\n" + ref + "\nbut got:\n" + out + "\n" + refs + "\nbut got:" + outs + "\n=====");
  } // runTest

private:
  std::string stripWhitespace(const std::string& str)
  {
    std::string s = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(str);
    
    std::string::size_type i = s.find("> ");
    while(i != std::string::npos)
    {
      s.erase(i+1, 1); 
      i = s.find("> ");
    } // while ..

    i = s.find(" <");
    while(i != std::string::npos)
    {
      s.erase(i, 1);
      i = s.find(" <");
    } // while ..

    return s;
  } // stripWhitespace
  
  std::string trimXMLDecl(const std::string& str)
  {
    if(str.find("<?") != 0)
      return str;

    return str.substr(str.find("?>") + 2);
  } // trimXMLDecl

  std::string input_xml_;
  std::string input_xslt_;
  std::string output_xml_;
}; // class CompareAsTextXSLTTest

template<class string_type, class string_adaptor>
class CompareAsXMLFragmentXSLTTest : public TestCase
{
public:
  CompareAsXMLFragmentXSLTTest(const std::string& name,
                   const std::string& input_xml,
                   const std::string& input_xslt,
                   const std::string& output_xml) : 
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt),
    output_xml_(output_xml)
  { 
  } // 

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    Arabica::SAX::InputSource<string_type, string_adaptor> source(string_adaptor::construct(input_xslt_));
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink<string_type, string_adaptor> output;
    stylesheet->set_output(output);

    std::basic_ostringstream<typename string_adaptor::value_type> errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<string_type, string_adaptor> document = buildDOM<string_type, string_adaptor>(input_xml_); 
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      assertImplementation(false, "Failed to run " + input_xslt_ + " : " + e.what());
    }

    std::string refStr = "<wrapper>" + readFragment(output_xml_) + "</wrapper>";
    Arabica::DOM::Document<string_type, string_adaptor> refDoc = buildDOMFromString<string_type, string_adaptor>(refStr);
    if(refDoc == 0)
      assertImplementation(false, "Couldn't read " + output_xml_ + ". Perhaps it isn't well-formed XML?");
    Arabica::DOM::DocumentFragment<string_type, string_adaptor> ref = refDoc.createDocumentFragment();
    for(Arabica::DOM::Node<string_type, string_adaptor> n = refDoc.getDocumentElement().getFirstChild(); n != 0; n = refDoc.getDocumentElement().getFirstChild())
      ref.appendChild(n);
    
    Arabica::DOM::Node<string_type, string_adaptor> out = output.node();
    out.normalize();
 
    std::string refs = docToString(ref);
    std::string outs = docToString(out);

    if(refs == outs)
      return;

    stripWhitespace(ref);
    stripWhitespace(out);
    std::string refs2 = docToString(ref);
    std::string outs2 = docToString(out);

    if(refs2 == outs2)
      return;

    assertImplementation(false, "Expected XML frag:\n" + refs + "\nbut got:\n" + outs + "\n=====\n" + refs2 + "\nbut:\n" + outs2 + "\n\n====\n\n");
  } // runTest

  std::string docToString(Arabica::DOM::Node<string_type, string_adaptor> node)
  {
    std::basic_ostringstream<typename string_adaptor::value_type> ss;
    ss << node;
    string_type streamed = string_adaptor::construct(ss.str());
    streamed = Arabica::text::normalize_whitespace<string_type, string_adaptor>(streamed);
    return string_adaptor::asStdString(streamed);
  } // docToString

  void stripWhitespace(Arabica::DOM::Node<string_type, string_adaptor> doc)
  {
    Arabica::XPath::NodeSet<string_type, string_adaptor> textNodes = selectNodes<string_type, string_adaptor>("//text()", doc);
    for(size_t i = 0; i != textNodes.size(); ++i)
    {
      Arabica::DOM::Node<string_type, string_adaptor> t = textNodes[i];
      string_type text = t.getNodeValue();
      text = Arabica::text::normalize_whitespace<string_type, string_adaptor>(text);
      size_t index = string_adaptor::find(text, Arabica::text::Unicode<typename string_adaptor::value_type>::SPACE);
      while(index != string_adaptor::npos())
      {
        text = string_adaptor::concat(string_adaptor::substr(text, 0, index), string_adaptor::substr(text, index+1));
        index = string_adaptor::find(text, Arabica::text::Unicode<typename string_adaptor::value_type>::SPACE);
      }
      t.setNodeValue(text);
      if(string_adaptor::length(text) == 0)
	      t.getParentNode().removeChild(t);
    }
  } // stripWhitespace

  std::string input_xml_;
  std::string input_xslt_;
  std::string output_xml_;
}; // class CompareAsXMLFragment

template<class string_type, class string_adaptor>
class StandardXSLTTest : public TestCase
{
public:
  StandardXSLTTest(const std::string& name,
                   const std::string& input_xml,
                   const std::string& input_xslt,
                   const std::string& output_xml) : 
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt),
    output_xml_(output_xml)
  { 
  } // StandardXSLTTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler<string_type, string_adaptor> compiler;

    Arabica::SAX::InputSource<string_type, string_adaptor> source(string_adaptor::construct(input_xslt_));
    std::auto_ptr<Arabica::XSLT::Stylesheet<string_type, string_adaptor> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink<string_type, string_adaptor> output;
    stylesheet->set_output(output);

    std::basic_ostringstream<typename string_adaptor::value_type> errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<string_type, string_adaptor> document = buildDOM<string_type, string_adaptor>(input_xml_); 
    if(document == 0)
      assertImplementation(false, "Couldn't read " + input_xml_ + ". Perhaps it isn't well-formed XML?");
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      assertImplementation(false, "Failed to run " + input_xslt_ + " : " + e.what());
    }

    Arabica::DOM::Document<string_type, string_adaptor> ref = buildDOM<string_type, string_adaptor>(output_xml_);
    if(ref == 0)
      assertImplementation(false, "Couldn't read " + output_xml_ + ". Perhaps it isn't well-formed XML?");
    Arabica::DOM::Node<string_type, string_adaptor> out = output.node();
    out.normalize();

    std::string refs = docToString(ref);
    std::string outs = docToString(out);

    if(refs == outs)
      return;

    stripWhitespace(ref);
    stripWhitespace(out);
    std::string refs2 = docToString(ref);
    std::string outs2 = docToString(out);

    if(refs2 == outs2)
      return;

    assertImplementation(false, "Expected XML:\n" + refs + "\nbut got:\n" + outs);
  } // runTest

  std::string docToString(Arabica::DOM::Node<string_type, string_adaptor> node)
  {
    std::basic_ostringstream<typename string_adaptor::value_type> ss;
    ss << node;
    string_type streamed = string_adaptor::construct(ss.str());
    streamed = Arabica::text::normalize_whitespace<string_type, string_adaptor>(streamed);
    std::string xml = string_adaptor::asStdString(streamed);
    if(xml.find("<?xml version=\"1.0\"?> ") == 0)
      xml.replace(0, 22, "");
    return xml;
  } // docToString

  void stripWhitespace(Arabica::DOM::Node<string_type, string_adaptor> doc)
  {
    Arabica::XPath::NodeSet<string_type, string_adaptor> textNodes = selectNodes<string_type, string_adaptor>("//text()", doc);
    for(size_t i = 0; i != textNodes.size(); ++i)
    {
      Arabica::DOM::Node<string_type, string_adaptor> t = textNodes[i];
      string_type text = t.getNodeValue();
      text = Arabica::text::normalize_whitespace<string_type, string_adaptor>(text);
      size_t index = string_adaptor::find(text, Arabica::text::Unicode<typename string_adaptor::value_type>::SPACE);
      while(index != string_adaptor::npos())
      {
        text = string_adaptor::concat(string_adaptor::substr(text, 0, index), string_adaptor::substr(text, index+1));
        index = string_adaptor::find(text, Arabica::text::Unicode<typename string_adaptor::value_type>::SPACE);
      }
      t.setNodeValue(text);
    }
  } // stripWhitespace

  std::string input_xml_;
  std::string input_xslt_;
  std::string output_xml_;
}; // class StandardXSLTTest

class Expected 
{
public:
  Expected() : loaded_(false) { }

  bool loaded() const { return loaded_; }

  void load()
  {
    if(loaded_)
      return;

    std::cerr << "Loaded expected fails" << std::endl;
    Arabica::DOM::Document<std::string> fail_doc = buildDOM<std::string, Arabica::default_string_adaptor<std::string> >(PATH_PREFIX + "arabica-expected-fails.xml");
    Arabica::XPath::NodeSet<std::string> failcases = selectNodes<std::string, Arabica::default_string_adaptor<std::string> >("/test-suite/test-case", fail_doc);
    for(size_t i = 0; i != failcases.size(); ++i)
    {
      std::string name = selectString("@id", failcases[i]);
      std::string compiles = selectString("@compiles", failcases[i]);
      std::string runs = selectString("@runs", failcases[i]);
      std::string skip = selectString("@skip", failcases[i]);
      std::string reason = selectString("@reason", failcases[i]);
      std::string compare = selectString("@compare",  failcases[i]);

      if(compiles == "no")
        fails_[name] = "compile";
      else if(runs == "no")
        fails_[name] = "run";
      else if(skip == "yes")
        fails_[name] = "skip";
      else if(compare == "text")
        fails_[name] = "text";
      else if(compare == "fragment")
        fails_[name] = "fragment";
      reasons_[name] = reason;
    } // for ...
    loaded_ = true;
  } // load

  std::map<std::string, std::string>& Fails() { return fails_; }
  std::map<std::string, std::string>& Reasons() { return reasons_; }

private:
  std::map<std::string, std::string> fails_;
  std::map<std::string, std::string> reasons_;
  bool loaded_;
}; // class Expected


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
template<class string_type, class string_adaptor>
Loader<string_type, string_adaptor>::Loader() :
  expected_fails_(new Expected())
{ 
  expected_fails_->load();
} // Loader

template<class string_type, class string_adaptor>
Loader<string_type, string_adaptor>::~Loader()
{
  delete expected_fails_;
} // ~Loader

template<class string_type, class string_adaptor>
Arabica::DOM::Document<std::string> Loader<string_type, string_adaptor>::loadCatalog(const std::string& catalog_filename)
{
  Arabica::DOM::Document<std::string> c = catalogs_[catalog_filename];
  if(c == 0)
  {
    std::cerr << "Loading " << catalog_filename << std::endl;
    c = buildDOM<std::string, Arabica::default_string_adaptor<std::string> >(PATH_PREFIX + catalog_filename);
    catalogs_[catalog_filename] = c;
  } // if(c == 0)

  return c;
} // catalog

template<class string_type, class string_adaptor>
TestSuite* Loader<string_type, string_adaptor>::suite(const std::string& path, const std::string& catalog_filename)
{
  Arabica::DOM::Document<std::string> catalog = loadCatalog(catalog_filename);
  
  TestSuite *suiteOfTests = new TestSuite;

  std::string testNamesSelector = "/test-suite/test-catalog/test-case[file-path='" + path + "']";
  Arabica::XPath::NodeSet<std::string> tests = 
      selectNodes<std::string, Arabica::default_string_adaptor<std::string> >(testNamesSelector.c_str(), catalog);
  std::cerr << "There are " << tests.size() << " " << path << " tests." << std::endl;
  for(size_t i = 0; i != tests.size(); ++i)
  {
    std::string operation = selectString("scenario/@operation", tests[i]);
    std::string name = selectString("@id", tests[i]);
    std::string path = selectString("concat(../major-path, '" + SEPERATOR + "', file-path)", tests[i]);
    std::string out_path = selectString("concat(../major-path, '" + SEPERATOR + "REF_OUT" + SEPERATOR + "', file-path)", tests[i]);
    std::string input_xml = selectString(".//input-file[@role='principal-data']", tests[i]);
    std::string input_xslt = selectString(".//input-file[@role='principal-stylesheet']", tests[i]);
    std::string output_xml = selectString(".//output-file[@role='principal']", tests[i]);

    if(expected_fails_->Fails().find(name) == expected_fails_->Fails().end())
    {
      if(operation == "execution-error")
        suiteOfTests->addTest(new ExecutionErrorTest<string_type, string_adaptor>(name, 
                                                     make_path(path, input_xml), 
                                                     make_path(path, input_xslt)));
      else 
        suiteOfTests->addTest(new StandardXSLTTest<string_type, string_adaptor>(name, 
                                                   make_path(path, input_xml), 
                                                   make_path(path, input_xslt), 
                                                   make_path(out_path, output_xml)));
    }
    else if(expected_fails_->Fails()[name] == "compile") 
      suiteOfTests->addTest(new CompileFailsTest<string_type, string_adaptor>(name, 
                                                 make_path(path, input_xslt),
                                                 expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "run")
      suiteOfTests->addTest(new RunFailsTest<string_type, string_adaptor>(name, 
                                             make_path(path, input_xml), 
                                             make_path(path, input_xslt),
                                             expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "skip")
      suiteOfTests->addTest(new SkipTest(name, expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "text")
      suiteOfTests->addTest(new CompareAsTextXSLTTest<string_type, string_adaptor>(name, 
                                                      make_path(path, input_xml),
                                                      make_path(path, input_xslt),
                                                      make_path(out_path, output_xml)));
    else if(expected_fails_->Fails()[name] == "fragment")
      suiteOfTests->addTest(new CompareAsXMLFragmentXSLTTest<string_type, string_adaptor>(name, 
                                                      make_path(path, input_xml),
                                                      make_path(path, input_xslt),
                                                      make_path(out_path, output_xml)));
  } // for ...

  return suiteOfTests;
} // suite

template<class string_type, class string_adaptor>
TestSuite* Loader<string_type, string_adaptor>::XSLTTest_suite(const std::string& path)
{
  return suite(path, "catalog.xml");
} // XSLTTest_suite

template<class string_type, class string_adaptor>
TestSuite* Loader<string_type, string_adaptor>::ArabicaTest_suite(const std::string& path)
{
  return suite(path, "arabica-catalog.xml");
} // ArabicaTest_suite

std::set<std::string> parse_tests_to_run(int argc, const char* argv[]);

template<class string_type, class string_adaptor>
void add_tests(TestRunner& runner, Loader<string_type, string_adaptor>& loader, const std::set<std::string>& wanted, const char** test_names);
template<class string_type, class string_adaptor>
void add_arabica_tests(TestRunner& runner, Loader<string_type, string_adaptor>& loader, const std::set<std::string>& wanted, const char** test_names);

const char* xalan_tests[] = {"attribvaltemplate", "axes", "boolean", "conditional", 
                             "conflictres", "copy", "dflt", "expression", "extend", 
                             /*"idkey",*/ "impincl", "lre", "match", "math", 
                             "mdocs", "message", "modes", "namedtemplate", 
                             "namespace", "node", /*"numberformat",*/ /*"numbering",*/
                             "output", "position", "predicate", "processorinfo", "reluri",
                             "select", "sort", "string", "variable", "ver", "whitespace", 0};

const char* msft_tests[] = { "AVTs", /*"AttributeSets",*/ "Attributes", "BVTs", 
                             "Comment", "Completeness", "ConflictResolution", "Copying", 
                             "Elements", "Errors", "Fallback", "ForEach", /*"FormatNumber",*/
                             "ForwardComp", "Import", "Keys", "Messages", 
                             "Miscellaneous", "Modes", "NamedTemplates", "Namespace",
                             "Namespace-alias", "Namespace_XPath", /*"Number",*/
                             /*"Output",*/ "ProcessingInstruction", "RTF", "Sorting", 
                             "Stylesheet", "Template", "Text",  "Valueof",
                             "Variables", "Whitespaces", "XSLTFunctions", 0 };

const char* arabica_tests[] = { "attributes",
                                "errors", "include", "processing-instruction", 
                                "stylesheet", "text", "variables", 0 };

template<class string_type, class string_adaptor>
bool XSLT_test_suite(int argc, const char* argv[])
{
  TestRunner runner;
  std::set<std::string> tests_to_run = parse_tests_to_run(argc, argv);

  // runner.addTest("ScopeTest", ScopeTest_suite<string_type, string_adaptor>());

  Loader<string_type, string_adaptor> loader;

  //add_tests(runner, loader, tests_to_run, xalan_tests);
  //add_tests(runner, loader, tests_to_run, msft_tests);
  add_arabica_tests(runner, loader, tests_to_run, arabica_tests);

  return runner.run(argc, argv);
}  // XSLT_test_suite

std::set<std::string> parse_tests_to_run(int argc, const char* argv[])
{
  std::set<std::string> tests;
  for(int a = 1; a != argc; ++a)
    if(argv[a][0] != '-')
      tests.insert(argv[a]);
    else
    {
      if(std::string(argv[a]) == "-log")
	      ++a; // skip next
    } // if ...
     
  return tests;
} // tests_to_run

template<class string_type, class string_adaptor>
void add_tests(TestRunner& runner, Loader<string_type, string_adaptor>& loader, const std::set<std::string>& wanted, const char** test_names)
{
  std::set<std::string>::const_iterator end = wanted.end();
  while(*test_names != 0)
  {
    if(wanted.empty() || (wanted.find(*test_names) != end))
      runner.addTest(*test_names, loader.XSLTTest_suite(*test_names));
    ++test_names;
  } // while ...
} // all_all_tests

template<class string_type, class string_adaptor>
void add_arabica_tests(TestRunner& runner, Loader<string_type, string_adaptor>& loader, const std::set<std::string>& wanted, const char** test_names)
{
  std::set<std::string>::const_iterator end = wanted.end();
  while(*test_names != 0)
  {
    if(wanted.empty() || (wanted.find(*test_names) != end))
      runner.addTest(*test_names, loader.ArabicaTest_suite(*test_names));
    ++test_names;
  } // while ...
} // all_all_tests
