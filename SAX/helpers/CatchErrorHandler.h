#ifndef ARABICA_CATCH_ERROR_HANDLER_H
#define ARABICA_CATCH_ERROR_HANDLER_H

#include <SAX/ErrorHandler.h>

/**
 * An ErrorHandler implementation that keeps hold of any errors for later reporting.
 */

namespace SAX
{
template<class string_type>
class CatchErrorHandler : public SAX::basic_ErrorHandler<string_type>
{
public:
  typedef SAX::basic_SAXParseException<string_type> SAXParseExceptionT;

  CatchErrorHandler() : errors_() { }
  virtual ~CatchErrorHandler() { }

  virtual void warning(const SAXParseExceptionT& exception)
  {
    hold(exception);
  } // warning

  virtual void error(const SAXParseExceptionT& exception)
  {
    hold(exception);
  } // error

  virtual void fatalError(const SAXParseExceptionT& exception)
  {
    hold(exception);
  } // fatalError

  bool errorsReported() const { return !errors_.empty(); }
  const std::string& errors() const { return errors_; }
  void reset() { errors_.erase(); }

private:
  void hold(const SAXParseExceptionT& exception)
  {
    errors_ += exception.what();
  } // hold

  std::string errors_;
}; // class CatchErrorHandler

} // namespace Arabica

#endif
