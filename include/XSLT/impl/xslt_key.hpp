#ifndef ARABICA_XSLT_KEY_HPP
#define ARABICA_XSLT_KEY_HPP

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
    use_(use),
    populated_(false)
  {
  } // Key

  Arabica::XPath::NodeSet<std::string> lookup(const std::string& value) const
  {
    if(!populated_)
      populate();

    NodeMap::const_iterator f = nodes_.find(value);
    if(f == nodes_.end())
      return Arabica::XPath::NodeSet<std::string>(0);

    return f->second;
  } // lookup

private:
  void populate() const
  {
    std::cerr << "Populating key map " << std::endl;
    populated_ = true;
  } // populate

  MatchExprList matches_;
  Arabica::XPath::XPathExpression<std::string> use_;
  mutable bool populated_;

  typedef std::map<std::string, Arabica::XPath::NodeSet<std::string> > NodeMap;
  NodeMap nodes_;
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
				   const std::string& id) const
  {
    const Keys::const_iterator k = keys_.find(name);
    if(k == keys_.end())
      throw SAX::SAXException("No key named '" + name + "' has been defined.");
    
    //if(k->second.size() == 0)
      return k->second[0]->lookup(id);
    
      //Arabica::XPath::NodeSet<std::string> nodes;
      //for(KeyList::const_iterator k = i->second.begin(), ke = i->second.end(); k != ke; ++k)    
      //nodes.a
      //return k->second.lookup(id);
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
