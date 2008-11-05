#ifndef ARABICA_XSLT_PRECEDENCE_HPP
#define ARABICA_XSLT_PRECEDENCE_HPP

class Precedence
{
public:
  Precedence() : 
    precedence_()
  { 
  } // Precedence

  Precedence(const Precedence& rhs) : 
    precedence_(rhs.precedence_)
  { 
  } // Precedence

private:
  Precedence(const std::vector<int> precedence) : 
    precedence_(precedence)
  {
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
    return *this;
  } // operator=

  Precedence nextGeneration(int p) const
  {
    Precedence next(precedence_);
    next.precedence_.push_back(p);
    return next;
  } // nextGeneration

private:
  std::vector<int> precedence_;  
}; // class Precedence

#endif
