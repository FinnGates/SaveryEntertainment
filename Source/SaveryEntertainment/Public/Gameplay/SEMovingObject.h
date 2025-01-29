// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/SEGravityObject.h"
#include "SEMovingObject.generated.h"

class USplineComponent;
/**
 * 
 */
UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	Forward,
	Backward
};

UCLASS()
class SAVERYENTERTAINMENT_API ASEMovingObject : public ASEGravityObject
{
	GENERATED_BODY()

public:
	ASEMovingObject(const FObjectInitializer& ObjectInitializer);
	
protected:

    /* I wanted to use splines for this but I was getting a lot of crashes of my entire PC while doing it, also the splines
     * wanted to curve and bend in weird ways that meant I couldn't get a consistent rotation in the way I wanted */
	UPROPERTY(EditAnywhere)
	USceneComponent* StartPoint;
    
    UPROPERTY(EditAnywhere)
	USceneComponent* MidPoint;

	UPROPERTY(EditAnywhere)
	USceneComponent* EndPoint;

	UPROPERTY()
	TArray<USceneComponent*> Points;

	UPROPERTY(EditAnywhere)
	int32 Index = 0;

	UPROPERTY(EditAnywhere)
	EMovementDirection MovementDirection = EMovementDirection::Forward;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 100.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
