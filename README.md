Arabica
=======

*Arabica is an XML and HTML processing toolkit*, providing *SAX2*, *DOM*, *XPath*, and *XSLT* implementations, written in *Standard C++*

* *SAX* is an event-based XML processing API. Arabica is a full SAX2 implementation, including the optional interfaces and helper classes. It provides uniform SAX2 wrappers for the Expat parser, Xerces, Libxml2 and, on Windows, for the Microsoft XML parser.
* The *DOM* is a platform- and language-neutral interface which models an XML document as a tree of nodes, defined by the W3C. Arabica implements the DOM Level 2 Core on top of the SAX layer.
* *XPath* is a language for addressing parts of an XML document. Arabica implements XPath 1.0 over its DOM implementation.
* *XSLT* is a language for transforming XML documents into other XML documents. Arabica builds XSLT over its XPath engine.
* In addition to the XML parser, Arabica includes Taggle, an *HTML parser* derived from TagSoup. 

Arabica is written in Standard C++ and should be portable to most platforms. It is parameterised on string type. Out of the box, it can provide UTF-8 encoded std::strings or UTF-16 encoded std::wstrings, but can easily be customised for arbitrary string types.

Arabica is available under a BSD-style license.

For latest Arabica news, please see http://www.jezuk.co.uk/arabica
For build notes see http://www.jezuk.co.uk/arabica/howtobuild

