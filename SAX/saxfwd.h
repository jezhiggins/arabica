#ifndef saxfwdH
#define saxfwdH

// $Id$

#include <string>

/** \mainpage SAX in C++
 *
 * \section intro Introduction
 *
 * SAX is an event-based XML processing API. It defines the interface 
 * between the parser (probably someone else's code) and its client 
 * (probably your code). Unlike the DOM, SAX has no official status 
 * within the W3C but is very popular and widely used. There are 
 * implementations in Java, Python, Perl, at least two COM versions and more.
 * <p>
 * This package consists of a definition of the SAX interface in C++ 
 * and it's associated documentation. Because an interface by itself 
 * wouldn't be terribly useful, there also SAX wrappers for a variety of 
 * parsers. Finally there are some examples, to give some clues as to how to use it.
 *
 *
 * \section license License
 * 
 * Copyright (c) 2001, Jez UK Ltd<br>
 * All rights reserved.
 * <p>
 * Redistribution and use in source and binary forms, with or <br>
 * without modification, are permitted provided that the following <br>
 * conditions are met:<br>
 * <ul>
 *   <li>Redistributions of source code must retain the above <br>
 *       copyright notice, this list of conditions and the following <br>
 *       disclaimer.</li>
 *   <li>Redistributions in binary form must reproduce the above <br>
 *       copyright notice, this list of conditions and the following <br>
 *       disclaimer in the documentation and/or other materials <br>
 *       provided with the distribution.</li>
 *   <li>Neither the name of Jez UK Ltd nor the names of  <br>
 *       contributors may be used to endorse or promote products <br>
 *       derived from this software without specific prior written <br>
 *       permission.</li>
 * </ul>
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND <br>
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, <br>
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF <br>
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE <br>
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE <br>
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, <br>
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, <br>
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, <br>
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY <br>
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR <br>
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT <br>
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY <br>
 * OF SUCH DAMAGE.<br>
 * 
 */



/**
 *  
 * SAX in C++ - A C++ implementation of the SAX2 interface.
 *
 */
namespace SAX 
{

template<class string_type> class basic_AttributeList;
template<class string_type> class basic_DocumentHandler;
template<class string_type> class basic_DTDHandler;
template<class string_type> class basic_EntityResolver;
template<class string_type> class basic_InputSource;
template<class string_type> class basic_Locator;
template<class string_type> class basic_Parser;
template<class string_type> class basic_SAXParseException;

class ErrorHandler;

typedef basic_AttributeList<std::string> AttributeList;
typedef basic_DocumentHandler<std::string> DocumentHandler;
typedef basic_DTDHandler<std::string> DTDHandler;
typedef basic_EntityResolver<std::string> EntityResolver;
typedef basic_InputSource<std::string> InputSource;
typedef basic_Locator<std::string> Locator;
typedef basic_Parser<std::string> Parser;
typedef basic_SAXParseException<std::string> SAXParseException;

typedef basic_AttributeList<std::wstring> wAttributeList;
typedef basic_DocumentHandler<std::wstring> wDocumentHandler;
typedef basic_DTDHandler<std::wstring> wDTDHandler;
typedef basic_EntityResolver<std::wstring> wEntityResolver;
typedef basic_InputSource<std::wstring> wInputSource;
typedef basic_Locator<std::wstring> wLocator;
typedef basic_Parser<std::wstring> wParser;
typedef basic_SAXParseException<std::wstring> wSAXParseException;

}; // namespace SAX

#endif
// end of file

