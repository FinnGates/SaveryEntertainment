// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEUtilitySingleton.generated.h"

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

//I would have usually made this a data class for the colours and then a utility singleton for the static functions but
//for a project this small it seemed like unnecessary work and complication.
UCLASS()
class SAVERYENTERTAINMENT_API ASEUtilitySingleton : public AActor
{
	GENERATED_BODY()
public:
	ASEUtilitySingleton();
	
	static bool DoesColourCrossover(EColourTypes Colour, EColourTypes ComparativeColour);
	static EColourTypes GetNextColour(EColourTypes Colour);
	static EColourTypes GetPreviousColour(EColourTypes Colour);

};
