#ifndef ARABICA_XSLT_PRECEDENCE_HPP
#define ARABICA_XSLT_PRECEDENCE_HPP

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
    static Precedence frozen_(-1);
    return frozen_;
  } // Precedence

  Precedence() : 
    precedence_()
  { 
    //precedence_.push_back(0);
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

  Precedence(int precedence) : 
    precedence_()
  {
    precedence_.push_back(precedence);
  } // Precedence

public:
  ~Precedence() { }

  bool operator==(const Precedence& rhs) const 
  { 
    return precedence_ == rhs.precedence_;
  } // operator==

  bool operator>(const Precedence& rhs) const
  {
    return precedence_ > rhs.precedence_;
  } // operator>

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

  friend bool operator<(const Precedence& lhs, const Precedence& rhs);
  friend std::ostream& operator<<(std::ostream& os, const Precedence& prec);
}; // class Precedence

bool operator<(const Precedence& lhs, const Precedence& rhs)
{
  return lhs.precedence_.back() < rhs.precedence_.back();
} // PrecedenceCompare

std::ostream& operator<<(std::ostream& os, const Precedence& prec)
{
  os << "(";
  for(std::vector<int>::const_iterator p = prec.precedence_.begin(), pe = prec.precedence_.end(); p != pe; ++p)
  {
    if(p != prec.precedence_.begin())
      os << ",";
    os << *p;
  } // for ..
  os << ")";
} // operator<<
  
class PrecedenceStack
{
public:
  PrecedenceStack() :
    stack_(),
    count_(1)
  {
    stack_.push(Precedence::InitialPrecedence());
  } // PrecedenceStack

  PrecedenceStack(const PrecedenceStack& rhs) : 
    stack_(rhs.stack_)
  {
  } // PrecedenceStack

  const Precedence& top() const { return stack_.top(); }
  void push() 
  { 
    stack_.push(top().nextGeneration(count_++)); 
    std::cout << "Pushed " << top() << std::endl;    
  }
  void pop() { stack_.pop(); }
  void freeze() 
  { 
    while(!stack_.empty())
      stack_.pop();
    stack_.push(Precedence::FrozenPrecedence());
  } // freeze

private:
  std::stack<Precedence> stack_;
  int count_;
}; // class PrecedenceStack
#endif
