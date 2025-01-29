// Fill out your copyright notice in the Description page of Project Settings.


#include "SEUtilitySingleton.h"

USEUtilitySingleton::USEUtilitySingleton()
{
}

bool USEUtilitySingleton::DoesColourCrossover(EColourTypes Colour, EColourTypes ComparativeColour)
{
	switch (Colour)
	{
	default:
	case EColourTypes::Default:
		return ComparativeColour == EColourTypes::Default;
	case EColourTypes::Red:
		return ComparativeColour == EColourTypes::Red || ComparativeColour == EColourTypes::Default;
	case EColourTypes::Purple:
		return ComparativeColour == EColourTypes::Red || ComparativeColour == EColourTypes::Purple || ComparativeColour == EColourTypes::Blue || ComparativeColour == EColourTypes::Default;
	case EColourTypes::Blue:
		return ComparativeColour == EColourTypes::Blue || ComparativeColour == EColourTypes::Default;
	case EColourTypes::Green:
		return ComparativeColour == EColourTypes::Blue || ComparativeColour == EColourTypes::Green || ComparativeColour == EColourTypes::Yellow || ComparativeColour == EColourTypes::Default;
	case EColourTypes::Yellow:
		return ComparativeColour == EColourTypes::Yellow || ComparativeColour == EColourTypes::Default;
	}
}

EColourTypes USEUtilitySingleton::GetNextColour(EColourTypes Colour)
{
	switch (Colour)
	{
	default:
	case EColourTypes::Default:
		return EColourTypes::Red;
	case EColourTypes::Red:
		return EColourTypes::Purple;
	case EColourTypes::Purple:
		return EColourTypes::Blue;
	case EColourTypes::Blue:
		return EColourTypes::Green;
	case EColourTypes::Green:
		return EColourTypes::Yellow;
	case EColourTypes::Yellow:
		return EColourTypes::Default;
	}
}

EColourTypes USEUtilitySingleton::GetPreviousColour(EColourTypes Colour)
{
	switch (Colour)
	{
	default:
	case EColourTypes::Default:
		return EColourTypes::Yellow;
	case EColourTypes::Red:
		return EColourTypes::Default;
	case EColourTypes::Purple:
		return EColourTypes::Red;
	case EColourTypes::Blue:
		return EColourTypes::Purple;
	case EColourTypes::Green:
		return EColourTypes::Blue;
	case EColourTypes::Yellow:
		return EColourTypes::Green;
	}
}
