///////////////////////////////////////////
//
// $Id$
//
///////////////////////////////////////////

#include <convert/base64codecvt.hpp>

static const std::string base64_charset("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
static const int NO_MORE = 256;

using namespace Arabica::convert;

std::codecvt_base::result base64codecvt::do_out(std::mbstate_t& state,
                        const char* from,
                        const char* from_end,
                        const char*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
{
  // convert to Base64
  grabState(state);
  grabFromNext(from_next);
  grabFromEnd(from_end);

  // base64 encode
  from_next = from;
  to_next = to;

  // generate the quad
  while((to_next != to_limit) && !((getCurrentOutChar() == NO_MORE) && (getPreviousChar() == 0))) 
  {
    char c = getCurrentOutChar();
    switch(getState())
    {
      case 0:
        *to_next++ = base64_charset[(c>>2) & 63];
        consumeOutChar();
        break;
      case 1:
        *to_next++ = base64_charset[((getPreviousChar() & 3) << 4) + ((c >> 4) & 15)];
        consumeOutChar();
        break;
      case 2:
        *to_next++ = base64_charset[((getPreviousChar() & 15) << 2) + ((c >> 6) & 3)];
        setPreviousChar(0);
        break;
      case 3:
        *to_next++ = base64_charset[(c & 63)];
        consumeOutChar();
        setPreviousChar(0);
        break;
    } // switch(s) 

    nextState();

    if((getState() == 0) && (getCurrentOutChar() == NO_MORE) && (getPreviousChar() == 0))
      break;
  } // while((from_next < from_end) && (to_next != to_end))

  // add padding if needed
  while((getState() != 0) && (to_next != to_limit))
  {
    *to_next++ = '=';
    nextState();
  } // while((state != 4) && (to_next != to_limit))

  return ((getState() == 0) && (getCurrentOutChar() == NO_MORE) && (getPreviousChar() == 0)) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // do_out

std::codecvt_base::result base64codecvt::do_in(std::mbstate_t& state,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       char* to,
                       char* to_limit,
                       char*& to_next) const
{
  // decode Base64
  grabState(state);
  from_next = from;
  to_next = to;

  while((from_next != from_end) && (to_next != to_limit))
  {
    char b = *from_next++;
    size_t i = base64_charset.find(b);
    if(i == std::string::npos)
    {
      if(b == '=')
        nextState();
      continue;
    }
    char c = static_cast<char>(i);

    char p = getPreviousChar();
    switch(getState())
    {
      case 0:
        break;
      case 1:
        *to_next++ = (p << 2) | (c >> 4);
        break;
      case 2:
        *to_next++ = (p << 4) | (c >> 2);
        break;
      case 3:
        *to_next++ = (p << 6) | c;
        break;
    } // switch(getState())
    setPreviousChar(c);
    nextState();
  } // while(to != to_limit)

  return (from_next == from_end) ? std::codecvt_base::ok : std::codecvt_base::partial; 
} // do_in

std::codecvt_base::result base64codecvt::do_unshift(std::mbstate_t& /* state */,
                            char* to,
                            char* to_limit,
                            char*& to_next) const
{
  to_next = to;

  // add padding if needed
  while((getState() != 0) && (to_next != to_limit))
  {
    *to_next++ = '=';
    nextState();
  } // while((state != 4) && (to_next != to_limit))

  return (to_next == to_limit) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // do_unshift

int base64codecvt::do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
						size_t max) const
{
  // 4 base64 chars = 3 chars
  size_t length(end - from);
  size_t quads(((length-1) / 4) + 1);
  size_t chars(quads*3);

  // htis next bit isn't exactly right, but it's close enough
  while(chars > max)
  {
    length -= 4;
    chars -= 3;
  } // while(chars > max)

  return length;
} // do_length

int base64codecvt::do_max_length() const throw()
{
  return 2;
} // do_max_length

void base64codecvt::grabState(std::mbstate_t& state) const
{ 
  state_ = reinterpret_cast<int*>(&state); 
  int s = getState();
  if((s < 0) || (s > 4))
    *state_ = 0;
} // grabState

int base64codecvt::getState() const
{
  return (*state_) & 0xff;
} // getState

void base64codecvt::nextState() const
{
  int s = getState();
  s = s + 1;
  if(s == 4)
    s = 0;

  *state_ &= 0xffffff00;
  *state_ |= s;
} // nextOutState

int base64codecvt::getCurrentOutChar() const
{
  if(*from_next_ != *from_end_)
    return **from_next_;

  return NO_MORE;
} // getCurrentOutChar

char base64codecvt::getPreviousChar() const
{
  return static_cast<char>((*state_ &0xff00) >> 8);
} // getCurrentOutChar

void base64codecvt::setPreviousChar(char c) const
{
  int bc(c);
  bc <<= 8;
  bc &= 0xff00;

  *state_ &= 0xffff00ff;
  *state_ |= bc;
} // setPreviousOutChar

void base64codecvt::consumeOutChar() const
{
  if(*from_next_ != *from_end_)
  {
    setPreviousChar(**from_next_);
    *from_next_ = *from_next_ + 1;
  } 
  else
    setPreviousChar(0);
}  // consumeOutChar

// end of file

