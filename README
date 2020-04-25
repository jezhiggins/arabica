# Arabica - An XML and HTML processing toolkit

*New release - https://github.com/jezhiggins/arabica/releases/tag/2020-April(April 2020 available now).*

----

*Arabica is an XML and HTML processing toolkit*, providing *SAX2*, *DOM*, *XPath*, and *XSLT* implementations, written in *Standard C++*

* *SAX* is an event-based XML processing API. Arabica is a full SAX2 implementation, including the optional interfaces and helper classes. It provides uniform SAX2 wrappers for the Expat parser, Xerces, Libxml2 and, on Windows, for the Microsoft XML parser.
* The *DOM* is a platform- and language-neutral interface which models an XML document as a tree of nodes, defined by the W3C. Arabica implements the DOM Level 2 Core on top of the SAX layer.
* *XPath* is a language for addressing parts of an XML document. Arabica implements XPath 1.0 over its DOM implementation.
* *XSLT* is a language for transforming XML documents into other XML documents. Arabica builds XSLT over its XPath engine.
* In addition to the XML parser, Arabica includes Taggle, an *HTML parser* derived from TagSoup.

Arabica is written in Standard C++ and should be portable to most platforms. It is parameterised on string type. Out of the box, it can provide UTF-8 encoded std::strings or UTF-16 encoded std::wstrings, but can easily be customised for arbitrary string types.

## How To Build

If you're on some kind of Linux-like platform or on Windows you should be fine with the instructions below. For other platforms you'll have to wing it I'm afraid, but hopefully these instructions should provide sufficient clues to get you going. I'm also happy to help as best I can, so do ask. I'd also be delighted to receive Makefiles or project files for other platform+compiler combinations. The source includes donated CMake files, if that's your kind of thing.

### Prerequisites

Arabica builds on an existing XML parser, so you will need to have at least one of the following parsers installed - Expat, Libxml2, Xerces or if you're on a Windows platform MSXML. If you're working on any kind of recent Unix type box, you probably have libxml2 or expat already installed. If you're working on Windows, using MSXML is the easiest choice. If you want to use the Arabica's XPath or XSLT facilities, you will also need Boost, release 1.33 or later.

### Building on Linux

* If you've pulled the source from GitHub, you'll need to start with `autoreconf`, otherwise go directly to ...
* `./configure`
* `make`
* Optionally `make check` to run the tests
* Optionally `make install`

The ./configure checks for installed parsers, Boost, and so on and so forth. If you want to choose on parser over another, having things installed in unusual locations, or whatever, you might need to give it a hand. Running ./configure --help will give the many and varied options you can feed it.

### Building on Windows

There project files included for various versions of Visual Studio, although I can no longer vouch for them, I'm afraid.

 Building Arabica isn't hard, but you might need to get your hands ever so slightly dirty.

*Visual Studio 2012*

* Choose your parser (or parsers) as detailed above.
* Open vs2012/Arabica.sln and find the Arabicalib project. If you're not interested in XPath or XSLT load Arabica_noboost.sln instead.
* The parsers that Arabica.lib compiles in are controlled by ArabicaConfig.hpp. This header is generated from ArabicaConfig.S using the preprocessor. To set up your choice of parsers, select ArabicaConfig.S, right-click to bring up the menu and select Properties. This brings up the property pages for ArabicaConfig.S. Open out the folders until you find Custom Build Step, then select the Command Line setting. It should look like . Hit the little button at the end there to bring up the Command Line edit box.
* Add /D USE_parser the parser you want to support. The choices are USE_MSXML (the default), USE_EXPAT, USE_LIBXML2, USE_XERCES. Hit OK, then hit OK on the property pages.
* Now build everything.
* If you see errors like `fatal error C1083: Cannot open include file: 'expat.h': No such file or directory` you need to adjust your include paths. Select the Tools menu, then Options .... Scroll down the list of folders to Projects. Open it up and choose VC++ Directories. Toggle the Show directories for: box to Include files. What a hassle. Add the path (or paths) the header files for your chosen parsers. While your header, toggle the drop-down from Include files to Library files and add those paths too. If you're using MSXML there is no library file, so you can skip that step.
* Everything should now build through, and Arabica.lib should turn up in the lib directory.
* The example_* projects are all little sample applications built on Arabica.lib. They should now build through, and you'll find them in the bin directory. If you get link errors, check the library paths you set up earlier. That's it. Have a play with the sample apps and off you go. If you get DLL not found errors, make sure your parser is on the PATH.
* For bonus points now load and compile Arabica_tests.sln as well. It'll spit out a load of test executables in bin.
