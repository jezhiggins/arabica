#ifndef JEZUK_XML_UNICODE_CHARACTERS_H
#define JEZUK_XML_UNICODE_CHARACTERS_H

template<typename charT>
struct Unicode
{
  static const charT HORIZONTAL_TABULATION;
  static const charT LINE_FEED;
  static const charT CARRIAGE_RETURN;
  static const charT SPACE;
  static const charT EXCLAMATION_MARK;
  static const charT QUOTATION_MARK;
  static const charT NUMBER_SIGN;
  static const charT PERCENT_SIGN;
  static const charT AMPERSAND;
  static const charT APOSTROPHE;
  static const charT LEFT_PARENTHESIS;
  static const charT RIGHT_PARENTHESIS;
  static const charT ASTERISK;
  static const charT PLUS_SIGN;
  static const charT COMMA;
  static const charT HYPHEN_MINUS;
  static const charT FULL_STOP;
  static const charT SLASH;
  static const charT COLON;
  static const charT SEMI_COLON;
  static const charT LESS_THAN_SIGN;
  static const charT EQUALS_SIGN;
  static const charT GREATER_THAN_SIGN;
  static const charT QUESTION_MARK;
  static const charT LEFT_SQUARE_BRACKET;
  static const charT BACK_SLASH;
  static const charT RIGHT_SQUARE_BRACKET;
  static const charT LOW_LINE;
  static const charT VERTICAL_BAR;
}; // namespace XML

template<typename charT>
const charT Unicode<charT>::HORIZONTAL_TABULATION = 0x09;
template<typename charT>
const charT Unicode<charT>::LINE_FEED             = 0x0A;
template<typename charT>
const charT Unicode<charT>::CARRIAGE_RETURN       = 0x0D;
template<typename charT>
const charT Unicode<charT>::SPACE                 = 0x20;
template<typename charT>
const charT Unicode<charT>::EXCLAMATION_MARK      = 0x21;   // !
template<typename charT>
const charT Unicode<charT>::QUOTATION_MARK        = 0x22;   // "
template<typename charT>
const charT Unicode<charT>::NUMBER_SIGN           = 0x23;   // #
template<typename charT>
const charT Unicode<charT>::PERCENT_SIGN          = 0x25;   // %
template<typename charT>
const charT Unicode<charT>::AMPERSAND             = 0x26;   // &
template<typename charT>
const charT Unicode<charT>::APOSTROPHE            = 0x27;   // '
template<typename charT>
const charT Unicode<charT>::LEFT_PARENTHESIS      = 0x28;   // (
template<typename charT>
const charT Unicode<charT>::RIGHT_PARENTHESIS     = 0x29;   // )
template<typename charT>
const charT Unicode<charT>::ASTERISK              = 0x2A;   // *
template<typename charT>
const charT Unicode<charT>::PLUS_SIGN             = 0x2B;   // +
template<typename charT>
const charT Unicode<charT>::COMMA                 = 0x2C;   // ,
template<typename charT>
const charT Unicode<charT>::HYPHEN_MINUS          = 0x2D;   // -
template<typename charT>
const charT Unicode<charT>::FULL_STOP             = 0x2E;   // .
template<typename charT>
const charT Unicode<charT>::SLASH                 = 0x2F;   // /
template<typename charT>
const charT Unicode<charT>::COLON                 = 0x3A;   // :
template<typename charT>
const charT Unicode<charT>::SEMI_COLON            = 0x3B;   // ;
template<typename charT>
const charT Unicode<charT>::LESS_THAN_SIGN        = 0x3C;   // <
template<typename charT>
const charT Unicode<charT>::EQUALS_SIGN           = 0x3D;   // =
template<typename charT>
const charT Unicode<charT>::GREATER_THAN_SIGN     = 0x3E;   // >
template<typename charT>
const charT Unicode<charT>::QUESTION_MARK         = 0x3F;   // ?
template<typename charT>
const charT Unicode<charT>::LEFT_SQUARE_BRACKET   = 0x5B;   // ]
template<typename charT>
const charT Unicode<charT>::BACK_SLASH            = 0x5C;   // 
template<typename charT>
const charT Unicode<charT>::RIGHT_SQUARE_BRACKET  = 0x5D;   // [
template<typename charT>
const charT Unicode<charT>::LOW_LINE              = 0x5F;   // _
template<typename charT>
const charT Unicode<charT>::VERTICAL_BAR          = 0x7C;   // |

#endif

