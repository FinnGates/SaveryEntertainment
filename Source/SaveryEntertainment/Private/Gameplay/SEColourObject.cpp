// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SEColourObject.h"

#include "Game/SEGameState.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASEColourObject::ASEColourObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	
	Shape = CreateDefaultSubobject<UStaticMeshComponent>(FName("Shape"));
	Shape->SetupAttachment(Root);
}

void ASEColourObject::NotifyColourChange(EColourTypes NewColour)
{
	if (!bLocked)
	{
		if (USEUtilitySingleton::DoesColourCrossover(NewColour, AssignedColour))
		{
			Shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			DesiredColour = FVector(SEGameState->GetColour(NewColour));
			DesiredOpacity = 1.f;
		}
		else
		{
			DesiredOpacity = 0.f;
			Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ASEColourObject::NotifyColourLocked(bool bIsLocked, EColourTypes LockedColour)
{
	if (AssignedColour != EColourTypes::Default && USEUtilitySingleton::DoesColourCrossover(LockedColour, AssignedColour))
	{
		bLocked = bIsLocked;
	}
}

// Called when the game starts or when spawned
void ASEColourObject::BeginPlay()
{
	Super::BeginPlay();

	DynamicColour = UMaterialInstanceDynamic::Create(Shape->GetMaterial(0), this);
	
	SEGameState = GetWorld()->GetGameState<ASEGameState>();

	if (SEGameState)
	{
		SEGameState->OnColourChanged.AddUObject(this, &ASEColourObject::NotifyColourChange);
		SEGameState->OnColourLocked.AddUObject(this, &ASEColourObject::NotifyColourLocked);
	}
	
	
	CurrentOpacity = 1.f;
	DesiredOpacity = 1.f;

	NotifyColourChange(SEGameState->GetCurrentColour());
}

// Called every frame
void ASEColourObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Makes it so the change in colour and visibility isn't instant
	if (!CurrentColour.Equals(DesiredColour))
	{
		CurrentColour = UKismetMathLibrary::VInterpTo(CurrentColour, DesiredColour, DeltaTime, 5.f);
		DynamicColour->SetVectorParameterValue("Colour", CurrentColour);
		Shape->SetMaterial(0, DynamicColour);
	}
	if (DesiredOpacity != CurrentOpacity)
	{
		CurrentOpacity = UKismetMathLibrary::FInterpTo(CurrentOpacity, DesiredOpacity, DeltaTime, 5.f);
		DynamicColour->SetScalarParameterValue("Opacity", CurrentOpacity);
		Shape->SetMaterial(0, DynamicColour);
	}
}

