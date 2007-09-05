#ifndef XSLT_XSLT_TEST_HPP
#define XSLT_XSLT_TEST_HPP

#include <SAX/InputSource.hpp>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <DOM/Utils/Stream.hpp>
#include <XSLT/XSLT.hpp>
#include <Utils/normalize_whitespace.hpp>

#ifdef ARABICA_WINDOWS
const std::string PATH_PREFIX="../tests/XSLT/testsuite/TESTS/";
const std::string SEPERATOR = "/";
#else
#include "test_path.hpp"
const std::string PATH_PREFIX=test_path;
const std::string SEPERATOR = "/";
#endif
  
Arabica::DOM::Document<std::string> buildDOM(const std::string& filename)
{
  Arabica::SAX::InputSource is(filename);
  Arabica::SAX2DOM::Parser<std::string> parser;
  parser.parse(is);       

  Arabica::DOM::Document<std::string> d = parser.getDocument();
  if(d != 0)
    d.normalize();
  return d;
} // buildDOM

Arabica::XPath::NodeSet<std::string> selectNodes(const std::string& path, const Arabica::DOM::Node<std::string>& node)
{
  Arabica::XPath::XPath<std::string> xpath;
  return xpath.evaluate(path, node)->asNodeSet();
} // selectNodes

Arabica::DOM::Node<std::string> selectNode(const std::string& path, const Arabica::DOM::Node<std::string>& node)
{
  return selectNodes(path, node)[0];
} // selectNode

std::string selectString(const std::string& path, const Arabica::DOM::Node<std::string>& node)
{
  Arabica::XPath::XPath<std::string> xpath;
  return xpath.evaluate_expr(path, node)->asString();
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

class CompileFailsTest : public TestCase
{
public:
  CompileFailsTest(const std::string& name,
                   const std::string& input_xslt) :
    TestCase(name),
    input_xslt_(input_xslt)
  {
  } // CompileFailsTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() != 0)
      assertImplementation(false, "Expected " + input_xslt_ + " not to compile.  But it did :o");
    throw SkipException(compiler.error());
  } // runTest

private:
  std::string input_xslt_;
}; // CompileFailsTest

class RunFailsTest : public TestCase
{
public:
  RunFailsTest(const std::string& name,
               const std::string& input_xml,
               const std::string& input_xslt) :
    TestCase(name),
    input_xml_(input_xml),
    input_xslt_(input_xslt)
  {
  } // RunFailsTest

protected:
  virtual void runTest()
  {
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink output;
    stylesheet->set_output(output);

    std::ostringstream errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::string> document = buildDOM(input_xml_); 
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      throw SkipException(e.what());
    }
    assertImplementation(false, "Expected " + input_xslt_ + " to fail to execute.  But it did :o");
  } // runTest

private:
  std::string input_xml_;
  std::string input_xslt_;
}; // RunFailsTest

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
  virtual void  runTest()
  {
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink output;
    stylesheet->set_output(output);

    std::ostringstream errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::string> document = buildDOM(input_xml_); 
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      assertImplementation(false, "Failed to run " + input_xslt_ + " : " + e.what());
    }

    Arabica::DOM::Document<std::string> ref = buildDOM(output_xml_);
    if(ref == 0)
      assertImplementation(false, "Couldn't read " + output_xml_ + ". Perhaps it isn't well-formed XML?");
    Arabica::DOM::Node<std::string> out = output.node();

    std::string refs = docToString(ref.getFirstChild());
    std::string outs = docToString(out.getFirstChild());

    if(refs != outs)
    {
      stripWhitespace(ref);
      stripWhitespace(out);
      std::string refs2 = docToString(ref.getFirstChild());
      std::string outs2 = docToString(out.getFirstChild());
      if(refs2 != outs2)
        assertImplementation(false, "Expected:\n" + refs + "\nbut got:\n" + outs);
    }
  } // runTest

  std::string docToString(Arabica::DOM::Node<std::string> node)
  {
    std::ostringstream ss;
    ss << node;
    return Arabica::string::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(ss.str());
  } // docToString

  void stripWhitespace(Arabica::DOM::Node<std::string> doc)
  {
    Arabica::XPath::NodeSet<std::string> textNodes = selectNodes("//text()", doc);
    for(int i = 0; i != textNodes.size(); ++i)
    {
      Arabica::DOM::Node<std::string> t = textNodes[i];
      std::string text = t.getNodeValue();
      size_t index = text.find_first_of(" \n");
      while(index != std::string::npos)
      {
        text.replace(index, 1, "");
        index = text.find_first_of(" \n");
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
  Expected() 
  {
    Arabica::DOM::Document<std::string> fail_doc = buildDOM(PATH_PREFIX + "arabica-expected-fails.xml");
    Arabica::XPath::NodeSet<std::string> failcases = selectNodes("/test-suite/test-case", fail_doc);
    for(int i = 0; i != failcases.size(); ++i)
    {
      std::string name = selectString("@id", failcases[i]);
      std::string compiles = selectString("@compiles", failcases[i]);
      std::string runs = selectString("@runs", failcases[i]);
      std::string skip = selectString("@skip", failcases[i]);
      std::string reason = selectString("@reason", failcases[i]);

      if(compiles == "no")
        fails[name] = "compile";
      else if(runs == "no")
        fails[name] = "run";
      else if(skip == "yes")
      {
        fails[name] = "skip";
        skips[name] = reason;
      }
    } // for ...
  } 

  std::map<std::string, std::string>& Fails() { return fails; }
  std::map<std::string, std::string>& Skips() { return skips; }

private:
  std::map<std::string, std::string> fails;
  std::map<std::string, std::string> skips;
};

static Expected expected;

TestSuite* XSLTTest_suite(const std::string& path)
{
  static Arabica::DOM::Document<std::string> catalog = buildDOM(PATH_PREFIX  + "catalog.xml");
  
  TestSuite *suiteOfTests = new TestSuite;

  Arabica::XPath::NodeSet<std::string> tests = 
//        selectNodes("/test-suite/test-catalog/test-case[scenario/@operation='standard']", catalog);
//        selectNodes("/test-suite/test-catalog/test-case[@id='boolean_boolean86']", catalog);
        selectNodes("/test-suite/test-catalog/test-case[scenario/@operation='standard' and file-path='" + path + "']", catalog);
  for(int i = 0; i != tests.size(); ++i)
  {
    std::string name = selectString("@id", tests[i]);
    std::string path = selectString("concat(../major-path, '" + SEPERATOR + "', file-path)", tests[i]);
    std::string out_path = selectString("concat(../major-path, '" + SEPERATOR + "REF_OUT" + SEPERATOR + "', file-path)", tests[i]);
    std::string input_xml = selectString(".//input-file[@role='principal-data']", tests[i]);
    std::string input_xslt = selectString(".//input-file[@role='principal-stylesheet']", tests[i]);
    std::string output_xml = selectString(".//output-file[@role='principal']", tests[i]);

    if(expected.Fails().find(name) == expected.Fails().end())
      suiteOfTests->addTest(new StandardXSLTTest(name, 
                                                 make_path(path, input_xml), 
                                                 make_path(path, input_xslt), 
                                                 make_path(out_path, output_xml)));
    else if(expected.Fails()[name] == "compile") 
      suiteOfTests->addTest(new CompileFailsTest(name, 
                                                 make_path(path, input_xslt)));
    else if(expected.Fails()[name] == "run")
      suiteOfTests->addTest(new RunFailsTest(name, 
                                             make_path(path, input_xml), 
                                             make_path(path, input_xslt)));
    else if(expected.Fails()[name] == "skip")
      suiteOfTests->addTest(new SkipTest(name, expected.Skips()[name]));
  } // for ...

	return suiteOfTests;
} // XSLTTest_suitoo

#endif
