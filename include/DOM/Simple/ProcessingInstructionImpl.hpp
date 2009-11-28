#ifndef JEZUK_SimpleDOM_PROCESSINGINSTRUCTIONIMPL_H
#define JEZUK_SimpleDOM_PROCESSINGINSTRUCTIONIMPL_H

#include <DOM/ProcessingInstruction.hpp>
#include <DOM/Simple/NodeImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ProcessingInstructionImpl : public DOM::ProcessingInstruction_impl<stringT, string_adaptorT>,
                                  public ChildlessNodeImpl<stringT, string_adaptorT>
{
  public:
    typedef ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
    typedef DOM::ProcessingInstruction_impl<stringT, string_adaptorT> DOMProcessingInstruction_implT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    ProcessingInstructionImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
                              stringT target,
                              stringT data) : 
        DOMProcessingInstruction_implT(),
        NodeT(ownerDoc),
        target_(target),
        data_(data)
    { 
    } // ProcessingInstructionImpl

    virtual ~ProcessingInstructionImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::ProcessingInstruction methods
    virtual const stringT& getTarget() const { return getNodeName(); }
    
    virtual const stringT& getData() const { return getNodeValue(); }
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

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      return NodeT::ownerDoc_->createProcessingInstruction(target_, data_);
    } // cloneNode

  private:
    stringT target_;
    stringT data_;
}; // class ProcessingInstructionImpl


} // namespace SAX2DOM
} // namespace Arabica

#endif

