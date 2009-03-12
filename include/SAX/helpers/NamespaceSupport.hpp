#ifndef ARABICA_NAMESPACE_SUPPORT_H
#define ARABICA_NAMESPACE_SUPPORT_H

#include <SAX/ArabicaConfig.hpp>
#include <map>
#include <vector>
#include <functional>
#include <XML/QName.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor>
struct NamespaceConstants
{
  const string_type xml;
  const string_type xmlns;
  const string_type xml_uri;
  const string_type xmlns_uri;
  const string_type xmlns11_uri;
  const string_type colon;

  NamespaceConstants() :
    xml(string_adaptor::construct_from_utf8("xml")),
    xmlns(string_adaptor::construct_from_utf8("xmlns")),
    xml_uri(string_adaptor::construct_from_utf8("http://www.w3.org/XML/1998/namespace")),
    xmlns_uri(),
    xmlns11_uri(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/")),
    colon(string_adaptor::construct_from_utf8(":"))
  {
  } // NamespaceConstants
}; // struct NamespaceContants

/**
 * Encapsulate Namespace logic for use by SAX drivers.
 *
 * <p>This class encapsulates the logic of Namespace processing:
 * it tracks the declarations currently in force for each context
 * and automatically processes qualified XML 1.0 names into their
 * Namespace parts; it can also be used in reverse for generating
 * XML 1.0 from Namespaces.</p>
 *
 * <p>Namespace support objects are reusable, but the reset method
 * must be invoked between each session.</p>
 *
 * <p>Here is a simple session:</p>
 *
 * <pre>
 * NamespaceSupport support;
 *
 * support.pushContext();
 * support.declarePrefix("", "http://www.w3.org/1999/xhtml");
 * support.declarePrefix("dc", "http://www.purl.org/dc#");
 *
 * NamespaceSupport parts = support.processName("p", parts, false);
 * std::cout << "Namespace URI: " << parts.URI << std::endl;
 * std::cout << "Local name: " << parts.localName << std::endl;
 * std::cout << "Raw name: " << parts.rawName << std::endl;

 * parts = support.processName("dc:title", parts, false);
 * std::cout << "Namespace URI: " << parts.URI << std::endl;
 * std::cout << "Local name: " << parts.localName << std::endl;
 * std::cout << "Raw name: " << parts.rawName << std::endl;

 * support.popContext();
 * </pre>
 *
 * <p>Note that this class is optimized for the use case where most
 * elements do not contain Namespace declarations: if the same
 * prefix/URI mapping is repeated for each context (for example), this
 * class will be somewhat less efficient.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 */
template<class string_type, class string_adaptor>
class NamespaceSupport
{
  public:
    typedef std::vector<string_type> stringListT;

    // functions
    NamespaceSupport() 
    { 
      reset(); 
    } // NamespaceSupport

    /**
     * Reset this Namespace support object for reuse.
     *
     * <p>It is necessary to invoke this method before reusing the
     * Namespace support object for a new session.</p>
     */
    void reset()
    {
      contexts_.clear();
      contexts_.push_back(Context());
      contexts_.back().insert(std::make_pair(nsc_.xml, nsc_.xml_uri));
    } // reset

    ////////////////////////////////////////////////////////////////////
    // Context management.
    ////////////////////////////////////////////////////////////////////
    /**
     * Start a new Namespace context.
     *
     * <p>Normally, you should push a new context at the beginning
     * of each XML element: the new context will automatically inherit
     * the declarations of its parent context, but it will also keep
     * track of which declarations were made within this context.</p>
     *
     * <p>The Namespace support object always starts with a base context
     * already in force: in this context, only the "xml" prefix is
     * declared.</p>
     *
     * @see #popContext
     */
    void pushContext()
    {
      contexts_.push_back(Context());
    } // pushContext
    
    /**
     * Revert to the previous Namespace context.
     *
     * <p>Normally, you should pop the context at the end of each
     * XML element.  After popping the context, all Namespace prefix
     * mappings that were previously in force are restored.</p>
     *
     * <p>You must not attempt to declare additional Namespace
     * prefixes after popping a context, unless you push another
     * context first.</p>
     *
     * @see #pushContext
     */
    void popContext()
    {
      contexts_.pop_back();
    } // popContext

    ////////////////////////////////////////////////////////////////////
    // Operations within a context.
    ////////////////////////////////////////////////////////////////////
    /**
     * Declare a Namespace prefix.
     *
     * <p>This method declares a prefix in the current Namespace
     * context; the prefix will remain in force until this context
     * is popped, unless it is shadowed in a descendant context.</p>
     *
     * <p>To declare a default Namespace, use the empty string.  The
     * prefix must not be "xml" or "xmlns".</p>
     *
     * <p>Note that you must <em>not</em> declare a prefix after
     * you've pushed and popped another Namespace.</p>
     *
     * <p>Note that there is an asymmetry in this library: while {@link
     * #getPrefix getPrefix} will not return the default "" prefix,
     * even if you have declared one; to check for a default prefix,
     * you have to look it up explicitly using {@link #getURI getURI}.
     * This asymmetry exists to make it easier to look up prefixes
     * for attribute names, where the default prefix is not allowed.</p>
     *
     * @param prefix The prefix to declare, or the empty string.
     * @param uri The Namespace URI to associate with the prefix.
     * @return true if the prefix was legal, false otherwise
     * @see #processName
     * @see #getURI
     * @see #getPrefix
     */
    bool declarePrefix(const string_type& prefix, const string_type& uri)
    {
      if((prefix == nsc_.xml) || (prefix == nsc_.xmlns))
        return false;

      contexts_.back().insert(std::make_pair(prefix, uri));
      return true;
    } // declarePrefix

    /**
     * Process a raw XML 1.0 name.
     *
     * <p>This method processes a raw XML 1.0 name in the current
     * context by removing the prefix and looking it up among the
     * prefixes currently declared.  
     *
     * <p>If
     * the raw name has a prefix that has not been declared, then
     * the return value will be empty.</p>
     *
     * <p>Note that attribute names are processed differently than
     * element names: an unprefixed element name will received the
     * default Namespace (if any), while an unprefixed attribute name
     * will not.</p>
     *
     * @param qName The raw XML 1.0 name to be processed.
     * @param isAttribute A flag indicating whether this is an
     *        attribute name (true) or an element name (false).
     * @return A <code>Parts</code> holding three strings representing the
     *         Namespace URI (or empty string), the local name, and the raw XML
     *         1.0 name.
     * @see #declarePrefix
     */
  private:
    class URIMapper
    {
    public:
      URIMapper(const NamespaceSupport* ns) : ns_(ns) { }
      string_type operator()(const string_type& prefix) const { return ns_->getURI(prefix); }
    private:
      const NamespaceSupport* const ns_;
    }; // class URIMapper

  public:
    XML::QualifiedName<string_type, string_adaptor> processName(const string_type& rawName, bool isAttribute) const
    {
      try 
      {
        return XML::QualifiedName<string_type, string_adaptor>::parseQName(rawName, isAttribute, URIMapper(this));
      } // try
      catch(const std::runtime_error& ex)
      {
        throw SAX::SAXException(ex.what());
      } // catch
    } // processName

    /**
     * Look up a prefix and get the currently-mapped Namespace URI.
     *
     * <p>This method looks up the prefix in the current context.
     * Use the empty string ("") for the default Namespace.</p>
     *
     * @param prefix The prefix to look up.
     * @return The associated Namespace URI, or empty string if the prefix
     *         is undeclared in this context.
     * @see #getPrefix
     * @see #getPrefixes
     */
    string_type getURI(const string_type& prefix) const
    {
      for(typename contextListT::const_reverse_iterator i = contexts_.rbegin(); i != contexts_.rend(); ++i)
      {
        typename stringMapT::const_iterator u = i->find(prefix);
        if(u != i->end())
          return u->second;
      } // for ...

      return string_type();
    } // getURI

    /**
     * Return one of the prefixes mapped to a Namespace URI.
     *
     * <p>If more than one prefix is currently mapped to the same
     * URI, this method will make an arbitrary selection; if you
     * want all of the prefixes, use the {@link #getPrefixes}
     * method instead.</p>
     *
     * <p><strong>Note:</strong> this will never return the empty (default) prefix;
     * to check for a default prefix, use the {@link #getURI getURI}
     * method with an argument of "".</p>
     *
     * @param uri The Namespace URI.
     * @return One of the prefixes currently mapped to the URI supplied,
     *         or an empty string if none is mapped or if the URI is assigned to
     *         the default Namespace.
     * @see #getPrefixes(const string_type&)
     * @see #getURI
     */
    string_type getPrefix(const string_type& uri) const
    {
      for(typename contextListT::const_reverse_iterator i = contexts_.rbegin(); i != contexts_.rend(); ++i)
      {
        for(typename stringMapT::const_iterator u = i->begin(); u != i->end(); ++u)
          if(u->second == uri)
            return u->first;
      } // for ...

      return string_type();
    } // getPrefix

    /**
     * Returns all prefixes currently declared.
     *
     * <p><strong>Note:</strong> if there is a default prefix, it will not be
     * returned in this enumeration; check for the default prefix
     * using the {@link #getURI getURI} with an argument of "".</p>
     *
     * @return A list of all prefixes declared in the
     *         current context except for the empty (default)
     *         prefix.
     * @see #getDeclaredPrefixes
     * @see #getURI
     */
    stringListT getPrefixes() const
    {
      stringListT prefixes;

      for(typename contextListT::const_reverse_iterator i = contexts_.rbegin(); i != contexts_.rend(); ++i)
      {
        for(typename stringMapT::const_iterator u = i->begin(); u != i->end(); ++u)
          if(!u->first.empty())
            prefixes.push_back(u->first);
      } // for ...
       
      return prefixes;
    } // getPrefixes

    /**
     * Returns a list of all prefixes currently declared for a URI.
     *
     * <p>This method returns prefixes mapped to a specific Namespace
     * URI.  The xml: prefix will be included.  If you want only one
     * prefix that's mapped to the Namespace URI, and you don't care 
     * which one you get, use the {@link #getPrefix getPrefix}
     *  method instead.</p>
     *
     * <p><strong>Note:</strong> the empty (default) prefix is <em>never</em> included
     * in this enumeration; to check for the presence of a default
     * Namespace, use the {@link #getURI getURI} method with an
     * argument of "".</p>
     *
     * @param uri The Namespace URI.
     * @return A list of all prefixes declared in the
     *         current context.
     * @see #getPrefix
     * @see #getDeclaredPrefixes
     * @see #getURI
     */
    stringListT getPrefixes(const string_type& uri) const
    {
      stringListT prefixes;

      for(typename contextListT::const_reverse_iterator i = contexts_.rbegin(); i != contexts_.rend(); ++i)
      {
        for(typename stringMapT::const_iterator u = i->begin(); u != i->end(); ++u)
          if(u->second == uri)
            prefixes.push_back(u->first);
      } // for ...

      return prefixes;
    } // getPrefixes

    /**
     * Return an enumeration of all prefixes declared in this context.
     *
     * <p>The empty (default) prefix will be included in this 
     * enumeration; note that this behaviour differs from that of
     * {@link #getPrefix} and {@link #getPrefixes}.</p>
     *
     * @return An enumeration of all prefixes declared in this
     *         context.
     * @see #getPrefixes
     * @see #getURI
     */
    stringListT getDeclaredPrefixes() const
    {
      stringListT prefixes;

      for(typename stringMapT::const_iterator u = contexts_.back().begin(); u != contexts_.back().end(); ++u)
        prefixes.push_back(u->first);
       
      return prefixes;
    } // getDeclaredPrefixes

  private:
    typedef typename std::multimap<string_type, string_type> stringMapT;
    typedef stringMapT Context;
    typedef typename std::vector<Context> contextListT;

    // member variables
    contextListT contexts_;

    const NamespaceConstants<string_type, string_adaptor> nsc_;

    // no impl
    NamespaceSupport(const NamespaceSupport&);
    NamespaceSupport& operator=(const NamespaceSupport&);
    bool operator==(const NamespaceSupport&) const;
}; // class NamespaceSupport

} // namespace SAX
} // namespace Arabica

#endif // NamespaceSupportH
