#ifndef ARABICA_TEST_SILLY_STRING_HPP
#define ARABICA_TEST_SILLY_STRING_HPP

#include <string>
#include <functional>

// testing purposes only
// a string with as minimal interface as possible

class silly_string
{
public:
  silly_string();
  silly_string(const silly_string& rhs);
  ~silly_string();

  bool operator==(const silly_string& rhs) const;
  silly_string& operator=(const silly_string& rhs);

private:
  // use a std::string to the actual work
  std::string s_;

  friend class silly_string_adaptor;
}; // class silly_string

class silly_string_adaptor
{
public:
  typedef silly_string stringT;
  typedef std::string::const_iterator const_iterator;
  typedef char value_type;
  typedef std::string::size_type size_type;
  static const size_type npos;

  char makeValueT(char c) const;
  silly_string makeStringT(const char* str) const;
  silly_string makeStringT(const char* str, int length) const;
  
  template<typename iterator_t>
  silly_string makeStringT(iterator_t first, iterator_t last) const
  {
    silly_string s;
    s.s_ = std::string(first, last);
    return s;
  } // makeStringT


  // here we go
  static bool empty(const silly_string& s);
  static size_type find(const silly_string& str, const silly_string& what);
  static silly_string substr(const silly_string& str, const size_type& offset);
  static silly_string substr(const silly_string& str, const size_type& offset, const size_type& count);
  static size_type length(const silly_string& str);
  static void append(silly_string& str, const silly_string& a);
  static void insert(silly_string& str, size_type offset, const silly_string& a);
  static void replace(silly_string& str, size_type offset, size_type count, const silly_string& a);
  static const_iterator begin(const silly_string& str) { return str.s_.begin(); }
  static const_iterator end(const silly_string& str) { return str.s_.end(); }

  // only used to constuct error strings - don't have to be highly efficient!
  std::string asStdString(const silly_string& str) const;
}; // class silly_string_adaptor

template<class CharType, class Traits>
std::basic_ostream<CharType, Traits>& operator<<(std::basic_ostream<CharType, Traits>& os, const silly_string& s)
{
  os << silly_string_adaptor().asStdString(s);
  return os;
} // operator<<

template<>
struct std::less<silly_string> : public binary_function<silly_string, silly_string, bool>
{	// functor for operator<
	bool operator()(const silly_string& lhs, const silly_string& rhs) const
	{	// apply operator< to operands
    silly_string_adaptor sa;
		return (sa.asStdString(lhs) < sa.asStdString(rhs));
	}
};

#endif
