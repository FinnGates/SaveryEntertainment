// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEColourObject.h"
#include "GameFramework/Actor.h"
#include "SEInteractable.generated.h"

class USphereComponent;

UCLASS()
class SAVERYENTERTAINMENT_API ASEInteractable : public ASEColourObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASEInteractable(const FObjectInitializer& ObjectInitializer);

	virtual void NotifyColourChange(EColourTypes NewColour) override;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* Pivot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Shaft;

	UPROPERTY(EditAnywhere)
	USphereComponent* Overlap;

	UPROPERTY(EditAnywhere)
	FRotator UsedInteractable = FRotator(0, 0, 40.f);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex);

	UFUNCTION()
	void Interact();
	
	UPROPERTY()
	bool bInteractedWith = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
