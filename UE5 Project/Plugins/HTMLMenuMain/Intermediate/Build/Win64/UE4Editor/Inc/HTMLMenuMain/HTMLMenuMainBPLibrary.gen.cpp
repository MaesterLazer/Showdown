// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HTMLMenuMain/Public/HTMLMenuMainBPLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHTMLMenuMainBPLibrary() {}
// Cross Module References
	HTMLMENUMAIN_API UClass* Z_Construct_UClass_UHTMLMenuMainBPLibrary_NoRegister();
	HTMLMENUMAIN_API UClass* Z_Construct_UClass_UHTMLMenuMainBPLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_HTMLMenuMain();
// End Cross Module References
	void UHTMLMenuMainBPLibrary::StaticRegisterNativesUHTMLMenuMainBPLibrary()
	{
	}
	UClass* Z_Construct_UClass_UHTMLMenuMainBPLibrary_NoRegister()
	{
		return UHTMLMenuMainBPLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_HTMLMenuMain,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "HTMLMenuMainBPLibrary.h" },
		{ "ModuleRelativePath", "Public/HTMLMenuMainBPLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHTMLMenuMainBPLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::ClassParams = {
		&UHTMLMenuMainBPLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHTMLMenuMainBPLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHTMLMenuMainBPLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHTMLMenuMainBPLibrary, 4026329098);
	template<> HTMLMENUMAIN_API UClass* StaticClass<UHTMLMenuMainBPLibrary>()
	{
		return UHTMLMenuMainBPLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHTMLMenuMainBPLibrary(Z_Construct_UClass_UHTMLMenuMainBPLibrary, &UHTMLMenuMainBPLibrary::StaticClass, TEXT("/Script/HTMLMenuMain"), TEXT("UHTMLMenuMainBPLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHTMLMenuMainBPLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
