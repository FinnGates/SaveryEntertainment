// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/SEColourObject.h"
#include "SEGravityObject.generated.h"

class UCharacterMovementComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class SAVERYENTERTAINMENT_API ASEGravityObject : public ASEColourObject
{
	GENERATED_BODY()

public:
	ASEGravityObject(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;

	UPROPERTY()
	UCharacterMovementComponent* PlayerMovement;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void NotifyColourChange(EColourTypes NewColour) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
