// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EHTML_DirectoryType : uint8;
enum class EHtmlMenuSystem : uint8;
enum class EHTML_FileType : uint8;
class UHTMLMenu;
enum class EHTML_JavascriptFunction : uint8;
class UJavascriptBean;
#ifdef HTMLMENUMAIN_HTMLMenu_generated_h
#error "HTMLMenu.generated.h already included, missing '#pragma once' in HTMLMenu.h"
#endif
#define HTMLMENUMAIN_HTMLMenu_generated_h

#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_73_DELEGATE \
struct HTMLMenu_eventJavascriptEventMouseUp_Parms \
{ \
	float X; \
	float Y; \
	int32 button; \
}; \
static inline void FJavascriptEventMouseUp_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventMouseUp, const float X, const float Y, const int32 button) \
{ \
	HTMLMenu_eventJavascriptEventMouseUp_Parms Parms; \
	Parms.X=X; \
	Parms.Y=Y; \
	Parms.button=button; \
	JavascriptEventMouseUp.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_67_DELEGATE \
struct HTMLMenu_eventJavascriptEventMouseDown_Parms \
{ \
	float X; \
	float Y; \
	int32 button; \
}; \
static inline void FJavascriptEventMouseDown_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventMouseDown, const float X, const float Y, const int32 button) \
{ \
	HTMLMenu_eventJavascriptEventMouseDown_Parms Parms; \
	Parms.X=X; \
	Parms.Y=Y; \
	Parms.button=button; \
	JavascriptEventMouseDown.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_65_DELEGATE \
struct HTMLMenu_eventOnBeforePopup_Parms \
{ \
	FString URL; \
	FString Frame; \
}; \
static inline void FOnBeforePopup_DelegateWrapper(const FMulticastScriptDelegate& OnBeforePopup, const FString& URL, const FString& Frame) \
{ \
	HTMLMenu_eventOnBeforePopup_Parms Parms; \
	Parms.URL=URL; \
	Parms.Frame=Frame; \
	OnBeforePopup.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_64_DELEGATE \
struct HTMLMenu_eventOnUrlChanged_Parms \
{ \
	FText Text; \
}; \
static inline void FOnUrlChanged_DelegateWrapper(const FMulticastScriptDelegate& OnUrlChanged, FText const& Text) \
{ \
	HTMLMenu_eventOnUrlChanged_Parms Parms; \
	Parms.Text=Text; \
	OnUrlChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_SPARSE_DATA
#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execappEnterBackgroundDelegate); \
	DECLARE_FUNCTION(execappReactivtedDelegate); \
	DECLARE_FUNCTION(execreconnectMobile); \
	DECLARE_FUNCTION(execGetUrl); \
	DECLARE_FUNCTION(execGetTitleText); \
	DECLARE_FUNCTION(execExecuteJavascript); \
	DECLARE_FUNCTION(execLoadString); \
	DECLARE_FUNCTION(execLoadURL); \
	DECLARE_FUNCTION(execfileToBase64String); \
	DECLARE_FUNCTION(execbase64StringToBytes); \
	DECLARE_FUNCTION(execbytesToBase64String); \
	DECLARE_FUNCTION(execbase64StringToString); \
	DECLARE_FUNCTION(execstringToBase64String); \
	DECLARE_FUNCTION(execgetSystemType); \
	DECLARE_FUNCTION(execLoadPDF_FileIntoViewer); \
	DECLARE_FUNCTION(execLoadAllFilesFromDirectory); \
	DECLARE_FUNCTION(execloadHTML_File); \
	DECLARE_FUNCTION(exectriggerKeyAction); \
	DECLARE_FUNCTION(execgenerateHTML_File); \
	DECLARE_FUNCTION(execgetHTMLMouseCursorPosition); \
	DECLARE_FUNCTION(execjavascriptMousePosition); \
	DECLARE_FUNCTION(execjavascriptClientTravel); \
	DECLARE_FUNCTION(execjavascriptGetGraphics); \
	DECLARE_FUNCTION(execjavascriptApplyAndSaveGraphics); \
	DECLARE_FUNCTION(execjavascriptQuitGame); \
	DECLARE_FUNCTION(execjavascriptConsoleCommand); \
	DECLARE_FUNCTION(exectriggerUE4EventMouseUp); \
	DECLARE_FUNCTION(exectriggerUE4EventMouseDown); \
	DECLARE_FUNCTION(exectriggerUE4EventWithJSON); \
	DECLARE_FUNCTION(exectriggerUE4EventWithMap); \
	DECLARE_FUNCTION(exectriggerUE4EventWithBlank); \
	DECLARE_FUNCTION(exectriggerUE4EventWithTag); \
	DECLARE_FUNCTION(execregisterJavascriptEvent); \
	DECLARE_FUNCTION(execJavascriptEventMouseUp); \
	DECLARE_FUNCTION(execJavascriptEventMouseDown);


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execappEnterBackgroundDelegate); \
	DECLARE_FUNCTION(execappReactivtedDelegate); \
	DECLARE_FUNCTION(execreconnectMobile); \
	DECLARE_FUNCTION(execGetUrl); \
	DECLARE_FUNCTION(execGetTitleText); \
	DECLARE_FUNCTION(execExecuteJavascript); \
	DECLARE_FUNCTION(execLoadString); \
	DECLARE_FUNCTION(execLoadURL); \
	DECLARE_FUNCTION(execfileToBase64String); \
	DECLARE_FUNCTION(execbase64StringToBytes); \
	DECLARE_FUNCTION(execbytesToBase64String); \
	DECLARE_FUNCTION(execbase64StringToString); \
	DECLARE_FUNCTION(execstringToBase64String); \
	DECLARE_FUNCTION(execgetSystemType); \
	DECLARE_FUNCTION(execLoadPDF_FileIntoViewer); \
	DECLARE_FUNCTION(execLoadAllFilesFromDirectory); \
	DECLARE_FUNCTION(execloadHTML_File); \
	DECLARE_FUNCTION(exectriggerKeyAction); \
	DECLARE_FUNCTION(execgenerateHTML_File); \
	DECLARE_FUNCTION(execgetHTMLMouseCursorPosition); \
	DECLARE_FUNCTION(execjavascriptMousePosition); \
	DECLARE_FUNCTION(execjavascriptClientTravel); \
	DECLARE_FUNCTION(execjavascriptGetGraphics); \
	DECLARE_FUNCTION(execjavascriptApplyAndSaveGraphics); \
	DECLARE_FUNCTION(execjavascriptQuitGame); \
	DECLARE_FUNCTION(execjavascriptConsoleCommand); \
	DECLARE_FUNCTION(exectriggerUE4EventMouseUp); \
	DECLARE_FUNCTION(exectriggerUE4EventMouseDown); \
	DECLARE_FUNCTION(exectriggerUE4EventWithJSON); \
	DECLARE_FUNCTION(exectriggerUE4EventWithMap); \
	DECLARE_FUNCTION(exectriggerUE4EventWithBlank); \
	DECLARE_FUNCTION(exectriggerUE4EventWithTag); \
	DECLARE_FUNCTION(execregisterJavascriptEvent); \
	DECLARE_FUNCTION(execJavascriptEventMouseUp); \
	DECLARE_FUNCTION(execJavascriptEventMouseDown);


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHTMLMenu(); \
	friend struct Z_Construct_UClass_UHTMLMenu_Statics; \
public: \
	DECLARE_CLASS(UHTMLMenu, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HTMLMenuMain"), NO_API) \
	DECLARE_SERIALIZER(UHTMLMenu)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_INCLASS \
private: \
	static void StaticRegisterNativesUHTMLMenu(); \
	friend struct Z_Construct_UClass_UHTMLMenu_Statics; \
public: \
	DECLARE_CLASS(UHTMLMenu, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HTMLMenuMain"), NO_API) \
	DECLARE_SERIALIZER(UHTMLMenu)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHTMLMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHTMLMenu) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHTMLMenu); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHTMLMenu); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHTMLMenu(UHTMLMenu&&); \
	NO_API UHTMLMenu(const UHTMLMenu&); \
public:


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHTMLMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHTMLMenu(UHTMLMenu&&); \
	NO_API UHTMLMenu(const UHTMLMenu&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHTMLMenu); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHTMLMenu); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHTMLMenu)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__bSupportsTransparency() { return STRUCT_OFFSET(UHTMLMenu, bSupportsTransparency); }


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_58_PROLOG
#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_PRIVATE_PROPERTY_OFFSET \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_SPARSE_DATA \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_RPC_WRAPPERS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_INCLASS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_PRIVATE_PROPERTY_OFFSET \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_SPARSE_DATA \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_INCLASS_NO_PURE_DECLS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h_61_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class HTMLMenu."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HTMLMENUMAIN_API UClass* StaticClass<class UHTMLMenu>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_HTMLMenu_h


#define FOREACH_ENUM_EHTMLMENUSYSTEM(op) \
	op(EHtmlMenuSystem::Android) \
	op(EHtmlMenuSystem::IOS) \
	op(EHtmlMenuSystem::Windows) \
	op(EHtmlMenuSystem::Linux) \
	op(EHtmlMenuSystem::Mac) 

enum class EHtmlMenuSystem : uint8;
template<> HTMLMENUMAIN_API UEnum* StaticEnum<EHtmlMenuSystem>();

#define FOREACH_ENUM_EHTML_DIRECTORYTYPE(op) \
	op(EHTML_DirectoryType::E_gd) \
	op(EHTML_DirectoryType::E_ad) 

enum class EHTML_DirectoryType : uint8;
template<> HTMLMENUMAIN_API UEnum* StaticEnum<EHTML_DirectoryType>();

#define FOREACH_ENUM_EHTML_FILETYPE(op) \
	op(EHTML_FileType::E_pdf) 

enum class EHTML_FileType : uint8;
template<> HTMLMENUMAIN_API UEnum* StaticEnum<EHTML_FileType>();

#define FOREACH_ENUM_EHTML_JAVASCRIPTFUNCTION(op) \
	op(EHTML_JavascriptFunction::E_Up) \
	op(EHTML_JavascriptFunction::E_Down) \
	op(EHTML_JavascriptFunction::E_Left) \
	op(EHTML_JavascriptFunction::E_Right) \
	op(EHTML_JavascriptFunction::E_Next) \
	op(EHTML_JavascriptFunction::E_Previous) \
	op(EHTML_JavascriptFunction::E_Choose) 

enum class EHTML_JavascriptFunction : uint8;
template<> HTMLMENUMAIN_API UEnum* StaticEnum<EHTML_JavascriptFunction>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
