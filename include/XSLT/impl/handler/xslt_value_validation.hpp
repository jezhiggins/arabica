#ifndef ARABICA_XSLT_VALUE_VALIDATION_HPP
#define ARABICA_XSLT_VALUE_VALIDATION_HPP

namespace Arabica 
{
namespace XSLT
{

template<class string_type>
struct ValueRule
{
  const string_type name;
  bool mandatory;
  const string_type default_value;
  const string_type* allowed;
}; // struct ValueRule

template<class string_type, class string_adaptor>
void validateValues(const string_type& parentElement, 
                    const string_type& name,
                    const string_type& value, 
                    const string_type allowed[])
{
  for(const string_type* a = allowed; *a != string_adaptor::empty_string(); ++a)
    if(value == *a)
      return;

  std::ostringstream os;
  os << string_adaptor::asStdString(parentElement) + ": " + string_adaptor::asStdString(name) + " may be one of ";
  while(*allowed != string_adaptor::empty_string())
    os << '\'' << string_adaptor::asStdString(*allowed++) << "' ";
  throw SAX::SAXException(os.str());
} // validateValues

template<class string_type, class string_adaptor>
void validateXmlAttribute(const string_type& parentElement,
                          const string_type& name, 
                          const string_type& value,
                  			  std::map<string_type, string_type>& results)
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

  results[name] = value;

  if(name == SC::space)
    validateValues<string_type, string_adaptor>(parentElement, name, value, SC::DefaultPreserve);
} // validateXmlAttribute

template<class string_type, class string_adaptor>
void validateAttribute(const string_type& parentElement,
                       const string_type& name, 
                       const string_type& value, 
                       const ValueRule<string_type>* rules, 
		                   std::map<string_type, string_type>& results)
{
  while((rules->name != string_adaptor::empty_string()) && (name != rules->name))
    ++rules;

  if(rules->name == string_adaptor::empty_string())
    throw SAX::SAXException(string_adaptor::asStdString(parentElement) + ": Illegal attribute " + string_adaptor::asStdString(name));

  results[name] = value;

  if(rules->allowed != 0)
    validateValues<string_type, string_adaptor>(parentElement, name, value, rules->allowed);
} // validateAttribute

template<class string_type, class string_adaptor>
std::map<string_type, string_type> gatherAttributes(const string_type& parentElement,
                                                    const SAX::Attributes<string_type, string_adaptor>& atts,
                                                    const ValueRule<string_type>* rules)
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

  std::map<string_type, string_type> results;

  for(const ValueRule<string_type>* r = rules ; r->name != string_adaptor::empty_string(); ++r)
  {
    if((r->mandatory) && (atts.getValue(r->name).empty()))
      throw SAX::SAXException(string_adaptor::asStdString(parentElement) + ": Attribute " + string_adaptor::asStdString(r->name) + " must be specified");
    if(r->default_value != string_adaptor::empty_string())
      results[r->name] = r->default_value;
  } // 

  for(int a = 0; a < atts.getLength(); ++a)
  {
    if(atts.getLocalName(a) == string_adaptor::empty_string()) 
      continue; // namespace decl
    if(atts.getURI(a) == SC::xml_uri)
    {
      validateXmlAttribute<string_type, string_adaptor>(parentElement, atts.getLocalName(a), atts.getValue(a), results); // special xml: attributes
      continue;
    }
    if(atts.getURI(a) == string_adaptor::empty_string())
      validateAttribute<string_type, string_adaptor>(parentElement, atts.getLocalName(a), atts.getValue(a), rules, results);
  }

  return results;
} // validateAttributes

template<class string_type, class string_adaptor>
void verifyNoCharacterData(const string_type& ch,
                           const string_type& name)
{
  for(typename string_type::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
    if(!Arabica::XML::is_space(*i))
      throw SAX::SAXException(string_adaptor::asStdString(name) + " element can not contain character data.");
} // verifyNoCharacterContent

} // namespace XSLT
} // namespace Arabica
#endif

