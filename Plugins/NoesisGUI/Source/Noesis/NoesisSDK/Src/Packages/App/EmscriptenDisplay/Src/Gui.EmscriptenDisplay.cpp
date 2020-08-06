////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Package.h>

#include "EmscriptenDisplay.h"


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NS_REGISTER_REFLECTION(App, EmscriptenDisplay)
{
    NS_REGISTER_COMPONENT(EmscriptenDisplay)
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INIT_PACKAGE(App, EmscriptenDisplay)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_SHUTDOWN_PACKAGE(App, EmscriptenDisplay)
{
}
