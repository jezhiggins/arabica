#include "silly_string.hpp"

silly_string::silly_string()
{
} // silly_string

silly_string::silly_string(const silly_string& rhs)
{
  s_ = rhs.s_;
} // silly_string

silly_string::~silly_string()
{
} // ~silly_string

bool silly_string::operator==(const silly_string& rhs) const
{
  return s_ == rhs.s_;
} // operator== 

silly_string& silly_string::operator=(const silly_string& rhs)
{
  s_ = rhs.s_;
  return *this;
} // operator=

////////////////////////////////////////
////////////////////////////////////////
const silly_string_adaptor::size_type silly_string_adaptor::npos = std::string::npos;

char silly_string_adaptor::makeValueT(char c) const
{
  return c;
} // makeValueT
  
silly_string silly_string_adaptor::makeStringT(const char* str) const
{
  silly_string s;
  s.s_ = str;
  return s;
} // makeStringT

silly_string silly_string_adaptor::makeStringT(const char* str, int length) const
{
  silly_string s;
  s.s_ = std::string(str, length);
  return s;
} // makeStringT

bool silly_string_adaptor::empty(const silly_string& s)
{
  return s.s_.empty();
} // empty

silly_string_adaptor::size_type silly_string_adaptor::find(const silly_string& str, const silly_string& what)
{
  return str.s_.find(what.s_);
} // find

silly_string silly_string_adaptor::substr(const silly_string& str, const size_type& offset)
{
  return silly_string_adaptor().makeStringT(str.s_.substr(offset).c_str());
} // substr

silly_string silly_string_adaptor::substr(const silly_string& str, const size_type& offset, const size_type& count)
{
  return silly_string_adaptor().makeStringT(str.s_.substr(offset, count).c_str());
} // substr

silly_string_adaptor::size_type silly_string_adaptor::length(const silly_string& str)
{
  return str.s_.length();
} // length

void silly_string_adaptor::append(silly_string& str, const silly_string& a)
{
  str.s_.append(a.s_);
} // append

void silly_string_adaptor::insert(silly_string& str, size_type offset, const silly_string& a)
{
  str.s_.insert(offset, a.s_);
} // insert

void silly_string_adaptor::replace(silly_string& str, size_type offset, size_type count, const silly_string& a)
{
  str.s_.replace(offset, count, a.s_);
} // replace


// only used to constuct error strings - don't have to be highly efficient!
std::string silly_string_adaptor::asStdString(const silly_string& str) const
{
  return str.s_;
} // asStdString
