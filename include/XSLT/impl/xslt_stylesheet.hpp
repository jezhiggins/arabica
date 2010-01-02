#ifndef ARABICA_XSLT_STYLESHEET_HPP
#define ARABICA_XSLT_STYLESHEET_HPP

namespace Arabica
{
namespace XSLT
{

#include <string>
#include <iostream>
#include <DOM/Node.hpp>
class Sink;

class Stylesheet
{
public:
  virtual ~Stylesheet() { }

  virtual void set_parameter(const std::string& name, bool value) = 0;
  virtual void set_parameter(const std::string& name, double value) = 0;
  virtual void set_parameter(const std::string& name, const char* value) = 0;
  virtual void set_parameter(const std::string& name, const std::string& value) = 0;

  virtual void set_output(Sink& sink) = 0;

  virtual void set_error_output(std::ostream& os) = 0;

  virtual void execute(const DOM::Node<std::string>& initialNode) const = 0;
}; // class Stylesheet

} // namespace XSLT
} // namespace Arabica

#endif
