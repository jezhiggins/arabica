#ifndef ARABICA_XML_CHARACTER_CLASSES_H
#define ARABICA_XML_CHARACTER_CLASSES_H

#ifdef _MSC_VER
#  include <stddef.h>
#endif

namespace Arabica
{

namespace XML
{
  bool is_char(wchar_t c);
  bool is_space(wchar_t c);
  bool is_name_char(wchar_t c);
  bool is_ncname_char(wchar_t c);
  bool is_letter(wchar_t c);
  bool is_base_char(wchar_t c);
  bool is_ideographic(wchar_t c);
  bool is_digit(wchar_t c);
  bool is_combining_char(wchar_t c);
  bool is_extender(wchar_t c);
  bool is_letter_or_digit(wchar_t c);

} // namespace XML

} // namespace Arabica
#endif
