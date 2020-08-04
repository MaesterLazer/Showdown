////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>


namespace Noesis
{


////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ArrayRef<T>::ArrayRef(const T* data, uint32_t size): mBegin(data), mSize(size)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ArrayRef<T>::ArrayRef(const T& value): mBegin(&value), mSize(1)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ArrayRef<T>::ArrayRef(NullPtrT): ArrayRef()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T> template<unsigned N>
ArrayRef<T>::ArrayRef(const T(&data)[N]): mBegin(data), mSize(N)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T> template<unsigned N>
ArrayRef<T>::ArrayRef(const Vector<T, N>& data): mBegin(data.Data()), mSize(data.Size())
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const T* ArrayRef<T>::Begin() const
{
    return mBegin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const T* ArrayRef<T>::End() const
{
    return mBegin + mSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool ArrayRef<T>::Empty() const
{
    return mSize == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline uint32_t ArrayRef<T>::Size() const
{
    return mSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const T* ArrayRef<T>::Data() const
{
    return mBegin;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const T& ArrayRef<T>::operator[](uint32_t i) const
{
    NS_ASSERT(i < mSize);
    return mBegin[i];
}

/// Range-based loop helpers
template<typename T> const T* begin(const ArrayRef<T>& v) { return v.Begin(); }
template<typename T> const T* end(const ArrayRef<T>& v) { return v.End(); }

}
