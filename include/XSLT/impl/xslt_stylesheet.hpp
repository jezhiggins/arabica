#ifndef ARABICA_XSLT_STYLESHEET_HPP
#define ARABICA_XSLT_STYLESHEET_HPP

namespace Arabica
{
namespace XSLT
{

#include <string>
#include <iostream>
#include <DOM/Node.hpp>
template<class string_type, class string_adaptor> class Sink;

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class Stylesheet
{
public:
  virtual ~Stylesheet() { }

  virtual void set_parameter(const string_type& name, bool value) = 0;
  virtual void set_parameter(const string_type& name, double value) = 0;
  virtual void set_parameter(const string_type& name, const char* value) = 0;
  virtual void set_parameter(const string_type& name, const string_type& value) = 0;

  virtual void set_output(Sink<string_type, string_adaptor>& sink) = 0;

  virtual void set_error_output(std::basic_ostream<typename string_adaptor::value_type>& os) = 0;

  virtual void execute(const DOM::Node<string_type, string_adaptor>& initialNode) const = 0;
}; // class Stylesheet

} // namespace XSLT
} // namespace Arabica

#endif
