#ifndef ARABICA_XSLT_KEY_HPP
#define ARABICA_XSLT_KEY_HPP

#include "xslt_execution_context.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Key
{
public: 
  typedef std::vector<Arabica::XPath::MatchExpr<string_type, string_adaptor> > MatchExprList;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathContext;

  Key(MatchExprList& matches,
      XPathExpression& use) :
    matches_(matches),
    use_(use)
  {
  } // Key

  NodeSet lookup(const string_type& value, const XPathContext& context) const
  {
    DOMNode doc = XPath::impl::get_owner_document(context.currentNode());
    DocumentNodeMapIterator nm = nodesPerDocument_.find(doc.underlying_impl());
    if(nm == nodesPerDocument_.end())
      populate(nodesPerDocument_[doc.underlying_impl()], context);

    const NodeMap& nodes = nodesPerDocument_[doc.underlying_impl()];
    NodeMapIterator f = nodes.find(value);
    if(f == nodes.end())
      return NodeSet(0);

    return f->second;
  } // lookup

private:
  typedef std::map<string_type, NodeSet> NodeMap;
  typedef typename NodeMap::const_iterator NodeMapIterator;
  typedef std::map<DOM::Node_impl<string_type, string_adaptor>*, NodeMap> DocumentNodeMap;
  typedef typename DocumentNodeMap::const_iterator DocumentNodeMapIterator;
  typedef typename NodeSet::iterator NodeSetIterator;
  typedef typename MatchExprList::const_iterator MatchExprListIterator;
 
  void populate(NodeMap& nodes, const XPathContext& context) const
  {
    typedef XPath::AxisEnumerator<string_type, string_adaptor> AxisEnum;

    DOMNode current = XPath::impl::get_owner_document(context.currentNode());

    for(AxisEnum ae(current, XPath::DESCENDANT_OR_SELF); *ae != 0; ++ae)
    {
      DOMNode node = *ae;
      for(MatchExprListIterator me = matches_.begin(), mee = matches_.end(); me != mee; ++me)
        if(me->evaluate(node, context))
        {
	        NodeSet ids = use_.evaluateAsNodeSet(node, context);
	        for(NodeSetIterator i = ids.begin(), ie = ids.end(); i != ie; ++i)
	        {
	          string_type id = Arabica::XPath::impl::nodeStringValue<string_type, string_adaptor>(*i);
	          nodes[id].push_back(node);
	        } // for ...
          break;
        } // if ...
    } // for 
  } // populate

  MatchExprList matches_;
  XPathExpression use_;
  mutable DocumentNodeMap nodesPerDocument_;

}; // class Key

template<class string_type, class string_adaptor>
class DeclaredKeys
{
public:
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathContext;

  DeclaredKeys() { }
  ~DeclaredKeys() 
  { 
    for(KeysIterator i = keys_.begin(), ie = keys_.end(); i != ie; ++i)
      for(KeyListIterator k = i->second.begin(), ke = i->second.end(); k != ke; ++k)
  	    delete (*k);
  } // ~DeclaredKeys

  void add(const string_type& name, Key<string_type, string_adaptor>* key)
  {
    keys_[name].push_back(key);
  } // add_key

  NodeSet lookup(const string_type& name,
	               const string_type& id,
                 const XPathContext& context) const
  {
    const KeysIterator k = keys_.find(name);
    if(k == keys_.end())
      throw SAX::SAXException("No key named '" + name + "' has been defined.");
    
    if(k->second.size() == 1)
      return k->second[0]->lookup(id, context);
    
    NodeSet nodes;
    for(KeyListIterator key = k->second.begin(), keye = k->second.end(); key != keye; ++key)    
      nodes.push_back((*key)->lookup(id, context));
    nodes.to_document_order();
    return nodes;
  } // lookup

private:
  typedef std::vector<Key<string_type, string_adaptor>*> KeyList;
  typedef typename std::vector<Key<string_type, string_adaptor>*>::const_iterator KeyListIterator;
  typedef std::map<string_type, KeyList> Keys;
  typedef typename Keys::const_iterator KeysIterator;

  Keys keys_;

  DeclaredKeys(const DeclaredKeys&);
  DeclaredKeys& operator=(const DeclaredKeys&);
  bool operator==(const DeclaredKeys&) const;
}; // class DeclaredKeys

} // namespace XSLT
} // namespace Arabica


#endif
