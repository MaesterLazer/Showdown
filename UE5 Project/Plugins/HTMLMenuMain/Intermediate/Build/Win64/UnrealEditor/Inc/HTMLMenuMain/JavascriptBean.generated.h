// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FStringTMap;
 
#ifdef HTMLMENUMAIN_JavascriptBean_generated_h
#error "JavascriptBean.generated.h already included, missing '#pragma once' in JavascriptBean.h"
#endif
#define HTMLMENUMAIN_JavascriptBean_generated_h

#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FStringTMap_Statics; \
	HTMLMENUMAIN_API static class UScriptStruct* StaticStruct();


template<> HTMLMENUMAIN_API UScriptStruct* StaticStruct<struct FStringTMap>();

#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_51_DELEGATE \
struct JavascriptBean_eventJavascriptEventJSON_Parms \
{ \
	FString json; \
}; \
static inline void FJavascriptEventJSON_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventJSON, const FString& json) \
{ \
	JavascriptBean_eventJavascriptEventJSON_Parms Parms; \
	Parms.json=json; \
	JavascriptEventJSON.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_45_DELEGATE \
struct JavascriptBean_eventJavascriptEventMap_Parms \
{ \
	FStringTMap map; \
}; \
static inline void FJavascriptEventMap_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventMap, const FStringTMap map) \
{ \
	JavascriptBean_eventJavascriptEventMap_Parms Parms; \
	Parms.map=map; \
	JavascriptEventMap.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_39_DELEGATE \
struct JavascriptBean_eventJavascriptEventBlank_Parms \
{ \
	TArray<FString> args; \
}; \
static inline void FJavascriptEventBlank_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventBlank, TArray<FString> const& args) \
{ \
	JavascriptBean_eventJavascriptEventBlank_Parms Parms; \
	Parms.args=args; \
	JavascriptEventBlank.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_33_DELEGATE \
struct JavascriptBean_eventJavascriptEventTag_Parms \
{ \
	FString ID; \
	FString ClassName; \
	FString Value; \
	TArray<FString> args; \
}; \
static inline void FJavascriptEventTag_DelegateWrapper(const FMulticastScriptDelegate& JavascriptEventTag, const FString& ID, const FString& ClassName, const FString& Value, TArray<FString> const& args) \
{ \
	JavascriptBean_eventJavascriptEventTag_Parms Parms; \
	Parms.ID=ID; \
	Parms.ClassName=ClassName; \
	Parms.Value=Value; \
	Parms.args=args; \
	JavascriptEventTag.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_SPARSE_DATA
#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(exectoStringMap); \
	DECLARE_FUNCTION(execJavascriptEventJSON); \
	DECLARE_FUNCTION(execJavascriptEventMap); \
	DECLARE_FUNCTION(execJavascriptEventBlank); \
	DECLARE_FUNCTION(execJavascriptEventTag);


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(exectoStringMap); \
	DECLARE_FUNCTION(execJavascriptEventJSON); \
	DECLARE_FUNCTION(execJavascriptEventMap); \
	DECLARE_FUNCTION(execJavascriptEventBlank); \
	DECLARE_FUNCTION(execJavascriptEventTag);


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUJavascriptBean(); \
	friend struct Z_Construct_UClass_UJavascriptBean_Statics; \
public: \
	DECLARE_CLASS(UJavascriptBean, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HTMLMenuMain"), NO_API) \
	DECLARE_SERIALIZER(UJavascriptBean)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_INCLASS \
private: \
	static void StaticRegisterNativesUJavascriptBean(); \
	friend struct Z_Construct_UClass_UJavascriptBean_Statics; \
public: \
	DECLARE_CLASS(UJavascriptBean, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HTMLMenuMain"), NO_API) \
	DECLARE_SERIALIZER(UJavascriptBean)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UJavascriptBean(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UJavascriptBean) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UJavascriptBean); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UJavascriptBean); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UJavascriptBean(UJavascriptBean&&); \
	NO_API UJavascriptBean(const UJavascriptBean&); \
public:


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UJavascriptBean(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UJavascriptBean(UJavascriptBean&&); \
	NO_API UJavascriptBean(const UJavascriptBean&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UJavascriptBean); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UJavascriptBean); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UJavascriptBean)


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_PRIVATE_PROPERTY_OFFSET
#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_21_PROLOG
#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_PRIVATE_PROPERTY_OFFSET \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_SPARSE_DATA \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_RPC_WRAPPERS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_INCLASS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_PRIVATE_PROPERTY_OFFSET \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_SPARSE_DATA \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_INCLASS_NO_PURE_DECLS \
	UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h_24_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class JavascriptBean."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HTMLMENUMAIN_API UClass* StaticClass<class UJavascriptBean>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE5_Project_Plugins_HTMLMenuMain_Source_HTMLMenuMain_Public_JavascriptBean_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
