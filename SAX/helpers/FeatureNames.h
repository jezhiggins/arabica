#ifndef FEATURENAMES_H
#define FEATURENAMES_H
/*
 * $Id$
 */

#include <SAX/helpers/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor_type = default_string_adaptor<string_type> >
struct FeatureNames
{
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;

    const stringT namespaces;
    const stringT namespace_prefixes;
    const stringT validation;
    const stringT external_general;
    const stringT external_parameter;
    const stringT use_attributes2;
    const stringT use_locator2;

    FeatureNames() :
      namespaces(string_adaptorT().makeStringT("http://xml.org/sax/features/namespaces")),
      namespace_prefixes(string_adaptorT().makeStringT("http://xml.org/sax/features/namespace-prefixes")),
      validation(string_adaptorT().makeStringT("http://xml.org/sax/features/validation")),
      external_general(string_adaptorT().makeStringT("http://xml.org/sax/features/external-general-entities")),
      external_parameter(string_adaptorT().makeStringT("http://xml.org/sax/features/external-parameter-entities")),
      use_attributes2(string_adaptorT().makeStringT("http://xml.org/sax/features/use-attributes2")),
      use_locator2(string_adaptorT().makeStringT("http://xml.org/sax/features/use-locator2"))
    {
    } // FeatureNames
}; // class FeatureNames

} // namespace SAX

#endif
// end of file
