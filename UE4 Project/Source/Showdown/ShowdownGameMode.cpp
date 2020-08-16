// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowdownGameMode.h"

FString AShowdownGameMode::GetGameVersion(bool bShortString) {


	if (bShortString) {
		return VersionData::GameVersionShort;
	}
	else {
		return VersionData::GameVersionLong;
	}
}
