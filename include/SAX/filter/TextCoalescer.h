#ifndef ARABICA_TEXT_COALESCER_H
#define ARABICA_TEXT_COALESCER_H

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/XMLFilterImpl.h>
#include <SAX/ext/LexicalHandler.h>
#include <SAX/ext/DeclHandler.h>

namespace SAX
{

template<class string_type>
class basic_TextCoalescer : public basic_XMLFilterImpl<string_type>,
                            private basic_LexicalHandler<string_type>,
                            private basic_DeclHandler<string_type>
{
}; // class basic_TextCoalescer

typedef basic_TextCoalescer<std::string> TextCoalescer;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_TextCoalescer<std::wstring> wTextCoalescer;
#endif 

} // namespace SAX
#endif