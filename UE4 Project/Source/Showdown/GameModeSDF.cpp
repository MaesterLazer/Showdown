// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeSDF.h"

FString AGameModeSDF::GetGameVersion(bool bShortString) {


	if (bShortString) {
		return VersionData::GameVersionShort;
	}
	else {
		return VersionData::GameVersionLong;
	}
}
