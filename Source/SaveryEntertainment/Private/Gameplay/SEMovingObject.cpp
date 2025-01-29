// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SEMovingObject.h"

#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASEMovingObject::ASEMovingObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	StartPoint = CreateDefaultSubobject<USceneComponent>(FName("StartPoint"));
	StartPoint->SetupAttachment(RootComponent);

	MidPoint = CreateDefaultSubobject<USceneComponent>(FName("MidPoint"));
	MidPoint->SetupAttachment(RootComponent);

	EndPoint = CreateDefaultSubobject<USceneComponent>(FName("EndPoint"));
	EndPoint->SetupAttachment(RootComponent);
}

void ASEMovingObject::BeginPlay()
{
	Super::BeginPlay();

	Points.Add(StartPoint);
	Points.Add(MidPoint);
	Points.Add(EndPoint);

	Index = FMath::Clamp(Index, 0, Points.Num()-1);
	Shape->SetRelativeLocation(Points[Index]->GetRelativeLocation());
}

void ASEMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bLocked)
	{
		if (Shape->GetRelativeLocation().Equals(Points[Index]->GetRelativeLocation(), 1.f))
		{
			if (MovementDirection == EMovementDirection::Forward)
			{
				if (Index == Points.Num()-1)
				{
					MovementDirection = EMovementDirection::Backward;
					Index--;
				}
				else
				{
					Index++;
				}
			}
			else
			{
				if (Index == 0)
				{
					MovementDirection = EMovementDirection::Forward;
					Index++;
				}
				else
				{
					Index--;
				}
			}
		}
		else
		{
			const FVector Location = UKismetMathLibrary::VInterpTo_Constant(Shape->GetRelativeLocation(), Points[Index]->GetRelativeLocation(), DeltaTime, MovementSpeed);
			Shape->SetRelativeLocation(Location);

			const FRotator Rotation = UKismetMathLibrary::RInterpTo_Constant(Shape->GetRelativeRotation(), Points[Index]->GetRelativeRotation(), DeltaTime, MovementSpeed/2);
			Shape->SetRelativeRotation(Rotation);
		}
	}
}
