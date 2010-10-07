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

class CompiledStylesheet : public Stylesheet
{
  typedef Arabica::XPath::BoolValue<std::string, Arabica::default_string_adaptor<std::string> > BoolValue;
  typedef Arabica::XPath::NumericValue<std::string, Arabica::default_string_adaptor<std::string> > NumericValue;
  typedef Arabica::XPath::StringValue<std::string, Arabica::default_string_adaptor<std::string> > StringValue;
  typedef Arabica::XPath::XPathValue<std::string> Value;

public:
  CompiledStylesheet() :
      output_(new StreamSink(std::cout)),
      error_output_(&std::cerr)
  {
  } // CompiledStylesheet

  virtual ~CompiledStylesheet()
  {
    // let's clean up!
    for(VariableDeclList::const_iterator ci = topLevelVars_.begin(), ce = topLevelVars_.end(); ci != ce; ++ci)
      delete *ci;
    for(ParamList::const_iterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      delete *pi;
    for(TemplateList::const_iterator ti = all_templates_.begin(), te = all_templates_.end(); ti != te; ++ti)
      delete *ti;
  } // ~CompiledStylesheet

  virtual void set_parameter(const std::string& name, bool value)
  {
    set_parameter(name, Value(new BoolValue(value)));
  } // set_parameter
  virtual void set_parameter(const std::string& name, double value)
  {
    set_parameter(name, Value(new NumericValue(value)));
  } // set_parameter
  virtual void set_parameter(const std::string& name, const char* value)
  {
    set_parameter(name, Value(new StringValue(value)));
  } // set_parameter
  virtual void set_parameter(const std::string& name, const std::string& value)
  {
    set_parameter(name, Value(new StringValue(value)));
  } // set_parameter

  virtual void set_output(Sink& sink)
  {
    output_.reset(sink);
  } // set_output

  virtual void set_error_output(std::ostream& os)
  {
    error_output_ = &os;
  } // set_error_output

  virtual void execute(const DOM::Node<std::string>& initialNode) const
  {
    if(initialNode == 0)
      throw std::runtime_error("Input document is empty");

    Arabica::XPath::NodeSet<std::string> ns;
    ns.push_back(initialNode);

    ExecutionContext context(*this, output_.get(), *error_output_);

    // set up variables and so forth
    for(ParamList::const_iterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      (*pi)->declare(context);
    for(VariableDeclList::const_iterator ci = topLevelVars_.begin(), ce = topLevelVars_.end(); ci != ce; ++ci)
      (*ci)->execute(initialNode, context);
    context.freezeTopLevel();

    // go!
    output_.get().asOutput().start_document(output_settings_, output_cdata_elements_);
    applyTemplates(ns, context, "");
    output_.get().asOutput().end_document();
  } // execute

  ////////////////////////////////////////
  const DeclaredKeys& keys() const { return keys_; }

  void add_template(Template* templat)
  {
    typedef std::vector<Arabica::XPath::MatchExpr<std::string> > MatchExprList;
    typedef MatchExprList::const_iterator MatchIterator;

    all_templates_.push_back(templat);

    for(MatchIterator e = templat->compiled_matches().begin(), ee = templat->compiled_matches().end(); e != ee; ++e)
      templates_[templat->precedence()][templat->mode()].push_back(MatchTemplate(*e, templat));

    if(!templat->has_name())
      return;

    NamedTemplates::const_iterator named_template = named_templates_.find(templat->name());
    if(named_template != named_templates_.end())
    {
      const Precedence& existing_precedence = named_template->second->precedence();

      if(existing_precedence > templat->precedence())
	return;

      if(existing_precedence == templat->precedence())
	throw SAX::SAXException("Template named '" +
                                templat->name() + 
				"' already defined");
    } // if ...
     
    named_templates_[templat->name()] = templat;
  } // add_template

  void add_variable(Item* item)
  {
    topLevelVars_.push_back(item);
  } // add_item

  void add_key(const std::string& name,
	             Key* key)
  {
    keys_.add(name, key);
  } // add_key

  void output_settings(const Output::Settings& settings, const Output::CDATAElements& cdata_elements)
  {
    output_settings_ = settings;
    output_cdata_elements_.insert(cdata_elements.begin(), cdata_elements.end());
  } // output_settings

  void prepare() 
  {
    for(TemplateStack::iterator ts = templates_.begin(), tse = templates_.end(); ts != tse; ++ts)
      for(ModeTemplates::iterator ms = ts->second.begin(), mse = ts->second.end(); ms != mse; ++ms)
      {
        MatchTemplates& matches = ms->second;
        std::reverse(matches.begin(), matches.end());
        std::stable_sort(matches.begin(), matches.end());
      } // for ...
  } // prepare

  ////////////////////////////////////////
  void applyTemplates(const Arabica::XPath::NodeSet<std::string>& nodes, ExecutionContext& context, const std::string& mode) const 
  {
    // entirely simple so far
    LastFrame last(context, nodes.size());
    int p = 1;
    for(Arabica::XPath::NodeSet<std::string>::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
    {
      context.setPosition(*n, p++);
      doApplyTemplates(*n, context, mode, Precedence::FrozenPrecedence());
    }
  } // applyTemplates

  void applyTemplates(const DOM::NodeList<std::string>& nodes, ExecutionContext& context, const std::string& mode) const 
  {
    // entirely simple so far
    LastFrame last(context, (size_t)nodes.getLength());
    for(int i = 0, ie = nodes.getLength(); i != ie; ++i)
    {
      context.setPosition(nodes.item(i), i+1);
      doApplyTemplates(nodes.item(i), context, mode, Precedence::FrozenPrecedence());
    }
  } // applyTemplates

  void applyTemplates(const DOM::Node<std::string>& node, ExecutionContext& context, const std::string& mode) const
  {
    LastFrame last(context, -1);
    context.setPosition(node, 1);
    doApplyTemplates(node, context, mode, Precedence::FrozenPrecedence());
  } // applyTemplates

  void callTemplate(const std::string& name, const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    StackFrame frame(context);

    NamedTemplates::const_iterator t = named_templates_.find(name);
    if(t == named_templates_.end())
    {
      std::cerr << "No template named '"; 
      std::cerr << name << "'.  I should be a compile-time error!" << std::endl;
      throw SAX::SAXException("No template named " + name + ".  I should be a compile-time error.  Sorry!");
      return;
    }
     
    t->second->execute(node, context);
  } // callTemplate

  void applyImports(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    doApplyTemplates(node, context, current_mode_, current_generation_);
  } // applyImports

private:
  void doApplyTemplates(const DOM::Node<std::string>& node, 
                        ExecutionContext& context, 
                        const std::string& mode, 
                        const Precedence& generation) const
  {
    StackFrame frame(context);

    std::vector<Precedence> lower_precedences;
    for(TemplateStack::const_iterator ts = templates_.begin(), tse = templates_.end(); ts != tse; ++ts)
      if(generation.is_descendant(ts->first))
        lower_precedences.push_back(ts->first);
    std::sort(lower_precedences.rbegin(), lower_precedences.rend());

    current_mode_ = mode;

    for(std::vector<Precedence>::const_iterator p = lower_precedences.begin(), pe = lower_precedences.end(); p != pe; ++p)
    { 
      current_generation_ = *p;
      ModeTemplates ts = templates_.find(current_generation_)->second;
      ModeTemplates::const_iterator mt = ts.find(mode);
      if(mt != ts.end())
      {
        const MatchTemplates& templates = mt->second;
	      for(MatchTemplates::const_iterator t = templates.begin(), te = templates.end(); t != te; ++t)
	        if(t->match().evaluate(node, context.xpathContext()))
	        {
	          t->action()->execute(node, context);
	          return;
	        } // if ...
      } // if ...
    } // for ...
    defaultAction(node, context, mode);
  } // doApplyTemplates

  void defaultAction(const DOM::Node<std::string>& node, 
                     ExecutionContext& context, 
                     const std::string& mode) const
  {
    switch(node.getNodeType())
    {
      case DOM::Node<std::string>::DOCUMENT_NODE:
      case DOM::Node<std::string>::DOCUMENT_FRAGMENT_NODE:
      case DOM::Node<std::string>::ELEMENT_NODE:
        applyTemplates(node.getChildNodes(), context, mode);
        break;
      case DOM::Node<std::string>::ATTRIBUTE_NODE:
      case DOM::Node<std::string>::TEXT_NODE:
      case DOM::Node<std::string>::CDATA_SECTION_NODE:
        context.sink().characters(node.getNodeValue());
	/*
        {
          const std::string& ch = node.getNodeValue();
          for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
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

  void set_parameter(const std::string& name, Value value)
  {
    params_.push_back(new TopLevelParam("", name, value));
  } // set_parameter

  void set_parameter(const std::string& namespace_uri, const std::string& name, Value value)
  {
    params_.push_back(new TopLevelParam(namespace_uri, name, value));
  } // set_parameter

private:
  class MatchTemplate
  {
  public:
    MatchTemplate(const Arabica::XPath::MatchExpr<std::string>& matchExpr, Template* templat) :
      match_(matchExpr),
      template_(templat) 
    { 
    } // MatchTemplate
    MatchTemplate(const MatchTemplate& rhs) : 
      match_(rhs.match_),
      template_(rhs.template_)
    {
    } // MatchTemplate

    const Arabica::XPath::MatchExpr<std::string>& match() const { return match_; }
    Template* action() const { return template_; }

    bool operator<(const MatchTemplate& rhs) const
    {
      // high priority first!
      return match_.priority() > rhs.match_.priority();
    } // operator<
  private:
    Arabica::XPath::MatchExpr<std::string> match_;
    Template* template_;
  }; // struct MatchTemplate

  typedef std::vector<Template*> TemplateList;
  typedef std::vector<MatchTemplate> MatchTemplates;
  typedef std::map<std::string, MatchTemplates> ModeTemplates;
  typedef std::map<Precedence, ModeTemplates> TemplateStack;
  typedef std::map<std::string, Template*> NamedTemplates;
  
  typedef std::vector<Item*> VariableDeclList;
  typedef std::vector<TopLevelParam*> ParamList;

  TemplateList all_templates_;
  NamedTemplates named_templates_;
  TemplateStack templates_;
  VariableDeclList topLevelVars_;
  DeclaredKeys keys_;
  ParamList params_;

  mutable std::string current_mode_;
  mutable Precedence current_generation_;

  Output::Settings output_settings_;
  Output::CDATAElements output_cdata_elements_;
  SinkHolder output_;
  mutable std::ostream* error_output_;
}; // class CompiledStylesheet

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_COMPILED_STYLESHEET_HPP

