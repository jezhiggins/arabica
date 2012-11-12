#ifndef ARABICA_XSLT_COMPILED_STYLESHEET_HPP
#define ARABICA_XSLT_COMPILED_STYLESHEET_HPP

#include <vector>
#include <iostream>
#include <XPath/XPath.hpp>

#include "xslt_execution_context.hpp"
#include "xslt_template.hpp"
#include "xslt_top_level_param.hpp"
#include "xslt_key.hpp"
#include "xslt_stylesheet.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class CompiledStylesheet : public Stylesheet<string_type, string_adaptor>
{
public:
  typedef Arabica::XPath::BoolValue<string_type, string_adaptor> BoolValue;
  typedef Arabica::XPath::NumericValue<string_type, string_adaptor> NumericValue;
  typedef Arabica::XPath::StringValue<string_type, string_adaptor> StringValue;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> Value;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef DOM::NodeList<string_type, string_adaptor> DOMNodeList;

  CompiledStylesheet() :
      output_(new StreamSink<string_type, string_adaptor>(std::wcout)),
      error_output_(&std::wcerr)
  {
  } // CompiledStylesheet

  virtual ~CompiledStylesheet()
  {
    // let's clean up!
    for(VariableDeclListIterator ci = topLevelVars_.begin(), ce = topLevelVars_.end(); ci != ce; ++ci)
      delete *ci;
    for(ParamListIterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      delete *pi;
    for(TemplateListIterator ti = all_templates_.begin(), te = all_templates_.end(); ti != te; ++ti)
      delete *ti;
  } // ~CompiledStylesheet

  virtual void set_parameter(const string_type& name, bool value)
  {
    set_parameter(name, Value(new BoolValue(value)));
  } // set_parameter
  virtual void set_parameter(const string_type& name, double value)
  {
    set_parameter(name, Value(new NumericValue(value)));
  } // set_parameter
  virtual void set_parameter(const string_type& name, const char* value)
  {
    set_parameter(name, Value(new StringValue(value)));
  } // set_parameter
  virtual void set_parameter(const string_type& name, const string_type& value)
  {
    set_parameter(name, Value(new StringValue(value)));
  } // set_parameter

  virtual void set_output(Sink<string_type, string_adaptor>& sink)
  {
    output_.reset(sink);
  } // set_output

  virtual void set_error_output(std::basic_ostream<typename string_adaptor::value_type>& os)
  {
    error_output_ = &os;
  } // set_error_output

  virtual void execute(const DOMNode& initialNode) const
  {
    if(initialNode == 0)
      throw std::runtime_error("Input document is empty");

    NodeSet ns;
    ns.push_back(initialNode);

    ExecutionContext<string_type, string_adaptor> context(*this, output_.get(), *error_output_);

    // set up variables and so forth
    for(ParamListIterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      (*pi)->declare(context);
    for(VariableDeclListIterator ci = topLevelVars_.begin(), ce = topLevelVars_.end(); ci != ce; ++ci)
      (*ci)->execute(initialNode, context);
    context.freezeTopLevel();

    // go!
    output_.get().asOutput().start_document(output_settings_, output_cdata_elements_);
    applyTemplates(ns, context, string_adaptor::empty_string());
    output_.get().asOutput().end_document();
  } // execute

  ////////////////////////////////////////
  const DeclaredKeys<string_type, string_adaptor>& keys() const { return keys_; }

  void add_template(Template<string_type, string_adaptor>* templat)
  {
    typedef typename Template<string_type, string_adaptor>::MatchExprList MatchExprList;
    typedef typename MatchExprList::const_iterator MatchIterator;

    all_templates_.push_back(templat);

    for(MatchIterator e = templat->compiled_matches().begin(), ee = templat->compiled_matches().end(); e != ee; ++e)
      templates_[templat->precedence()][templat->mode()].push_back(MatchTemplate(*e, templat));

    if(!templat->has_name())
      return;

    NamedTemplatesIterator named_template = named_templates_.find(templat->name());
    if(named_template != named_templates_.end())
    {
      const Precedence& existing_precedence = named_template->second->precedence();

      if(existing_precedence > templat->precedence())
	      return;

      if(existing_precedence == templat->precedence())
        	throw SAX::SAXException("Template named '" +
                                  string_adaptor::asStdString(templat->name()) + 
				                          "' already defined");
    } // if ...
     
    named_templates_[templat->name()] = templat;
  } // add_template

  void add_variable(Item<string_type, string_adaptor>* item)
  {
    topLevelVars_.push_back(item);
  } // add_item

  void add_key(const string_type& name,
	             Key<string_type, string_adaptor>* key)
  {
    keys_.add(name, key);
  } // add_key

  void output_settings(const typename Output<string_type, string_adaptor>::Settings& settings, 
                       const typename Output<string_type, string_adaptor>::CDATAElements& cdata_elements)
  {
    output_settings_ = settings;
    output_cdata_elements_.insert(cdata_elements.begin(), cdata_elements.end());
  } // output_settingsp

  void prepare() 
  {
    for(typename TemplateStack::iterator ts = templates_.begin(), tse = templates_.end(); ts != tse; ++ts)
      for(typename ModeTemplates::iterator ms = ts->second.begin(), mse = ts->second.end(); ms != mse; ++ms)
      {
        MatchTemplates& matches = ms->second;
        std::reverse(matches.begin(), matches.end());
        std::stable_sort(matches.begin(), matches.end());
      } // for ...
  } // prepare

  ////////////////////////////////////////
  void applyTemplates(const NodeSet& nodes, ExecutionContext<string_type, string_adaptor>& context, const string_type& mode) const 
  {
    // entirely simple so far
    LastFrame<string_type, string_adaptor> last(context, nodes.size());
    int p = 1;
    for(typename NodeSet::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
    {
      context.setPosition(*n, p++);
      doApplyTemplates(*n, context, mode, Precedence::FrozenPrecedence());
    }
  } // applyTemplates

  void applyTemplates(const DOMNodeList& nodes, ExecutionContext<string_type, string_adaptor>& context, const string_type& mode) const 
  {
    // entirely simple so far
    LastFrame<string_type, string_adaptor> last(context, (size_t)nodes.getLength());
    for(int i = 0, ie = nodes.getLength(); i != ie; ++i)
    {
      context.setPosition(nodes.item(i), i+1);
      doApplyTemplates(nodes.item(i), context, mode, Precedence::FrozenPrecedence());
    }
  } // applyTemplates

  void applyTemplates(const DOMNode& node, ExecutionContext<string_type, string_adaptor>& context, const string_type& mode) const
  {
    LastFrame<string_type, string_adaptor> last(context, -1);
    context.setPosition(node, 1);
    doApplyTemplates(node, context, mode, Precedence::FrozenPrecedence());
  } // applyTemplates

  void callTemplate(const string_type& name, const DOMNode& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    StackFrame<string_type, string_adaptor> frame(context);

    NamedTemplatesIterator t = named_templates_.find(name);
    if(t == named_templates_.end())
    {
      std::cerr << "No template named '"; 
      std::cerr << string_adaptor::asStdString(name) << "'.  I should be a compile-time error!" << std::endl;
      throw SAX::SAXException("No template named " + string_adaptor::asStdString(name) + ".  I should be a compile-time error.  Sorry!");
      return;
    }
     
    t->second->execute(node, context);
  } // callTemplate

  void applyImports(const DOMNode& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    doApplyTemplates(node, context, current_mode_, current_generation_);
  } // applyImports

private:
  void doApplyTemplates(const DOMNode& node, 
                        ExecutionContext<string_type, string_adaptor>& context, 
                        const string_type& mode, 
                        const Precedence& generation) const
  {
    StackFrame<string_type, string_adaptor> frame(context);

    std::vector<Precedence> lower_precedences;
    for(TemplateStackIterator ts = templates_.begin(), tse = templates_.end(); ts != tse; ++ts)
      if(generation.is_descendant(ts->first))
        lower_precedences.push_back(ts->first);
    std::sort(lower_precedences.rbegin(), lower_precedences.rend());

    current_mode_ = mode;

    for(std::vector<Precedence>::const_iterator p = lower_precedences.begin(), pe = lower_precedences.end(); p != pe; ++p)
    { 
      current_generation_ = *p;
      ModeTemplates ts = templates_.find(current_generation_)->second;
      ModeTemplatesIterator mt = ts.find(mode);
      if(mt != ts.end())
      {
        const MatchTemplates& templates = mt->second;
	      for(MatchTemplatesIterator t = templates.begin(), te = templates.end(); t != te; ++t)
	        if(t->match().evaluate(node, context.xpathContext()))
	        {
	          t->action()->execute(node, context);
	          return;
	        } // if ...
      } // if ...
    } // for ...
    defaultAction(node, context, mode);
  } // doApplyTemplates

  void defaultAction(const DOMNode& node, 
                     ExecutionContext<string_type, string_adaptor>& context, 
                     const string_type& mode) const
  {
    switch(node.getNodeType())
    {
      case DOM::Node_base::DOCUMENT_NODE:
      case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
      case DOM::Node_base::ELEMENT_NODE:
        applyTemplates(node.getChildNodes(), context, mode);
        break;
      case DOM::Node_base::ATTRIBUTE_NODE:
      case DOM::Node_base::TEXT_NODE:
      case DOM::Node_base::CDATA_SECTION_NODE:
        context.sink().characters(node.getNodeValue());
	/*
        {
          const string_type& ch = node.getNodeValue();
          for(string_type::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
            if(!Arabica::XML::is_space(*i))
            {
              context.sink().characters(ch);
              return;
            } // if ...
        } 
	*/
        break;
      default:
        ;// nothing!
    } // switch
  } // defaultAction

  void set_parameter(const string_type& name, Value value)
  {
    params_.push_back(new TopLevelParam<string_type, string_adaptor>(string_adaptor::empty_string(), name, value));
  } // set_parameter

  void set_parameter(const string_type& namespace_uri, const string_type& name, Value value)
  {
    params_.push_back(new TopLevelParam<string_type, string_adaptor>(namespace_uri, name, value));
  } // set_parameter

private:
  class MatchTemplate
  {
  public:
    MatchTemplate(const Arabica::XPath::MatchExpr<string_type, string_adaptor>& matchExpr, Template<string_type, string_adaptor>* templat) :
      match_(matchExpr),
      template_(templat) 
    { 
    } // MatchTemplate
    MatchTemplate(const MatchTemplate& rhs) : 
      match_(rhs.match_),
      template_(rhs.template_)
    {
    } // MatchTemplate

    const Arabica::XPath::MatchExpr<string_type, string_adaptor>& match() const { return match_; }
    Template<string_type, string_adaptor>* action() const { return template_; }

    bool operator<(const MatchTemplate& rhs) const
    {
      // high priority first!
      return match_.priority() > rhs.match_.priority();
    } // operator<
  private:
    Arabica::XPath::MatchExpr<string_type, string_adaptor> match_;
    Template<string_type, string_adaptor>* template_;
  }; // struct MatchTemplate

  typedef std::vector<Template<string_type, string_adaptor>*> TemplateList;
  typedef typename TemplateList::const_iterator TemplateListIterator;
  typedef std::vector<MatchTemplate> MatchTemplates;
  typedef typename MatchTemplates::const_iterator MatchTemplatesIterator;
  typedef std::map<string_type, MatchTemplates> ModeTemplates;
  typedef typename ModeTemplates::const_iterator ModeTemplatesIterator;
  typedef std::map<Precedence, ModeTemplates> TemplateStack;
  typedef typename TemplateStack::const_iterator TemplateStackIterator;
  typedef std::map<string_type, Template<string_type, string_adaptor>*> NamedTemplates;
  typedef typename NamedTemplates::const_iterator NamedTemplatesIterator;
  
  typedef std::vector<Item<string_type, string_adaptor>*> VariableDeclList;
  typedef typename std::vector<Item<string_type, string_adaptor>*>::const_iterator VariableDeclListIterator;
  typedef std::vector<TopLevelParam<string_type, string_adaptor>*> ParamList;
  typedef typename ParamList::const_iterator ParamListIterator;

  TemplateList all_templates_;
  NamedTemplates named_templates_;
  TemplateStack templates_;
  VariableDeclList topLevelVars_;
  DeclaredKeys<string_type, string_adaptor> keys_;
  ParamList params_;

  mutable string_type current_mode_;
  mutable Precedence current_generation_;

  typename Output<string_type, string_adaptor>::Settings output_settings_;
  typename Output<string_type, string_adaptor>::CDATAElements output_cdata_elements_;
  SinkHolder<string_type, string_adaptor> output_;
  mutable std::basic_ostream<typename string_adaptor::value_type>* error_output_;
}; // class CompiledStylesheet

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_COMPILED_STYLESHEET_HPP

