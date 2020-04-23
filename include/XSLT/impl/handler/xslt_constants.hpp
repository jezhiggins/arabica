#ifndef ARABICA_XSLT_CONSTANTS_HPP
#define ARABICA_XSLT_CONSTANTS_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
struct StylesheetConstant : public Arabica::text::Unicode<typename string_adaptor::value_type>
{
  static const string_type NamespaceURI;
  static const string_type Version;
  static const string_type Vendor;
  static const string_type VendorUrl;

  static const string_type CDATAStart;
  static const string_type CDATAEnd;
  static const string_type CommentStart;
  static const string_type CommentEnd;
  static const string_type PIStart;
  static const string_type PIEnd;

  static const string_type stylesheet;
  static const string_type transform;

  static const string_type apply_imports;
  static const string_type apply_templates; 
  static const string_type attribute; 
  static const string_type attribute_set;
  static const string_type call_template;
  static const string_type choose; 
  static const string_type comment;
  static const string_type copy;
  static const string_type copy_of;
  static const string_type decimal_format;
  static const string_type element; 
  static const string_type fallback; 
  static const string_type for_each;
  static const string_type if_;
  static const string_type import;
  static const string_type include;
  static const string_type key;
  static const string_type message;
  static const string_type namespace_alias;
  static const string_type number;
  static const string_type output;
  static const string_type param;
  static const string_type preserve_space;
  static const string_type processing_instruction;
  static const string_type strip_space;
  static const string_type template_;
  static const string_type text;
  static const string_type value_of;
  static const string_type variable;
  static const string_type sort;
  static const string_type with_param;
  static const string_type when;
  static const string_type otherwise;

  static const string_type version;
  static const string_type extension_element_prefixes;
  static const string_type exclude_result_prefixes;
  static const string_type id;
  static const string_type href;
  static const string_type select;
  static const string_type name;
  static const string_type namespace_;
  static const string_type match;
  static const string_type mode;
  static const string_type priority;
  static const string_type use;
  static const string_type method;
  static const string_type indent;
  static const string_type omit_xml_declaration;
  static const string_type standalone;
  static const string_type space;
  static const string_type media_type;
  static const string_type encoding;
  static const string_type doctype_public;
  static const string_type doctype_system;
  static const string_type stylesheet_prefix;
  static const string_type result_prefix;
  static const string_type cdata_section_elements;
  static const string_type use_attribute_sets;
  static const string_type test;
  static const string_type lang;
  static const string_type data_type;
  static const string_type order;
  static const string_type case_order;
  static const string_type terminate;
  static const string_type disable_output_escaping;
  static const string_type hash_default;
  static const string_type no;
  static const string_type yes;
  static const string_type utf8;
  static const string_type ascending;
  static const string_type descending;
  static const string_type upper_first;
  static const string_type lower_first;
  static const string_type AllowedYesNo[];
  static const string_type DefaultPreserve[];

  static const string_type double_hyphen;
  static const string_type escaped_double_hyphen;
  static const string_type escaped_pi_end;

  static const string_type root_xpath;
  static const string_type current_xpath;
  static const string_type namespace_xpath;

  static const string_type version_property;
  static const string_type vendor_property;
  static const string_type vendor_url_property;

  static const string_type xml;
  static const string_type html;
  static const string_type xmlns_colon;
  static const string_type xmlns;
  static const string_type auto_ns;
  static const string_type xmlns_uri;
  static const string_type xml_uri;

  static const string_type newline;
}; // struct StylesheetConstant

#define STYLESHEETCONSTANT(What, Value) template<class string_type, class string_adaptor> const string_type StylesheetConstant<string_type, string_adaptor>::What = string_adaptor::construct_from_utf8(Value)

STYLESHEETCONSTANT(NamespaceURI, "http://www.w3.org/1999/XSL/Transform");
STYLESHEETCONSTANT(Version, "1.0");
STYLESHEETCONSTANT(Vendor, "Jez Higgins, JezUK Ltd");
STYLESHEETCONSTANT(VendorUrl, "http://www.jezuk.co.uk/arabica/");

STYLESHEETCONSTANT(CDATAStart, "<![CDATA[");
STYLESHEETCONSTANT(CDATAEnd, "]]>");
STYLESHEETCONSTANT(CommentStart, "<!--");
STYLESHEETCONSTANT(CommentEnd, "-->");
STYLESHEETCONSTANT(PIStart, "<?");
STYLESHEETCONSTANT(PIEnd, "?>");

STYLESHEETCONSTANT(stylesheet, "stylesheet");
STYLESHEETCONSTANT(transform, "transform");

STYLESHEETCONSTANT(apply_imports, "apply-imports");
STYLESHEETCONSTANT(apply_templates, "apply-templates");
STYLESHEETCONSTANT(attribute, "attribute");
STYLESHEETCONSTANT(attribute_set, "attribute-set");
STYLESHEETCONSTANT(call_template, "call-template");
STYLESHEETCONSTANT(choose, "choose");
STYLESHEETCONSTANT(comment, "comment"); 
STYLESHEETCONSTANT(copy, "copy");
STYLESHEETCONSTANT(copy_of, "copy-of"); 
STYLESHEETCONSTANT(decimal_format, "decimal-format");
STYLESHEETCONSTANT(element, "element"); 
STYLESHEETCONSTANT(fallback, "fallback"); 
STYLESHEETCONSTANT(for_each, "for-each");
STYLESHEETCONSTANT(if_, "if");
STYLESHEETCONSTANT(import, "import");
STYLESHEETCONSTANT(include, "include");
STYLESHEETCONSTANT(key, "key");
STYLESHEETCONSTANT(message, "message");
STYLESHEETCONSTANT(namespace_alias, "namespace-alias");
STYLESHEETCONSTANT(number, "number");
STYLESHEETCONSTANT(output, "output");
STYLESHEETCONSTANT(param, "param");
STYLESHEETCONSTANT(preserve_space, "preserve-space");
STYLESHEETCONSTANT(processing_instruction, "processing-instruction");
STYLESHEETCONSTANT(strip_space, "strip-space");
STYLESHEETCONSTANT(template_, "template");
STYLESHEETCONSTANT(text, "text");
STYLESHEETCONSTANT(value_of, "value-of");
STYLESHEETCONSTANT(variable, "variable");
STYLESHEETCONSTANT(sort, "sort");
STYLESHEETCONSTANT(with_param, "with-param");
STYLESHEETCONSTANT(when, "when");
STYLESHEETCONSTANT(otherwise, "otherwise");

STYLESHEETCONSTANT(version, "version");
STYLESHEETCONSTANT(extension_element_prefixes, "extension-element-prefixes");
STYLESHEETCONSTANT(exclude_result_prefixes, "exclude-result-prefixes");
STYLESHEETCONSTANT(id, "id");
STYLESHEETCONSTANT(href, "href");
STYLESHEETCONSTANT(select, "select");
STYLESHEETCONSTANT(name, "name");
STYLESHEETCONSTANT(namespace_, "namespace");
STYLESHEETCONSTANT(match, "match");
STYLESHEETCONSTANT(mode, "mode");
STYLESHEETCONSTANT(priority, "priority");
STYLESHEETCONSTANT(use, "use");
STYLESHEETCONSTANT(method, "method");
STYLESHEETCONSTANT(indent, "indent");
STYLESHEETCONSTANT(omit_xml_declaration, "omit-xml-declaration");
STYLESHEETCONSTANT(standalone, "standalone");
STYLESHEETCONSTANT(space, "space");
STYLESHEETCONSTANT(media_type, "media-type");
STYLESHEETCONSTANT(encoding, "encoding");
STYLESHEETCONSTANT(doctype_public, "doctype-public");
STYLESHEETCONSTANT(doctype_system, "doctype-system");
STYLESHEETCONSTANT(stylesheet_prefix, "stylesheet-prefix");
STYLESHEETCONSTANT(result_prefix, "result-prefix");
STYLESHEETCONSTANT(cdata_section_elements, "cdata-section-elements");
STYLESHEETCONSTANT(use_attribute_sets, "use-attribute-sets");
STYLESHEETCONSTANT(test, "test");
STYLESHEETCONSTANT(disable_output_escaping, "disable-output-escaping");
STYLESHEETCONSTANT(lang, "lang");
STYLESHEETCONSTANT(data_type, "data-type");
STYLESHEETCONSTANT(order, "order");
STYLESHEETCONSTANT(case_order, "case-order");
STYLESHEETCONSTANT(terminate, "terminate");
STYLESHEETCONSTANT(hash_default, "#default");

STYLESHEETCONSTANT(no, "no");
STYLESHEETCONSTANT(yes, "yes");
STYLESHEETCONSTANT(utf8, "UTF-8");
STYLESHEETCONSTANT(ascending, "ascending");
STYLESHEETCONSTANT(descending, "descending");
STYLESHEETCONSTANT(upper_first, "upper-first");
STYLESHEETCONSTANT(lower_first, "lower-first");

STYLESHEETCONSTANT(double_hyphen, "--");
STYLESHEETCONSTANT(escaped_double_hyphen, "- -");
STYLESHEETCONSTANT(escaped_pi_end, "? >");

STYLESHEETCONSTANT(root_xpath, "/");
STYLESHEETCONSTANT(current_xpath, ".");
STYLESHEETCONSTANT(namespace_xpath, "namespace::node()");

STYLESHEETCONSTANT(version_property, "xsl:version");
STYLESHEETCONSTANT(vendor_property, "xsl:vendor");
STYLESHEETCONSTANT(vendor_url_property, "xsl:vendor-url");

STYLESHEETCONSTANT(xml, "xml");
STYLESHEETCONSTANT(html, "html");
STYLESHEETCONSTANT(xmlns_colon, "xmlns:");
STYLESHEETCONSTANT(xmlns, "xmlns");
STYLESHEETCONSTANT(auto_ns, "auto-ns");
STYLESHEETCONSTANT(xmlns_uri, "http://www.w3.org/2000/xmlns");
STYLESHEETCONSTANT(xml_uri, "http://www.w3.org/XML/1998/namespace");

STYLESHEETCONSTANT(newline, "\n");

template<class string_type, class string_adaptor> 
const string_type StylesheetConstant<string_type, string_adaptor>::AllowedYesNo[] = { no, yes, string_adaptor::empty_string() };

template<class string_type, class string_adaptor> 
const string_type StylesheetConstant<string_type, string_adaptor>::DefaultPreserve[] = { string_adaptor::construct_from_utf8("default"),
                                                                                         string_adaptor::construct_from_utf8("preserve"), 
                                                                                         string_adaptor::empty_string() };
#undef STYLESHEETCONSTANT
} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

