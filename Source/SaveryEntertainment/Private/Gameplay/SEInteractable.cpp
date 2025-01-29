// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SEInteractable.h"

#include "Components/SphereComponent.h"
#include "Game/SEGameState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/SaveryEntertainmentCharacter.h"

// Sets default values
ASEInteractable::ASEInteractable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>(FName("Pivot"));
	Pivot->SetupAttachment(Root);

	Shape = CreateDefaultSubobject<UStaticMeshComponent>(FName("Handle"));
	Shape->SetupAttachment(Pivot);

	Shaft = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shaft"));
	Shaft->SetupAttachment(Pivot);

	Overlap = CreateDefaultSubobject<USphereComponent>(FName("Overlap"));
	Overlap->SetupAttachment(Root);
}

void ASEInteractable::NotifyColourChange(EColourTypes NewColour)
{
	if (!bInteractedWith)
	{
		AssignedColour = NewColour;
		DesiredColour = FVector(SEGameState->GetColour(NewColour));
	}
}

// Called when the game starts or when spawned
void ASEInteractable::BeginPlay()
{
	Super::BeginPlay();

	Overlap->OnComponentBeginOverlap.AddDynamic(this, &ASEInteractable::OnOverlapBegin);
	Overlap->OnComponentEndOverlap.AddDynamic(this, &ASEInteractable::OnOverlapEnd);
}

void ASEInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASaveryEntertainmentCharacter* Player = Cast<ASaveryEntertainmentCharacter>(OtherActor))
	{
		Player->InteractDelegate.BindUObject(this, &ASEInteractable::Interact);
	}
}

void ASEInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ASaveryEntertainmentCharacter* Player = Cast<ASaveryEntertainmentCharacter>(OtherActor))
	{
		Player->InteractDelegate.Unbind();
	}
}

void ASEInteractable::Interact()
{
	bInteractedWith = !bInteractedWith;
	SEGameState->LockColour(bInteractedWith, AssignedColour);
}

// Called every frame
void ASEInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInteractedWith)
	{
		if (!Pivot->GetRelativeRotation().Equals(UsedInteractable, 1.f))
		{
			const FRotator Rotation = UKismetMathLibrary::RInterpTo_Constant(Pivot->GetRelativeRotation(), UsedInteractable, DeltaTime, 20.f);
			Pivot->SetRelativeRotation(Rotation);
		}
	}
	else
	{
		if (!Pivot->GetRelativeRotation().Equals(FRotator::ZeroRotator, 1.f))
		{
			const FRotator Rotation = UKismetMathLibrary::RInterpTo_Constant(Pivot->GetRelativeRotation(), FRotator::ZeroRotator, DeltaTime, 20.f);
			Pivot->SetRelativeRotation(Rotation);
		}
	}
}



