// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EColourTypes : uint8
{
	Default,
	Red,
	Purple,
	Blue,
	Green,
	Yellow
};

/**
 * 
 */

class SAVERYENTERTAINMENT_API USEUtilitySingleton
{
public:
	USEUtilitySingleton();
	
	static bool DoesColourCrossover(EColourTypes Colour, EColourTypes ComparativeColour);
	static EColourTypes GetNextColour(EColourTypes Colour);
	static EColourTypes GetPreviousColour(EColourTypes Colour);

};
