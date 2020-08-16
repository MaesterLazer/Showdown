/**********************************************************************/
/* DO NOT MODIFY THIS FILE. THIS FILE IS REFRENCED BY THE BUILD SYSTEM.    */
/**********************************************************************/
#pragma once
namespace VersionData {

	const FString MajorVersion = "0";
	const FString MinorVersion = "1";
	const FString RevisionVersion = "0";

	/* Automatically updated by build system*/
const int BuildNumber = 11;
	/*********************************************************************/

	const FString BuildVersion = FString::FromInt(BuildNumber - 1);

	const FString GameVersionShort = (MajorVersion + "." + MinorVersion + "." + RevisionVersion);
	const FString GameVersionLong = (MajorVersion + "." + MinorVersion + "." + RevisionVersion + "." + BuildVersion);
};

