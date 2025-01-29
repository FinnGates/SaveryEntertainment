// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEUtilitySingleton.h"
#include "GameFramework/GameStateBase.h"
#include "SEGameState.generated.h"

class ASEColourObject;
enum class EColourTypes : uint8;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnColourChanged, EColourTypes);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnColourLocked, bool, EColourTypes);

UCLASS()
class SAVERYENTERTAINMENT_API ASEGameState : public AGameStateBase
{
	GENERATED_BODY()

	ASEGameState();
public:
	EColourTypes GetCurrentColour() const {return CurrentColour;}
	
	FColor GetColour(EColourTypes Colour) const;
	
	void ChangeColour(bool bDirection);

	void LockColour(bool bIsLocked, EColourTypes LockColour) const;
	
	FOnColourChanged OnColourChanged;
	FOnColourLocked OnColourLocked;
	
protected:
	UPROPERTY(EditAnywhere)
	EColourTypes CurrentColour = EColourTypes::Default;

	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Default = FColor::White;
	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Red = FColor::Red;
	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Purple = FColor::Purple;
	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Blue = FColor::Blue;
	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Green = FColor::Green;
	UPROPERTY(EditAnywhere, Category = Colours)
	FColor Yellow = FColor::Yellow;

};
