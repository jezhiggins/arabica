#ifndef JEZUK_DOM_CHARACTERDATA_H
#define JEZUK_DOM_CHARACTERDATA_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>

namespace DOM
{
template<class stringT> class CharacterData_impl;

template<class stringT>
class CharacterData : public Node<stringT>
{
    typedef Node<stringT> NodeT;
  public:
    CharacterData() : Node<stringT>() { }
    explicit CharacterData(CharacterData_impl<stringT>* impl) : Node<stringT>(impl) { }
    CharacterData(const CharacterData& rhs) : Node<stringT>(rhs) { }
    explicit CharacterData(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(dynamic_cast<CharacterData_impl<stringT>*>(rhs.impl()) == 0)
        throw std::bad_cast();
    } // CharacterData

    
    stringT getData() const { return cdImpl()->getData(); }
    void setData(const stringT& data) const 
    { 
      cdImpl()->throwIfReadOnly();
      cdImpl()->setData(data); 
    } // setData

    int getLength() const { return cdImpl()->getLength(); }

    stringT substringData(int offset, int count) const { return cdImpl()->substringData(offset, count); }

    void appendData(const stringT& arg) 
    {
      cdImpl()->throwIfReadOnly();
      cdImpl()->appendData(arg); 
    } // appendData
    void insertData(int offset, const stringT& arg) 
    { 
      cdImpl()->throwIfReadOnly();
      cdImpl()->insertData(offset, arg); 
    } // insertData
    void deleteData(int offset, int count) 
    { 
      cdImpl()->throwIfReadOnly();
      cdImpl()->deleteData(offset, count); 
    } // deleteData
    void replaceData(int offset, int count, const stringT& arg) 
    { 
      cdImpl()->throwIfReadOnly();
      cdImpl()->replaceData(offset, count); 
    } // replaceData

  private:
    CharacterData_impl<stringT>* cdImpl() { return dynamic_cast<CharacterData<stringT>*>(NodeT::impl()); }
}; // class CharacterData

////////////////////////////////////////////////////////////////////
template<class stringT>
class CharacterData_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~CharacterData_impl () { }

    //////////////////////////////////////////////////////////////////
    // DOM::CharacterData methods
    virtual stringT getData() const = 0;
    virtual void setData(const stringT& data) = 0;

    virtual int getLength() const = 0;

    virtual stringT substringData(int offset, int count) const = 0;

    virtual void appendData(const stringT& arg) = 0;
    virtual void insertData(int offset, const stringT& arg) = 0;
    virtual void deleteData(int offset, int count) = 0;
    virtual void replaceData(int offset, int count, const stringT& arg) = 0;
}; // CharacterData_impl


} // namespace DOM

#endif
