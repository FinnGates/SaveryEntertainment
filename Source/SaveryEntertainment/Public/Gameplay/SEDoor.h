// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/SEColourObject.h"
#include "SEDoor.generated.h"

/**
 * 
 */
UCLASS()
class SAVERYENTERTAINMENT_API ASEDoor : public ASEColourObject
{
	GENERATED_BODY()

public:
	virtual void NotifyColourChange(EColourTypes NewColour) override;

protected:
	UPROPERTY(EditAnywhere)
	FVector OpenLocation = FVector(0,0,80.f);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
