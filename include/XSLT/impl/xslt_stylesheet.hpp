#ifndef ARABICA_XSLT_STYLESHEET_HPP
#define ARABICA_XSLT_STYLESHEET_HPP

#include <vector>
#include <iostream>
#include <XPath/XPath.hpp>

#include "xslt_execution_context.hpp"
#include "xslt_template.hpp"
#include "xslt_top_level_param.hpp"

namespace Arabica
{
namespace XSLT
{

class Stylesheet
{
  typedef Arabica::XPath::BoolValue<std::string, Arabica::default_string_adaptor<std::string> > BoolValue;
  typedef Arabica::XPath::NumericValue<std::string, Arabica::default_string_adaptor<std::string> > NumericValue;
  typedef Arabica::XPath::StringValue<std::string, Arabica::default_string_adaptor<std::string> > StringValue;
  typedef Arabica::XPath::XPathValuePtr<std::string> ValuePtr;

public:
  Stylesheet() :
      output_(new StreamSink(std::cout)),
      error_output_(&std::cerr)
  {
    push_import_precedence();
  } // Stylesheet

  ~Stylesheet()
  {
    // let's clean up!
    for(ItemStack::const_iterator isi = items_.begin(), ise = items_.end(); isi != ise; ++isi)
      for(ItemList::const_iterator ci = isi->begin(), ce = isi->end(); ci != ce; ++ci)
        delete *ci;
    for(ParamList::const_iterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      delete *pi;
    for(TemplateList::const_iterator ti = all_templates_.begin(), te = all_templates_.end(); ti != te; ++ti)
      delete *ti;
  } // ~Stylesheet

  void set_parameter(const std::string& name, bool value)
  {
    set_parameter(name, ValuePtr(new BoolValue(value)));
  } // set_parameter
  void set_parameter(const std::string& name, double value)
  {
    set_parameter(name, ValuePtr(new NumericValue(value)));
  } // set_parameter
  void set_parameter(const std::string& name, const char* value)
  {
    set_parameter(name, ValuePtr(new StringValue(value)));
  } // set_parameter
  void set_parameter(const std::string& name, const std::string& value)
  {
    set_parameter(name, ValuePtr(new StringValue(value)));
  } // set_parameter

  void set_output(Sink& sink)
  {
    output_.reset(sink);
  } // set_output

  void set_error_output(std::ostream& os)
  {
    error_output_ = &os;
  } // set_error_output

  void execute(DOM::Node<std::string>& initialNode) const
  {
    if(initialNode == 0)
      throw std::runtime_error("Input document is empty");

    Arabica::XPath::NodeSet<std::string> ns;
    ns.push_back(initialNode);

    ExecutionContext context(*this, output_.get(), *error_output_);

    // set up variables and so forth
    for(ParamList::const_iterator pi = params_.begin(), pe = params_.end(); pi != pe; ++pi)
      (*pi)->declare(context);
    for(ItemStack::const_iterator isi = items_.begin(), ise = items_.end(); isi != ise; ++isi)
    {
      for(ItemList::const_iterator ci = isi->begin(), ce = isi->end(); ci != ce; ++ci)
        (*ci)->execute(initialNode, context);
      context.pushVariablePrecendence();
    } // for ...
    context.freezeTopLevel();

    // go!
    output_.get().asOutput().start_document(output_settings_);
    applyTemplates(ns, context, std::pair<std::string, std::string>("", ""));
    output_.get().asOutput().end_document();
  } // execute

  ////////////////////////////////////////
  void add_template(Template* templat)
  {
    typedef std::vector<Arabica::XPath::MatchExpr<std::string> > MatchExprList;
    typedef MatchExprList::const_iterator MatchIterator;

    all_templates_.push_back(templat);

    for(MatchIterator e = templat->compiled_matches().begin(), ee = templat->compiled_matches().end(); e != ee; ++e)
      templates_.back()[templat->mode()].push_back(MatchTemplate(*e, templat));

    if(!templat->has_name())
      return;

    if(named_templates_.find(templat->name()) != named_templates_.end())
    {
      std::cerr << "Template named '";
      if(!templat->name().first.empty())
        std::cerr << "{" << templat->name().first << "}";
      std::cerr << templat->name().second << "' already defined" << std::endl;
      return;
    }
     
    named_templates_[templat->name()] = templat;
  } // add_template

  void push_import_precedence()
  {
    templates_.push_back(ModeTemplates());
    items_.push_back(ItemList());
  } // push_import_precedence

  void add_item(Item* item)
  {
    items_.back().push_back(item);
  } // add_item

  void output_settings(const Output::Settings& settings)
  {
    output_settings_ = settings;
  } // output_settings

  void prepare() 
  {
    for(TemplateStack::iterator ts = templates_.begin(), tse = templates_.end(); ts != tse; ++ts)
      for(ModeTemplates::iterator ms = ts->begin(), mse = ts->end(); ms != mse; ++ms)
      {
        MatchTemplates& matches = ms->second;
        std::reverse(matches.begin(), matches.end());
        std::stable_sort(matches.begin(), matches.end());
      } // for ...
  } // prepare

  ////////////////////////////////////////
  void applyTemplates(const Arabica::XPath::NodeSet<std::string>& nodes, ExecutionContext& context, const std::pair<std::string, std::string>& mode) const 
  {
    // entirely simple so far
    LastFrame last(context, nodes.size());
    int p = 1;
    for(Arabica::XPath::NodeSet<std::string>::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
    {
      context.setPosition(*n, p++);
      doApplyTemplates(*n, context, mode, 0);
    }
  } // applyTemplates

  void applyTemplates(const DOM::NodeList<std::string>& nodes, ExecutionContext& context, const std::pair<std::string, std::string>& mode) const 
  {
    // entirely simple so far
    LastFrame last(context, (size_t)nodes.getLength());
    for(int i = 0, ie = nodes.getLength(); i != ie; ++i)
    {
      context.setPosition(nodes.item(i), i+1);
      doApplyTemplates(nodes.item(i), context, mode, 0);
    }
  } // applyTemplates

  void applyTemplates(const DOM::Node<std::string>& node, ExecutionContext& context, const std::pair<std::string, std::string>& mode) const
  {
    LastFrame last(context, -1);
    context.setPosition(node, 1);
    doApplyTemplates(node, context, mode, 0);
  } // applyTemplates

  void callTemplate(const std::pair<std::string, std::string>& name, const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    StackFrame frame(context);

    NamedTemplates::const_iterator t = named_templates_.find(name);
    if(t == named_templates_.end())
    {
      std::cerr << "No template named '"; 
      if(!name.first.empty())
        std::cerr << "{" << name.first << "}";
      std::cerr << name.second << "'.  I should be a compile-time error!" << std::endl;
      throw SAX::SAXException("No template named {" + name.first + "}" + name.second + ".  I should be a compile-time error.  Sorry!");
      return;
    }
     
    t->second->execute(node, context);
  } // callTemplate

  void applyImports(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    doApplyTemplates(node, context, current_mode_, current_generation_+1);
  } // applyImports

private:
  void doApplyTemplates(const DOM::Node<std::string>& node, 
                        ExecutionContext& context, 
                        const std::pair<std::string, std::string>& mode, 
                        int generation) const
  {
    StackFrame frame(context);

    current_mode_ = mode;
    current_generation_ = generation;

    for(TemplateStack::const_iterator ts = templates_.begin()+generation, tse = templates_.end(); ts != tse; ++ts)
    {      
      ModeTemplates::const_iterator mt = ts->find(mode);
      if(mt != ts->end())
      {
        const MatchTemplates& templates = mt->second;
	      for(MatchTemplates::const_iterator t = templates.begin(), te = templates.end(); t != te; ++t)
	        if(t->match().evaluate(node, context.xpathContext()))
	        {
	          t->action()->execute(node, context);
	          return;
	        } // if ...
      } // if ...
      ++current_generation_;
    } // for ...
    defaultAction(node, context, mode);
  } // doApplyTemplates

  void defaultAction(const DOM::Node<std::string>& node, 
                     ExecutionContext& context, 
                     const std::pair<std::string, std::string>& mode) const
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

  void set_parameter(const std::string& name, ValuePtr value)
  {
    params_.push_back(new TopLevelParam("", name, value));
  } // set_parameter

  void set_parameter(const std::string& namespace_uri, const std::string& name, ValuePtr value)
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
  typedef std::map<std::pair<std::string, std::string>, MatchTemplates> ModeTemplates;
  typedef std::vector<ModeTemplates> TemplateStack;
  typedef std::map<std::pair<std::string, std::string>, Template*> NamedTemplates;
  
  typedef std::vector<Item*> ItemList;
  typedef std::vector<ItemList> ItemStack;

  typedef std::vector<TopLevelParam*> ParamList;

  TemplateList all_templates_;
  NamedTemplates named_templates_;
  TemplateStack templates_;
  ItemStack items_;
  ParamList params_;

  mutable std::pair<std::string, std::string> current_mode_;
  mutable int current_generation_;

  Output::Settings output_settings_;
  SinkHolder output_;
  mutable std::ostream* error_output_;
}; // class Stylesheet

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_STYLESHEET_HPP

