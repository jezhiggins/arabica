#ifdef _MSC_VER
#pragma warning(disable: 4250)
#endif


#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"

#include "xslt_test.hpp"
#include <XSLT/XSLT.hpp>

//#include <elephant/newdelete.h>
//#include <elephant/memorymonitorholder.h>
//#include <elephant/leakdetector.h>
//#include <elephant/leakdisplayfunc.h>

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
  Arabica::SAX::InputSource<std::string> is(filename);
  Arabica::SAX2DOM::Parser<std::string> parser;
  parser.parse(is);       

  Arabica::DOM::Document<std::string> d = parser.getDocument();
  if(d != 0)
    d.normalize();
  return d;
} // buildDOM

Arabica::DOM::Document<std::string> buildDOMFromString(const std::string& xml)
{
  std::stringstream ss;
  ss << xml;
  Arabica::SAX::InputSource<std::string> is(ss);

  Arabica::SAX2DOM::Parser<std::string> parser;
  parser.parse(is);       

  Arabica::DOM::Document<std::string> d = parser.getDocument();
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

Arabica::XPath::NodeSet<std::string> selectNodes(const std::string& path, const Arabica::DOM::Node<std::string>& node)
{
  Arabica::XPath::XPath<std::string> xpath;
  return xpath.evaluate(path, node).asNodeSet();
} // selectNodes

Arabica::DOM::Node<std::string> selectNode(const std::string& path, const Arabica::DOM::Node<std::string>& node)
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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() != 0)
      assertImplementation(false, "Expected " + input_xslt_ + " not to compile.  But it did :o");
    throw SkipException(reason_ + " : " + compiler.error());
  } // runTest

private:
  std::string input_xslt_;
  std::string reason_;
}; // CompileFailsTest

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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
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
      throw SkipException(reason_ + " : " + e.what());
    }
    assertImplementation(false, "Expected " + input_xslt_ + " to fail to execute.  But it did :o");
  } // runTest

private:
  std::string input_xml_;
  std::string input_xslt_;
  std::string reason_;
}; // RunFailsTest

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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      return;

    Arabica::XSLT::DOMSink output;
    stylesheet->set_output(output);

    std::ostringstream errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::string> document = buildDOM(input_xml_); 
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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    std::ostringstream xml_output;
    Arabica::XSLT::StreamSink output(xml_output);
    stylesheet->set_output(output);

    std::ostringstream errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::string> document = buildDOM(input_xml_);
    try {
      stylesheet->execute(document);
    }
    catch(const std::exception& e) {
      assertImplementation(false, "Failed to run " + input_xslt_ + " : " + e.what());
    } // catch

    std::string ref = readFile(output_xml_);
    std::string out = xml_output.str();

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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
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

    std::string refStr = "<wrapper>" + readFragment(output_xml_) + "</wrapper>";
    Arabica::DOM::Document<std::string> refDoc = buildDOMFromString(refStr);
    if(refDoc == 0)
      assertImplementation(false, "Couldn't read " + output_xml_ + ". Perhaps it isn't well-formed XML?");
    Arabica::DOM::DocumentFragment<std::string> ref = refDoc.createDocumentFragment();
    for(Arabica::DOM::Node<std::string> n = refDoc.getDocumentElement().getFirstChild(); n != 0; n = refDoc.getDocumentElement().getFirstChild())
      ref.appendChild(n);
    
    Arabica::DOM::Node<std::string> out = output.node();
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

  std::string docToString(Arabica::DOM::Node<std::string> node)
  {
    std::ostringstream ss;
    ss << node;
    return Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(ss.str());
  } // docToString

  void stripWhitespace(Arabica::DOM::Node<std::string> doc)
  {
    Arabica::XPath::NodeSet<std::string> textNodes = selectNodes("//text()", doc);
    for(size_t i = 0; i != textNodes.size(); ++i)
    {
      Arabica::DOM::Node<std::string> t = textNodes[i];
      std::string text = t.getNodeValue();
      text = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(text);
      size_t index = text.find_first_of(" ");
      while(index != std::string::npos)
      {
        text.replace(index, 1, "");
        index = text.find_first_of(" ");
      }
      t.setNodeValue(text);
      if(text.length() == 0)
	t.getParentNode().removeChild(t);
    }
  } // stripWhitespace

  std::string input_xml_;
  std::string input_xslt_;
  std::string output_xml_;
}; // class CompareAsXMLFragment

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
    Arabica::XSLT::StylesheetCompiler compiler;

    Arabica::SAX::InputSource<std::string> source(input_xslt_);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
      assertImplementation(false, "Failed to compile " + input_xslt_ + " : " + compiler.error());

    Arabica::XSLT::DOMSink output;
    stylesheet->set_output(output);

    std::ostringstream errors;
    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::string> document = buildDOM(input_xml_); 
    if(document == 0)
      assertImplementation(false, "Couldn't read " + input_xml_ + ". Perhaps it isn't well-formed XML?");
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

  std::string docToString(Arabica::DOM::Node<std::string> node)
  {
    std::ostringstream ss;
    ss << node;
    std::string xml = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(ss.str());
    if(xml.find("<?xml version=\"1.0\"?> ") == 0)
      xml.replace(0, 22, "");
    return xml;
  } // docToString

  void stripWhitespace(Arabica::DOM::Node<std::string> doc)
  {
    Arabica::XPath::NodeSet<std::string> textNodes = selectNodes("//text()", doc);
    for(size_t i = 0; i != textNodes.size(); ++i)
    {
      Arabica::DOM::Node<std::string> t = textNodes[i];
      std::string text = t.getNodeValue();
      text = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(text);
      size_t index = text.find_first_of(" ");
      while(index != std::string::npos)
      {
        text.replace(index, 1, "");
        index = text.find_first_of(" ");
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
    Arabica::DOM::Document<std::string> fail_doc = buildDOM(PATH_PREFIX + "arabica-expected-fails.xml");
    Arabica::XPath::NodeSet<std::string> failcases = selectNodes("/test-suite/test-case", fail_doc);
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
Loader::Loader() :
  expected_fails_(new Expected())
{ 
  expected_fails_->load();
} // Loader

Loader::~Loader()
{
  delete expected_fails_;
} // ~Loader

Arabica::DOM::Document<std::string> Loader::loadCatalog(const std::string& catalog_filename)
{
  Arabica::DOM::Document<std::string> c = catalogs_[catalog_filename];
  if(c == 0)
  {
    std::cerr << "Loading " << catalog_filename << std::endl;
    c = buildDOM(PATH_PREFIX + catalog_filename);
    catalogs_[catalog_filename] = c;
  } // if(c == 0)

  return c;
} // catalog

TestSuite* Loader::suite(const std::string& path, const std::string& catalog_filename)
{
  Arabica::DOM::Document<std::string> catalog = loadCatalog(catalog_filename);
  
  TestSuite *suiteOfTests = new TestSuite;

  Arabica::XPath::NodeSet<std::string> tests = 
      selectNodes("/test-suite/test-catalog/test-case[file-path='" + path + "']", catalog);
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
        suiteOfTests->addTest(new ExecutionErrorTest(name, 
                                                     make_path(path, input_xml), 
                                                     make_path(path, input_xslt)));
      else 
        suiteOfTests->addTest(new StandardXSLTTest(name, 
                                                   make_path(path, input_xml), 
                                                   make_path(path, input_xslt), 
                                                   make_path(out_path, output_xml)));
    }
    else if(expected_fails_->Fails()[name] == "compile") 
      suiteOfTests->addTest(new CompileFailsTest(name, 
                                                 make_path(path, input_xslt),
                                                 expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "run")
      suiteOfTests->addTest(new RunFailsTest(name, 
                                             make_path(path, input_xml), 
                                             make_path(path, input_xslt),
                                             expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "skip")
      suiteOfTests->addTest(new SkipTest(name, expected_fails_->Reasons()[name]));
    else if(expected_fails_->Fails()[name] == "text")
      suiteOfTests->addTest(new CompareAsTextXSLTTest(name, 
                                                      make_path(path, input_xml),
                                                      make_path(path, input_xslt),
                                                      make_path(out_path, output_xml)));
    else if(expected_fails_->Fails()[name] == "fragment")
      suiteOfTests->addTest(new CompareAsXMLFragmentXSLTTest(name, 
                                                      make_path(path, input_xml),
                                                      make_path(path, input_xslt),
                                                      make_path(out_path, output_xml)));
  } // for ...

  return suiteOfTests;
} // suite

TestSuite* Loader::XSLTTest_suite(const std::string& path)
{
  return suite(path, "catalog.xml");
} // XSLTTest_suite

TestSuite* Loader::ArabicaTest_suite(const std::string& path)
{
  return suite(path, "arabica-catalog.xml");
} // ArabicaTest_suite

