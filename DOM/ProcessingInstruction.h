#ifndef JEZUK_DOM_PROCESSINGINSTRUCTION_H
#define JEZUK_DOM_PROCESSINGINSTRUCTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>

namespace DOM
{

template<class stringT> class ProcessingInstruction_impl;

template<class stringT>
class ProcessingInstruction : public Node<stringT>
{
  public:
    ProcessingInstruction() : Node<stringT>(0) { }
    explicit ProcessingInstruction(ProcessingInstruction_impl<stringT>* impl) : Node<stringT>(dynamic_cast<Node_impl<stringT>*>(impl)) { }
    ProcessingInstruction(const ProcessingInstruction& rhs) : Node<stringT>(rhs) { }
    explicit ProcessingInstruction(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::PROCESSING_INSTRUCTION_NODE)
        throw std::bad_cast();
    }

    stringT getTarget() const { return piImpl()->getTarget(); }

    stringT getData() const { return piImpl()->getData(); }
    void setData(const stringT& data) { piImpl()->setData(data); }

  private:
    ProcessingInstruction_impl<stringT>* piImpl() const { return dynamic_cast<ProcessingInstruction_impl<stringT>*>(*impl_); }
}; // class DocumentFragment


//////////////////////////////////////////////////////////
template<class stringT>
class ProcessingInstruction_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~ProcessingInstruction_impl () { }

    ////////////////////////////////////////////////////////
    // DOM::ProcessingInstruction methods
    virtual stringT getTarget() const = 0;

    virtual stringT getData() const = 0;
    virtual void setData(const stringT& data) = 0;
}; // class ProcessingInstruction_impl

} // namespace DOM

#endif

