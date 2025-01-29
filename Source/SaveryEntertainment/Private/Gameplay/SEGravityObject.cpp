// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SEGravityObject.h"

#include "SEUtilitySingleton.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASEGravityObject::ASEGravityObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(FName("OverlapBox"));
	OverlapBox->SetupAttachment(Shape);
}

void ASEGravityObject::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ASEGravityObject::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ASEGravityObject::OnOverlapEnd);
}

void ASEGravityObject::NotifyColourChange(EColourTypes NewColour)
{
	Super::NotifyColourChange(NewColour);

	if (!bLocked)
	{
		if (USEUtilitySingleton::DoesColourCrossover(NewColour, AssignedColour))
		{
			OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			OverlapBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ASEGravityObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerMovement)
	{
		FVector GravityDirection = UKismetMathLibrary::VInterpTo(PlayerMovement->GetGravityDirection(), -OverlapBox->GetUpVector(), DeltaTime, 7.f);
		PlayerMovement->SetGravityDirection(GravityDirection);
	}
}

void ASEGravityObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		PlayerMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void ASEGravityObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerMovement = nullptr;
}