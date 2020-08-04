////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Boxing.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
TypeEnumImpl<T>::TypeEnumImpl(Symbol name): TypeEnum(name)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
bool TypeEnumImpl<T>::GetValueObject(Symbol name, Ptr<BoxedValue>& value) const
{
    int v;
    if (HasName(name, v))
    {
        value = Boxing::Box<T>(static_cast<T>(v));
        return true;
    }

    return false;
}

}
