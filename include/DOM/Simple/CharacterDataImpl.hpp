#ifndef JEZUK_SimpleDOM_CHARACTERDATAIMPL_H
#define JEZUK_SimpleDOM_CHARACTERDATAIMPL_H

#include <DOM/CharacterData.hpp>
#include <DOM/Simple/NodeImpl.hpp>

#define DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, newValue) \
  DOM::Events::MutationEvent<stringT, string_adaptorT> mutationEvent(NodeImpl<stringT, string_adaptorT>::ownerDoc_->createEvent("MutationEvent")); \
  mutationEvent.initMutationEvent("DOMCharacterDataModified", true, false, Arabica::DOM::Node<stringT, string_adaptorT>(), oldValue, newValue, string_adaptorT::empty_string(), Arabica::DOM::Events::MutationEvent<stringT, string_adaptorT>::MODIFICATION); \
  DOM::Events::EventTarget<stringT, string_adaptorT> eventTarget(this);			\
eventTarget.dispatchEvent(mutationEvent); \

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CharacterDataImpl : virtual public DOM::CharacterData_impl<stringT, string_adaptorT>,
                          public ChildlessNodeImpl<stringT, string_adaptorT>
{
    typedef ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
  public:
    CharacterDataImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        ChildlessNodeImpl<stringT, string_adaptorT>(ownerDoc),
        data_(data)
    { 
    } // CharacterDataImpl

    virtual ~CharacterDataImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::CharacterData methods
    virtual const stringT& getData() const
    {
      return getNodeValue();
    } // getData

    virtual void setData(const stringT& data)
    {
      NodeT::throwIfReadOnly();
      stringT oldValue = data_;
      setNodeValue(data);
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // setData

    virtual int getLength() const
    {
      return static_cast<int>(string_adaptorT::length(data_));
    } // getLength

    virtual stringT substringData(int offset, int count) const
    {
      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);
      if(count < 0)
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      return string_adaptorT::substr(data_, offset, count);
    } // substringData

    virtual void appendData(const stringT& arg)
    {
      NodeT::throwIfReadOnly();
      stringT oldValue = data_;
      string_adaptorT::append(data_, arg);
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // appendData

    virtual void insertData(int offset, const stringT& arg)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      stringT oldValue = data_;
      string_adaptorT::insert(data_, offset, arg);
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // insertData

    virtual void deleteData(int offset, int count)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);
      if(count < 0)
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      stringT oldValue = data_;
      string_adaptorT::replace(data_, offset, count, stringT());
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // deleteData

    virtual void replaceData(int offset, int count, const stringT& arg)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);
      if(count < 0)
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      stringT oldValue = data_;
      string_adaptorT::replace(data_, offset, count, arg);
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // replaceData

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual const stringT& getNodeValue() const 
    {
      return data_;
    } // getNodeValue

    virtual void setNodeValue(const stringT& data)
    {
      NodeT::throwIfReadOnly();

      stringT oldValue = data_;
      data_ = data;
      DISPATCH_DOM_CHARACTERDATA_MODIFIED_EVENT(oldValue, data_);
    } // setNodeValue
  private:
    stringT data_;
}; // class CharacterDataImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

