// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SEGameState.h"

ASEGameState::ASEGameState()
{

}

void ASEGameState::ChangeColour(bool bDirection)
{
	if (bDirection)
	{
		CurrentColour = ASEUtilitySingleton::GetNextColour(CurrentColour);
	}
	else
	{
		CurrentColour = ASEUtilitySingleton::GetPreviousColour(CurrentColour);
	}
	
	OnColourChanged.Broadcast(CurrentColour);
}

//I've made it so this is the only place where colour needs to be changed if the decision is to change the shade or tone
FColor ASEGameState::GetColour(EColourTypes Colour) const
{
	switch (Colour)
	{
	default:
	case EColourTypes::Default:
		return Default;
	case EColourTypes::Red:
		return Red;
	case EColourTypes::Purple:
		return Purple;
	case EColourTypes::Blue:
		return Blue;
	case EColourTypes::Green:
		return Green;
	case EColourTypes::Yellow:
		return Yellow;
	}
}