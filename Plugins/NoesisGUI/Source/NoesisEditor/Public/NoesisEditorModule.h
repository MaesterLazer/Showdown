////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define NOESISEDITOR_MODULE_NAME "NoesisEditor"

class NOESISEDITOR_API INoesisEditorModuleInterface : public IModuleInterface
{
public:

	static INoesisEditorModuleInterface* Get();
};
