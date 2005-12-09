#ifndef JEZUK_SimpleDOM_PROCESSINGINSTRUCTIONIMPL_H
#define JEZUK_SimpleDOM_PROCESSINGINSTRUCTIONIMPL_H

#include <DOM/ProcessingInstruction.h>
#include <DOM/Simple/NodeImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ProcessingInstructionImpl : public DOM::ProcessingInstruction_impl<stringT>,
                                  public ChildlessNodeImpl<stringT, string_adaptorT>
{
    typedef ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
  public:
    ProcessingInstructionImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
                              stringT target,
                              stringT data) : 
        DOM::ProcessingInstruction_impl<stringT>(),
        ChildlessNodeImpl<stringT, string_adaptorT>(ownerDoc),
        target_(target),
        data_(data)
    { 
    } // ProcessingInstructionImpl

    virtual ~ProcessingInstructionImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::ProcessingInstruction methods
    virtual stringT getTarget() const { return getNodeName(); }
    
    virtual stringT getData() const { return getNodeValue(); }
    virtual void setData(const stringT& data) { setNodeValue(data); }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::PROCESSING_INSTRUCTION_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return target_;
    } // getNodeName

    virtual const stringT& getNodeValue() const
    {
      return data_;
    } // getNodeValue

    virtual void setNodeValue(const stringT& nodeValue)
    {
      NodeT::throwIfReadOnly();

      data_ = nodeValue;
    } // setNodeValue

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return NodeT::ownerDoc_->createProcessingInstruction(target_, data_);
    } // cloneNode

  private:
    stringT target_;
    stringT data_;
}; // class ProcessingInstructionImpl


} // namespace SAX2DOM

#endif

