// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HTMLMenuMain/Public/WebBrowserAssetManagerHTMLMenu.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWebBrowserAssetManagerHTMLMenu() {}
// Cross Module References
	HTMLMENUMAIN_API UClass* Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_NoRegister();
	HTMLMENUMAIN_API UClass* Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_HTMLMenuMain();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
// End Cross Module References
	void UWebBrowserAssetManagerHTMLMenu::StaticRegisterNativesUWebBrowserAssetManagerHTMLMenu()
	{
	}
	UClass* Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_NoRegister()
	{
		return UWebBrowserAssetManagerHTMLMenu::StaticClass();
	}
	struct Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FSoftObjectPropertyParams NewProp_DefaultMaterial;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_HTMLMenuMain,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "WebBrowserAssetManagerHTMLMenu.h" },
		{ "ModuleRelativePath", "Public/WebBrowserAssetManagerHTMLMenu.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::NewProp_DefaultMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/WebBrowserAssetManagerHTMLMenu.h" },
	};
#endif
	const UE4CodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::NewProp_DefaultMaterial = { "DefaultMaterial", nullptr, (EPropertyFlags)0x0024080000000000, UE4CodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UWebBrowserAssetManagerHTMLMenu, DefaultMaterial), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::NewProp_DefaultMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::NewProp_DefaultMaterial_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::NewProp_DefaultMaterial,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWebBrowserAssetManagerHTMLMenu>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::ClassParams = {
		&UWebBrowserAssetManagerHTMLMenu::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UWebBrowserAssetManagerHTMLMenu, 1858655908);
	template<> HTMLMENUMAIN_API UClass* StaticClass<UWebBrowserAssetManagerHTMLMenu>()
	{
		return UWebBrowserAssetManagerHTMLMenu::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UWebBrowserAssetManagerHTMLMenu(Z_Construct_UClass_UWebBrowserAssetManagerHTMLMenu, &UWebBrowserAssetManagerHTMLMenu::StaticClass, TEXT("/Script/HTMLMenuMain"), TEXT("UWebBrowserAssetManagerHTMLMenu"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UWebBrowserAssetManagerHTMLMenu);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
