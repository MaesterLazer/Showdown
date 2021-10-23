// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHTMLMenuMain_init() {}
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UHTMLMenu_OnUrlChanged__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UHTMLMenu_OnBeforePopup__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UHTMLMenu_JavascriptEventMouseDown__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UHTMLMenu_JavascriptEventMouseUp__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventTag__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventBlank__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventMap__DelegateSignature();
	HTMLMENUMAIN_API UFunction* Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventJSON__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_HTMLMenuMain()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_UHTMLMenu_OnUrlChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UHTMLMenu_OnBeforePopup__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UHTMLMenu_JavascriptEventMouseDown__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UHTMLMenu_JavascriptEventMouseUp__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventTag__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventBlank__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventMap__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UJavascriptBean_JavascriptEventJSON__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/HTMLMenuMain",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x82488E07,
				0x69DE0CF8,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
