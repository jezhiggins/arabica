#ifndef JEZUK_DOM_PROCESSINGINSTRUCTION_H
#define JEZUK_DOM_PROCESSINGINSTRUCTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>

namespace Arabica
{ 
namespace DOM
{

template<class stringT, class string_adaptorT> class ProcessingInstruction_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class ProcessingInstruction : public Node<stringT, string_adaptorT>
{
    typedef Node<stringT, string_adaptorT> NodeT;
  public:
    ProcessingInstruction() : Node<stringT, string_adaptorT>(0) { }
    explicit ProcessingInstruction(ProcessingInstruction_impl<stringT, string_adaptorT>* impl) : Node<stringT, string_adaptorT>(dynamic_cast<Node_impl<stringT, string_adaptorT>*>(impl)) { }
    ProcessingInstruction(const ProcessingInstruction& rhs) : Node<stringT, string_adaptorT>(rhs) { }
    explicit ProcessingInstruction(const Node<stringT, string_adaptorT>& rhs) : Node<stringT, string_adaptorT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT, string_adaptorT>::PROCESSING_INSTRUCTION_NODE)
        throw std::bad_cast();
    }

    const stringT& getTarget() const { return piImpl()->getTarget(); }

    const stringT& getData() const { return piImpl()->getData(); }
    void setData(const stringT& data) { piImpl()->setData(data); }

  private:
    ProcessingInstruction_impl<stringT, string_adaptorT>* piImpl() const { return dynamic_cast<ProcessingInstruction_impl<stringT, string_adaptorT>*>(*NodeT::impl_); }
}; // class DocumentFragment


//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class ProcessingInstruction_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~ProcessingInstruction_impl () { }

    ////////////////////////////////////////////////////////
    // DOM::ProcessingInstruction methods
    virtual const stringT& getTarget() const = 0;

    virtual const stringT& getData() const = 0;
    virtual void setData(const stringT& data) = 0;
}; // class ProcessingInstruction_impl

} // namespace DOM
} // namespace Arabica
#endif

