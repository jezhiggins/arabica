#ifndef ARABICA_TEST_SILLY_STRING_HPP
#define ARABICA_TEST_SILLY_STRING_HPP

#include <string>
#include <functional>
#include <Arabica/stringadaptortag.hpp>
#include <SAX/ArabicaConfig.hpp>
// testing purposes only
// a string with as minimal interface as possible

class silly_string
{
public:
  silly_string();
  silly_string(const silly_string& rhs);
  ~silly_string();

  bool operator==(const silly_string& rhs) const;
  bool operator!=(const silly_string& rhs) const { return !(this->operator==(rhs)); }
  silly_string& operator=(const silly_string& rhs);

private:
  // use a std::string to the actual work
  std::string s_;

  friend class silly_string_adaptor;
  friend bool operator<(const silly_string& lhs, 
                        const silly_string& rhs);
}; // class silly_string

bool operator<(const silly_string& lhs, const silly_string& rhs);

class silly_string_adaptor : public Arabica::string_adaptor_tag
{
public:
  typedef silly_string string_type;
  typedef std::string::const_iterator const_iterator;
  typedef std::string::iterator mutable_iterator;
  typedef char value_type;
  typedef std::string::size_type size_type;
  static size_type npos()
  {
    return std::string::npos;
  }

  static const silly_string& empty_string() { static silly_string es; return es; }

  template<class InputIterator>
  static silly_string construct(InputIterator from, InputIterator to)
  {
    silly_string ss;
    ss.s_ = std::string(from, to);
    return ss;
  } // construct

  static string_type construct(const value_type* s)
  {
    silly_string ss;
    ss.s_ = std::string(s);
    return ss;
  } // construct

  static char convert_from_utf8(char c);
  static silly_string construct_from_utf8(const char* str);
  static silly_string construct_from_utf8(const char* str, int length);
#ifndef ARABICA_NO_WCHAR_T
  static silly_string construct_from_utf16(const wchar_t* str);
  static silly_string construct_from_utf16(const wchar_t* str, int length);
#endif

  // here we go
  static bool empty(const silly_string& s);
  static size_type find(const silly_string& str, const silly_string& what);
  static size_type find(const silly_string& str, value_type c);
  static silly_string substr(const silly_string& str, const size_type& offset);
  static silly_string substr(const silly_string& str, const size_type& offset, const size_type& count);
  static size_type length(const silly_string& str);
  static void append(silly_string& str, const silly_string& a);
  static void insert(silly_string& str, size_type offset, const silly_string& a);
  static void replace(silly_string& str, size_type offset, size_type count, const silly_string& a);
  static const_iterator begin(const silly_string& str) { return str.s_.begin(); }
  static mutable_iterator begin(silly_string& str) { return str.s_.begin(); }
  static const_iterator end(const silly_string& str) { return str.s_.end(); }
  static mutable_iterator end(silly_string& str) { return str.s_.end(); }

  // mainly used to constuct error strings - don't have to be highly efficient!
  static std::string asStdString(const silly_string& str);
#ifndef ARABICA_NO_WCHAR_T
  static std::wstring asStdWString(const silly_string& str);
#endif
}; // class silly_string_adaptor

template<class CharType, class Traits>
std::basic_ostream<CharType, Traits>& operator<<(std::basic_ostream<CharType, Traits>& os, const silly_string& s)
{
  os << silly_string_adaptor::asStdString(s);
  return os;
} // operator<<

namespace std {

template<>
struct less<silly_string> : public binary_function<silly_string, silly_string, bool>
{	// functor for operator<
	bool operator()(const silly_string& lhs, const silly_string& rhs) const
	{	// apply operator< to operands
    return (silly_string_adaptor::asStdString(lhs) < silly_string_adaptor::asStdString(rhs));
	}
};
} // namespace std

#endif
