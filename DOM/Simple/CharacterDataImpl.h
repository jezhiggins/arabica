#ifndef JEZUK_SimpleDOM_CHARACTERDATAIMPL_H
#define JEZUK_SimpleDOM_CHARACTERDATAIMPL_H

#include <DOM/CharacterData.h>
#include <DOM/Simple/NodeImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CharacterDataImpl : virtual public DOM::CharacterData_impl<stringT>,
                          public ChildlessNodeImpl<stringT, string_adaptorT>
{
  public:
    CharacterDataImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        ChildlessNodeImpl<stringT, string_adaptorT>(ownerDoc),
        data_(data)
    { 
    } // CharacterDataImpl

    virtual ~CharacterDataImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::CharacterData methods
    virtual stringT getData() const
    {
      return getNodeValue();
    } // getData

    virtual void setData(const stringT& data)
    {
      setNodeValue(data);
    } // setData

    virtual int getLength() const
    {
      return static_cast<int>(data_.length());
    } // getLength

    virtual stringT substringData(int offset, int count) const
    {
      return data_.substr(offset, count);
    } // substringData

    virtual void appendData(const stringT& arg)
    {
      throwIfReadOnly();

      data_.append(arg);
    } // appendData

    virtual void insertData(int offset, const stringT& arg)
    {
      throwIfReadOnly();

      if(offset > static_cast<int>(data_.length()))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      data_.insert(offset, arg);
    } // insertData

    virtual void deleteData(int offset, int count)
    {
      throwIfReadOnly();

      if(offset > static_cast<int>(data_.length()))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      data_.replace(offset, count, stringT());
    } // deleteData

    virtual void replaceData(int offset, int count, const stringT& arg)
    {
      throwIfReadOnly();

      if(offset > static_cast<int>(data_.length()))
        throw DOM::DOMException(DOM::DOMException::INDEX_SIZE_ERR);

      data_.replace(offset, count, arg);
    } // replaceData

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual stringT getNodeValue() const 
    {
      return data_;
    } // getNodeValue

    virtual void setNodeValue(const stringT& data)
    {
      throwIfReadOnly();

      data_ = data;
    } // setNodeValue
  private:
    stringT data_;
}; // class CharacterDataImpl

} // namespace SAX2DOM
#endif

