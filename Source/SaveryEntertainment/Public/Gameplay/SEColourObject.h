// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEColourObject.generated.h"

class ASEGameState;
enum class EColourTypes : uint8;

UCLASS()
class SAVERYENTERTAINMENT_API ASEColourObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASEColourObject(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	virtual void NotifyColourChange(EColourTypes NewColour);
	UFUNCTION()
	virtual void NotifyColourLocked(bool bIsLocked, EColourTypes LockedColour);

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Shape;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Colour)
	EColourTypes AssignedColour;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicColour;

	UPROPERTY()
	ASEGameState* SEGameState;

	UPROPERTY()
	FVector CurrentColour;

	UPROPERTY()
	FVector DesiredColour;

	UPROPERTY()
	float CurrentOpacity;

	UPROPERTY()
	float DesiredOpacity;

	UPROPERTY()
	bool bLocked = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
