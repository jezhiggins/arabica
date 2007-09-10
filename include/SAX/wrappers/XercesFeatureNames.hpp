#ifndef ARABICA_XERCES_FEATURENAMES_H
#define ARABICA_XERCES_FEATURENAMES_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{
  template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
  struct XercesFeatureNames
  {
    typedef string_type stringT;

    /** @name SAX 2 Features.
     * These features are defined by the %SAX 2 standard.
     * @{ */
    /** True indicates namespace URIs and unprefixed local names for element and
     * attribute names will be available.
     *
     * Default: true
     *
     * Note:   If the validation feature is set to true, then the document must
     * contain a grammar that supports the use of namespaces.  
     *
     * @see namespace_prefixes
     * @see validation */
    const stringT namespaces;
    /** True indicates XML 1.0 names (with prefixes) and attributes (including
     * xmlns attributes) will be available. 
     *
     * Default: false */
    const stringT namespace_prefixes;
    /** Controls whether the parser is reporting all validity errors; if true,
     * all external entities will be read. 
     *
     * Default: true 
     *
     * @see validation_dynamic
     * @see external_dtd */
    const stringT validation;
    /** @} */

    /** @name Xerces Features.
     * These features are defined by the Xerces parser. 
     * @{ */
    /** True indicates that the parser will validate the document only if a
     * grammar is specified.
     *
     * True indicates that the parser will validate the document only if a
     * grammar is specified.  (validation must be
     * true).
     *
     * False indicates that validation is determined by the state of the
     * validation feature.
     *
     * Default: false  
     *
     * @see validation
     * */
    const stringT validation_dynamic;
    /** True enables the parser's schema support.  
     *
     * False disables the parser's schema support.  
     *
     * Default: true  
     *
     * Note: If set to true, namespace processing must also be turned on.  
     *
     * @see namespaces
     * */
    const stringT validation_schema;
    /** True enables full schema constraint checking.  
     *
     * True enables full schema constraint checking, including checking which
     * may be time-consuming or memory intensive. Currently, particle unique
     * attribution constraint checking and particle derivation restriction
     * checking are controlled by this option.  
     *
     * False disables full schema constraint checking.  
     *
     * Default: false  
     *
     * Note: This feature checks the Schema grammar itself for additional errors
     * that are time-consuming or memory intensive. It does not affect the level
     * of checking performed on document instances that use Schema grammars.
     *
     * @see validation_schema
     * */
    const stringT schema_full_checking;
    /** True indicates that the External DTDs should be loaded.  
     *
     * False indicates that external DTD should be ignored completely. 
     *
     * Default: true 
     *
     * Note:  This feature is ignored and DTD is always loaded when validation
     * is on. 
     *
     * @see validation*/
    const stringT external_dtd;
    /** True indicates that the parser should attempt to continue parsing after
     * a fatal error. 
     *
     * False indicates that the parser should stop on the first fatal error. 
     *
     * Default: false 
     *
     * Note: The behavior of the parser when this feature is set to true is
     * undetermined! Therefore use this feature with extreme caution because the
     * parser may get stuck in an infinite loop or worse. 
     *
     * */
    const stringT continue_after_fatal;
    /** True indicates that the parser will treat validation error as fatal.
     *
     * True indicates that the parser will treat validation error as fatal and
     * will exit depends on the state of continue_after_fatal.
     *
     * False indicates that the parser will report the error and continue
     * processing.  
     *
     * Default: false 
     *
     * Note: Setting this true does not mean the validation error will be
     * printed with the word &quot;Fatal Error&quot;.   It is still printed as
     * &quot;Error&quot;, but the parser will exit if continue_after_fatal is
     * set to false.  
     *
     * @see continue_after_fatal*/
    const stringT validation_errors_fatal;
    /** True indicates that the parser should use cached grammar if it exists in
     * the pool. 
     *
     * False indicates that the parse should parse the schema grammar.
     *
     * Default: false 
     *
     * Note: If cache_grammar is enabled, this feature is set to true
     * automatically. Any setting to this feature by the users is a no-op.
     *
     * @see cache_grammar*/
    const stringT use_cached;
    /** True indicates that the parser should cache the grammar in the pool for
     * re-use in subsequent parses.
     *
     * False indicates that the parser should not cache the grammar in the pool
     *
     * Default: false
     *
     * Note: If set to true, the use_cached
     *
     * @see use_cached*/
    const stringT cache_grammar;
    /** @} */

    XercesFeatureNames() :
      namespaces(	       string_adaptor_type().makeStringT("http://xml.org/sax/features/namespaces")),
      namespace_prefixes(      string_adaptor_type().makeStringT("http://xml.org/sax/features/namespace-prefixes")),
      validation(	       string_adaptor_type().makeStringT("http://xml.org/sax/features/validation")),
      validation_dynamic(      string_adaptor_type().makeStringT("http://apache.org/xml/features/validation/dynamic")),
      validation_schema(       string_adaptor_type().makeStringT("http://apache.org/xml/features/validation/schema")),
      schema_full_checking(    string_adaptor_type().makeStringT("http://apache.org/xml/features/validation/schema-full-checking")),
      external_dtd(	       string_adaptor_type().makeStringT("http://apache.org/xml/features/nonvalidating/load-external-dtd")),
      continue_after_fatal(    string_adaptor_type().makeStringT("http://apache.org/xml/features/continue-after-fatal-error")),
      validation_errors_fatal( string_adaptor_type().makeStringT("http://apache.org/xml/features/validation-error-as-fatal")),
      use_cached(              string_adaptor_type().makeStringT("http://apache.org/xml/features/validation/use-cachedGrammarInParse")),
      cache_grammar(           string_adaptor_type().makeStringT("http://apache.org/xml/features/validation/cache-grammarFromParse"))
    {
    } // XercesFeatureNames
  }; // class XercesFeatureNames
} // namespace SAX
} // namespace Arabica

#endif
// end of file
