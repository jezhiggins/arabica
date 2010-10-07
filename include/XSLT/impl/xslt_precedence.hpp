#ifndef ARABICA_XSLT_PRECEDENCE_HPP
#define ARABICA_XSLT_PRECEDENCE_HPP

#include <algorithm>

class Precedence
{
public:
  static const Precedence& InitialPrecedence()
  {
    static Precedence initial_(0);
    return initial_;
  } // Precedence

  static const Precedence& FrozenPrecedence()
  {
    static Precedence frozen_;
    return frozen_;
  } // Precedence

  Precedence() : 
    precedence_(),
    children_(0)
  { 
    //precedence_.push_back(0);
  } // Precedence

  Precedence(const Precedence& rhs) : 
    precedence_(rhs.precedence_),
    children_(rhs.children_)
  { 
  } // Precedence

private:
  Precedence(const std::vector<int> precedence) : 
    precedence_(precedence),
    children_(0)
  {
  } // Precedence

  Precedence(int precedence) : 
    precedence_(),
    children_(0)
  {
    precedence_.push_back(precedence);
  } // Precedence

public:
  ~Precedence() { }

  bool operator==(const Precedence& rhs) const 
  { 
    return precedence_ == rhs.precedence_;
  } // operator==

  Precedence& operator=(const Precedence& rhs) 
  { 
    std::vector<int> other(rhs.precedence_);
    precedence_.swap(other);
    children_ = rhs.children_;
    return *this;
  } // operator=

  bool is_descendant(const Precedence& other) const
  {
    if(other.precedence_.size() <= precedence_.size())
      return false;

    for(int i = 0, ie = precedence_.size(); i != ie; ++i)
      if(other.precedence_[i] != precedence_[i])
        return false;

    return true;
  } // is_descendant

  Precedence next_generation() 
  {
    Precedence next(precedence_);
    next.precedence_.push_back(++children_);
    return next;
  } // nextGeneration

private:
  std::vector<int> precedence_;  
  int children_;

  friend bool operator<(const Precedence& lhs, const Precedence& rhs);
  friend std::ostream& operator<<(std::ostream& os, const Precedence& prec);
}; // class Precedence

bool operator<(const Precedence& lhs, const Precedence& rhs)
{
  if(lhs.precedence_ == rhs.precedence_)
    return false;

  int len = (std::min)(lhs.precedence_.size(), rhs.precedence_.size());
  for(int c = 0; c != len; ++c)
  {
    if(lhs.precedence_[c] < rhs.precedence_[c])
      return true;
    if(lhs.precedence_[c] > rhs.precedence_[c])
      return false;
  }
  if(lhs.precedence_.size() < rhs.precedence_.size()) 
    return false;

  return true;
} // operator>

bool operator>(const Precedence& lhs, const Precedence& rhs)
{
  return !(lhs == rhs) && !(lhs < rhs);
} // operator>

std::ostream& operator<<(std::ostream& os, const Precedence& prec)
{
  os << '(' << prec.precedence_[0];
  for(size_t i = 1; i != prec.precedence_.size(); ++i)
    os << ',' << prec.precedence_[i];
  os << ')';
  return os;
} // operator<<
 
#endif
