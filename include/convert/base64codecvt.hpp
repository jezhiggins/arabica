#ifndef ARABICA_BASE64_CODECVT_H
#define ARABICA_BASE64_CODECVT_H
///////////////////////////////////////////
//
// $Id$
//
///////////////////////////////////////////

#include <locale>
#include <SAX/ArabicaConfig.hpp>
#include <Arabica/mbstate.hpp>

namespace Arabica
{
namespace convert
{

class base64codecvt : public std::codecvt<char, char, std::mbstate_t>
{
public:
  virtual ~base64codecvt() { }

protected:
  virtual result do_out(std::mbstate_t& state,
                        const char* from,
                        const char* from_end,
                        const char*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const;

  virtual result do_in(std::mbstate_t& state,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       char* to,
                       char* to_limit,
                       char*& to_next) const;

  virtual result do_unshift(std::mbstate_t&  state,
                       char* to,
                       char* to_limit,
                       char*& to_next) const;

  virtual int do_encoding() const throw() { return -1; } 

  virtual bool do_always_noconv() const throw() { return false; }

  virtual int do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
                        size_t max) const;

  virtual int do_max_length() const throw();

private:
  // state here is a little tricky - we need the previous char and
  // the state counter, and in some case we need to "pad" the input
  // strings.  I use these helper functions to mungle them
  // together and keep the details neater (or try to anyway)
  mutable int* state_;
  mutable const char** from_next_;
  mutable const char** from_end_;
  void grabState(std::mbstate_t& state) const;
  void grabFromNext(const char*& from_next) const { from_next_ = &from_next; }
  void grabFromEnd(const char*& from_end) const { from_end_ = &from_end; }

  int getState() const;
  void nextState() const;
  int getCurrentOutChar() const;
  void consumeOutChar() const;
  char getPreviousChar() const;
  void setPreviousChar(char c) const;
}; // class base64codecvt

} // namespace convert
} // namespace Arabica

#endif
