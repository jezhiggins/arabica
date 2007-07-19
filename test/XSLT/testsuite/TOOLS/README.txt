Checking your XSLT processor that you use for utility purposes

The MkFinder.xsl stylesheet is an example of a stylesheet that extracts
data from the test-case catalog and produces a text file that can be
executed as a script. In fact, this is the exact script that was used to
check that the files listed in the catalog are present in the directory
tree as shipped. (There are a couple entries for IDontExist.xml that will
be reported as missing. See doubts.xml for reports of discrepancies.) If
your XSLT processor can execute this stylesheet against catalog.xml and
produces no errors, then it should be functional enough to produce scripts
to run tests, canonicalize result files (see below), compare result files
against REF_OUT files, and generally move files around, clean up old files,
create directory trees having the same structure as the TESTS tree, etc.

Checking your output (copied from the toplevel README)

XML Documents may be logically equivalent without being physically identical.
(See Canonical XML 1.0, http://www.w3.org/TR/2001/REC- xml-c14n-20010315, and
its errata, http://www.w3.org/2001/03/C14N-errata for more details.) We
have provided reference output files in the REF_OUT subdirectories.  In order
to check that test output matches the reference files, it will be necessary to
convert both your output and the reference files to a standard form.  We have
provided a simple stylesheet, infoset.xsl, which produces standardized (very
expanded) output.  There are also publicly available tools that create
canonical XML.  You must use one of these tools in order to do meaningful
output comparisons.

One source of freely available XML and HTML canonicalizers is:
    http://www.datapower.com/xmldev/xsltmark.html
This actually provides a complete test harness that will accomodate any XSLT
processor, and can be built on both Linux and Windows systems.

If you need only the XML and HTML canonicalizers, you only need to build the
dgnorm and htmlnorm programs.  Build instructions are provided.  You can also
build the entire test harness.  Creating the control files from the catalog
we have provided is straghtforward.

====================================================================
Copyright (C) The Organization for the Advancement of
Structured Information Standards [OASIS] (2004). All Rights Reserved.

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
