#ifndef ARABICA_XSLT_KEY_HPP
#define ARABICA_XSLT_KEY_HPP

#include "xslt_execution_context.hpp"

namespace Arabica
{
namespace XSLT
{

class Key
{
public: 
  typedef std::vector<Arabica::XPath::MatchExpr<std::string> > MatchExprList;

  Key(MatchExprList& matches,
      Arabica::XPath::XPathExpression<std::string>& use) :
    matches_(matches),
    use_(use)
  {
  } // Key

  Arabica::XPath::NodeSet<std::string> lookup(const std::string& value,
                                              const Arabica::XPath::ExecutionContext<std::string>& context) const
  {
    DOM::Node<std::string> doc = XPath::impl::get_owner_document(context.currentNode());
    DocumentNodeMap::const_iterator nm = nodesPerDocument_.find(doc.underlying_impl());
    if(nm == nodesPerDocument_.end())
      populate(nodesPerDocument_[doc.underlying_impl()], context);

    const NodeMap& nodes = nodesPerDocument_[doc.underlying_impl()];
    NodeMap::const_iterator f = nodes.find(value);
    if(f == nodes.end())
      return Arabica::XPath::NodeSet<std::string>(0);

    return f->second;
  } // lookup

private:
  typedef std::map<std::string, Arabica::XPath::NodeSet<std::string> > NodeMap;
  typedef std::map<DOM::Node_impl<std::string, Arabica::default_string_adaptor<std::string> >*, NodeMap> DocumentNodeMap;
 
  void populate(NodeMap& nodes,
                const Arabica::XPath::ExecutionContext<std::string>& context) const
  {
    typedef XPath::AxisEnumerator<std::string> AxisEnum;

    DOM::Node<std::string> current = XPath::impl::get_owner_document(context.currentNode());

    for(AxisEnum ae(current, XPath::DESCENDANT_OR_SELF); *ae != 0; ++ae)
    {
      DOM::Node<std::string> node = *ae;
      for(MatchExprList::const_iterator me = matches_.begin(), mee = matches_.end(); me != mee; ++me)
        if(me->evaluate(node, context))
        {
	  Arabica::XPath::NodeSet<std::string> ids = use_.evaluateAsNodeSet(node, context);
	  for(Arabica::XPath::NodeSet<std::string>::const_iterator i = ids.begin(), ie = ids.end(); i != ie; ++i)
	  {
	    std::string id = Arabica::XPath::impl::nodeStringValue<std::string, Arabica::default_string_adaptor<std::string> >(*i);
	    nodes[id].push_back(node);
	  } // for ...
          break;
        } // if ...
    } // for 
  } // populate

  MatchExprList matches_;
  Arabica::XPath::XPathExpression<std::string> use_;
  mutable DocumentNodeMap nodesPerDocument_;

}; // class Key

class DeclaredKeys
{
public:
  DeclaredKeys() { }
  ~DeclaredKeys() 
  { 
    for(Keys::const_iterator i = keys_.begin(), ie = keys_.end(); i != ie; ++i)
      for(KeyList::const_iterator k = i->second.begin(), ke = i->second.end(); k != ke; ++k)
  	delete (*k);
  } // ~DeclaredKeys

  void add(const std::string& name, Key* key)
  {
    keys_[name].push_back(key);
  } // add_key

  Arabica::XPath::NodeSet<std::string> lookup(const std::string& name,
	                                            const std::string& id,
                                              const Arabica::XPath::ExecutionContext<std::string>& context) const
  {
    const Keys::const_iterator k = keys_.find(name);
    if(k == keys_.end())
      throw SAX::SAXException("No key named '" + name + "' has been defined.");
    
    if(k->second.size() == 1)
      return k->second[0]->lookup(id, context);
    
    Arabica::XPath::NodeSet<std::string> nodes;
    for(KeyList::const_iterator key = k->second.begin(), keye = k->second.end(); key != keye; ++key)    
      nodes.push_back((*key)->lookup(id, context));
    nodes.to_document_order();
    return nodes;
  } // lookup

private:
  typedef std::vector<Key*> KeyList;
  typedef std::map<std::string, KeyList> Keys;

  Keys keys_;

  DeclaredKeys(const DeclaredKeys&);
  DeclaredKeys& operator=(const DeclaredKeys&);
  bool operator==(const DeclaredKeys&) const;
}; // class DeclaredKeys

} // namespace XSLT
} // namespace Arabica


#endif
