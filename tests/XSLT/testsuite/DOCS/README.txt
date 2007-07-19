Prototype XSLT/XPath 1.0 Conformance Test Suite

I. Introduction

This package is the complete test suite created by the OASIS
XSLT / XPath Conformance Technical Committee.  Its purpose is to
provide tests and tools from which to build a test harness for a
specific XSLT processor, running on a particular platform.  Note
that we have not provided a complete test harness here.

This test suite covers all of XSLT 1.0 and XPath 1.0, and consists
of 3173 tests.

II. Package Contents

There are 3 top-level directories -- DOCS, TESTS and TOOLS.

DOCS: -- documentation
    README.txt -- this document
    HowToSub.htm -- details about the catalog format (long)
    LabGuide.htm -- partly-completed document about using the test
      suite, which can be examined for ideas and suggestions
    xsltcfg.htm -- definition of all scenarios, compares, and other
      values that may occur in the catalog
    xsltcfg.xml -- raw configuration data
    xsltDevQ.htm -- questionnaire for XSLT implementer to provide
      data about what they chose for each discretionary item
    xsltdisc.htm -- master list of discretionary items in XSLT/XPath
      (explains <discretionary> elements in catalog)
DOCS/Background contains additional information about the XSLT/XPath
      Test Regime, for those who want to know more about it.

TESTS: -- contains all test subdirectories
    MSFT_Conformance_Tests
    Xalan_Conformance_Tests
    The catalog.xml and doubts.xml files are explained below.

TOOLS: -- tools and scripts
    README.txt -- tools documentation
    infoset.xsl -- stylesheet to convert output to standard form
    mkfinder.xsl -- stylesheet to exercise the XSLT processor you
      use to transform the catalog.xml and doubts.xml in your lab

III. How to Use the Tests

A. Creating a test script

You will run the tests using a test harness (if you have one), or with a test
script.  You can use the catalog file, catalog.xml, in the TESTS directory.
Use it as sources of filenames to create the script, or to create a control file
for the test harness.  The format of the catalog files is simple, and you can
use a stylesheet, or your favorite scripting language, to process it. See the
mkfinder.xsl stylesheet (provided in TOOLS) for an example of a stylesheet that
transforms catalog.xml into a script. If each test-case element is a "line item"
in your script, then the scenario element identifies the syntax needed for that
line item. The "standard" scenario is where a stylesheet is invoked against an
XML document and is expected to succeed and produce output.

B. Running the tests

To run the script, you need to decide where the output from the test will be
stored.  The two usual choices are to put them in amongst the tests themselves,
or to create a separate output subdirectory.  One other issue to be careful
about is to make sure your XSLT processor is executing in the proper directory
for each test. The file-path element in the catalog can be used to create
output subdirectories, in addition to being used to locate the test inputs.

C. Checking your output

XML Documents may be logically equivalent without being physically identical.
(See Canonical XML 1.0, http://www.w3.org/TR/2001/REC- xml-c14n-20010315, and
its errata, http://www.w3.org/2001/03/C14N-errata for more details.) We
have provided reference output files in the REF_OUT subdirectories.  In order
to check that test output matches the reference files, it will be necessary to
convert both your output and the reference files to a standard form.  We have
provided a simple stylesheet, infoset.xsl, which produces standardized (very
expanded) output.  There are also publicly available tools that create
canonical XML.  You must use one of these tools in order to do meaningful
output comparisons.  See README.txt in the TOOLS subdirectory for one source
of freely available XML and HTML canonicalizers.

IV. Issues

The tests provided by this testsuite have been used extensively by various
organizations, and are believed to be accurate.  All doubts and issues that
were brought to our attention through April 2005 are cataloged in doubts.xml,
which can be combined with catalog.xml for additional filtering. We suggest
that you make a working copy of doubts.xml and add any additional issues or
annotations you need.

====================================================================
Copyright (C) The Organization for the Advancement of
Structured Information Standards [OASIS] (2001). All Rights Reserved.

This document and translations of it may be copied and furnished to
others, and derivative works that comment on or otherwise explain it or
assist in its implementation may be prepared, copied, published and
distributed, in whole or in part, without restriction of any kind,
provided that the above copyright notice and this paragraph are included
on all such copies and derivative works. However, this document itself
may not be modified in any way, such as by removing the copyright notice
or references to OASIS, except as needed for the purpose of developing
OASIS specifications, in which case the procedures for copyrights
defined in the OASIS Intellectual Property Rights document must be
followed, or as required to translate it into languages
other than English.

The limited permissions granted above are perpetual and
will not be revoked by OASIS or its successors or assigns.

This document and the information contained herein is provided on an
"AS IS" basis and OASIS DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.


