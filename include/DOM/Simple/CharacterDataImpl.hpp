#ifndef JEZUK_SimpleDOM_CHARACTERDATAIMPL_H
#define JEZUK_SimpleDOM_CHARACTERDATAIMPL_H

#include <DOM/CharacterData.hpp>
#include <DOM/Simple/NodeImpl.hpp>

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
      setNodeValue(data);
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
      string_adaptorT::append(data_, arg);
    } // appendData

    virtual void insertData(int offset, const stringT& arg)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      string_adaptorT::insert(data_, offset, arg);
    } // insertData

    virtual void deleteData(int offset, int count)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);
      if(count < 0)
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      string_adaptorT::replace(data_, offset, count, stringT());
    } // deleteData

    virtual void replaceData(int offset, int count, const stringT& arg)
    {
      NodeT::throwIfReadOnly();

      if((offset < 0) || (offset > static_cast<int>(string_adaptorT::length(data_))))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);
      if(count < 0)
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      string_adaptorT::replace(data_, offset, count, arg);
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

      data_ = data;
    } // setNodeValue
  private:
    stringT data_;
}; // class CharacterDataImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif
