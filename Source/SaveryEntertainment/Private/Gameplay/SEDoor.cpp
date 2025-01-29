// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SEDoor.h"

#include "Game/SEGameState.h"
#include "Kismet/KismetMathLibrary.h"

void ASEDoor::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicColour->SetVectorParameterValue("Colour", FVector(SEGameState->GetColour(AssignedColour)));
	Shape->SetMaterial(0, DynamicColour);
}

void ASEDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLocked)
	{
		if (!Shape->GetRelativeLocation().Equals(OpenLocation, 1.f))
		{
			const FVector Location = UKismetMathLibrary::VInterpTo_Constant(Shape->GetRelativeLocation(), OpenLocation, DeltaTime, 20.f);
			Shape->SetRelativeLocation(Location);
		}
	}
	else
	{
		if (!Shape->GetRelativeLocation().Equals(FVector::ZeroVector, 1.f))
		{
			const FVector Location = UKismetMathLibrary::VInterpTo_Constant(Shape->GetRelativeLocation(), FVector::ZeroVector, DeltaTime, 20.f);
			Shape->SetRelativeLocation(Location);
		}
	}
}


void ASEDoor::NotifyColourChange(EColourTypes NewColour)
{
	
}
