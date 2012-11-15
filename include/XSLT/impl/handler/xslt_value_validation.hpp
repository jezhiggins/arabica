#ifndef ARABICA_XSLT_VALUE_VALIDATION_HPP
#define ARABICA_XSLT_VALUE_VALIDATION_HPP

namespace Arabica 
{
namespace XSLT
{

template<class string_type, class string_adaptor> class AttributeValidatorsBuilder;
template<class string_type, class string_adaptor> class AttributeValidators;

template<class string_type>
class AllowedValues
{
public:
  AllowedValues() 
  {
  } // AllowedValues

  AllowedValues(const string_type& v1, const string_type& v2) 
  {
    allowed_.insert(v1);
    allowed_.insert(v2);
  } // AllowedValues

  AllowedValues(const AllowedValues& rhs) :
    allowed_(rhs.allowed_)
  {
  } // AllowedValues

  bool is_allowed(const string_type& v) const
  {
    if(allowed_.size() == 0)
      return true;
    return allowed_.find(v) != allowed_.end();
  } // is_allowed

  AllowedValues& operator=(const AllowedValues& rhs)
  {
    allowed_ = rhs.allowed_;
    return *this;
  } // operator=

private:
  std::set<string_type> allowed_;
}; // AllowedValues

template<class string_type, class string_adaptor> 
class AttributeValidator
{
public:
  AttributeValidator() :
    required_(false)
  {
  } // AttributeValidator

  bool mandatory() const { return required_; }
  bool has_default() const { return !def_.empty(); }
  const string_type& default_value() const { return def_; }
  bool is_allowed(const string_type& v) const { return allowed_.is_allowed(v); }

private:
  explicit AttributeValidator(bool required) :
    required_(required)
  {
  } // AttributeValidator

  AttributeValidator(bool required, const string_type& def, const AllowedValues<string_type> allowed) :
    required_(required),
    def_(def),
    allowed_(allowed)
  {
  } // AttributeValidator

  bool required_;
  string_type def_;
  AllowedValues<string_type> allowed_;

  AttributeValidator& operator=(const AttributeValidator& rhs)
  {
    required_ = rhs.required_;
    def_ = rhs.def_;
    allowed_ = rhs.allowed_;
    return *this;
  } // operator=

  friend class AttributeValidators<string_type, string_adaptor>;
}; // class AttributeValidator

template<class string_type, class string_adaptor>
class AttributeValidators
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

public:
  static AttributeValidatorsBuilder<string_type, string_adaptor> rule(const string_type& name, bool required);

  std::map<string_type, string_type> gather(const string_type& parentElement,
                                             const SAX::Attributes<string_type, string_adaptor>& atts) const
  {
    typedef StylesheetConstant<string_type, string_adaptor> SC;

    std::map<string_type, string_type> results;

    for(ValidatorMapIterator r = rules_.begin(); r != rules_.end(); ++r)
    {
      const string_type& name = r->first;
      const AttributeValidator<string_type, string_adaptor>& av = r->second;
      if((av.mandatory()) && (atts.getValue(name).empty()))
        throw SAX::SAXException(string_adaptor::asStdString(parentElement) + ": Attribute " + string_adaptor::asStdString(name) + " must be specified");
      if(av.has_default())
        results[name] = av.default_value();
    } // for ...

    for(int a = 0; a < atts.getLength(); ++a)
    {
      const string_type& name = atts.getLocalName(a);
      if(name == string_adaptor::empty_string()) 
        continue; // namespace decl

      const string_type& uri = atts.getURI(a);
      const string_type& value = atts.getValue(a);

      results[name] = value;

      if(uri == string_adaptor::empty_string())
        validateAttribute(parentElement, name, value);
      else if(uri == SC::xml_uri)
        validateXmlAttribute(parentElement, name, value); // special xml: attributes
    } // for ...

    return results;
  } // gather

private:
  void validateXmlAttribute(const string_type& parentElement,
                            const string_type& name, 
                            const string_type& value) const
  {
    if(name == SC::space)
      validateValues(parentElement, name, value, XMLSpaceValidator);
  } // validateXmlAttribute

  void validateAttribute(const string_type& parentElement,
                         const string_type& name, 
                         const string_type& value) const
  {
    ValidatorMapIterator r = rules_.find(name);

    if(r == rules_.end())
      throw SAX::SAXException(string_adaptor::asStdString(parentElement) + ": Illegal attribute " + string_adaptor::asStdString(name));

    validateValues(parentElement, name, value, r->second);
  }

  void validateValues(const string_type& parentElement,
                      const string_type& name,
                      const string_type& value,
                      const AttributeValidator<string_type, string_adaptor>& rule) const
  {                       
    if(rule.is_allowed(value))
      return;

    throw SAX::SAXException(string_adaptor::asStdString(value) + 
                            " is not an allowed value for " +
                            string_adaptor::asStdString(parentElement) + 
                            "/@ " + 
                            string_adaptor::asStdString(name));
  } // validateValues

  void put(const string_type& name, bool required)
  {
    rules_[name] = AttributeValidator<string_type, string_adaptor>(required);
  } // put

  AttributeValidators() { }

  typedef std::map<string_type, AttributeValidator<string_type, string_adaptor> > ValidatorMap;
  typedef typename ValidatorMap::const_iterator ValidatorMapIterator;

  ValidatorMap rules_;

  static const AttributeValidator<string_type, string_adaptor> XMLSpaceValidator;

  friend class AttributeValidatorsBuilder<string_type, string_adaptor>;
}; // class AttributeValidators

template<class string_type, class string_adaptor>
const AttributeValidator<string_type, string_adaptor> 
    AttributeValidators<string_type, string_adaptor>::XMLSpaceValidator(false, 
                                                                        string_adaptor::empty_string(),
                                                                        AllowedValues<string_type>(string_adaptor::construct_from_utf8("default"),
                                                                                                   string_adaptor::construct_from_utf8("preserve")));

template<class string_type, class string_adaptor>
class AttributeValidatorsBuilder
{
public:
  operator AttributeValidators<string_type, string_adaptor>&() { return validators_; }

  AttributeValidatorsBuilder& rule(const string_type& name, bool required)
  {
    validators_.put(name, required);
    return *this;
  } // rule

private:
  AttributeValidatorsBuilder() { }
  AttributeValidatorsBuilder(const AttributeValidatorsBuilder& rhs) :
    validators_(rhs.validators_)
  { 
  } // AttributeValidatorsBuilder

  AttributeValidators<string_type, string_adaptor> validators_;

  friend class AttributeValidators<string_type, string_adaptor>;
}; // class AttributeValidatorsBuilder
 
template<class string_type, class string_adaptor>
AttributeValidatorsBuilder<string_type, string_adaptor> 
  AttributeValidators<string_type, string_adaptor>::rule(const string_type& name, bool required)
{
  AttributeValidatorsBuilder<string_type, string_adaptor> builder;
  builder.rule(name, required);
  return builder;
} // AttributeValidator::rule

////

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

