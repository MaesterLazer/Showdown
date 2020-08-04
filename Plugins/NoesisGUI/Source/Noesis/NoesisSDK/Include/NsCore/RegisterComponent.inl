////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


namespace Noesis
{

class BaseComponent;

NS_CORE_KERNEL_API void RegisterComponent(const TypeClass* type, BaseComponent* (*func)(Symbol));
NS_CORE_KERNEL_API void UnregisterComponent(const TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline void RegisterComponent()
{
    RegisterComponent(TypeOf<T>(), [](Symbol) -> BaseComponent* { return new T; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline void UnregisterComponent()
{
    UnregisterComponent(TypeOf<T>());
}

} 
