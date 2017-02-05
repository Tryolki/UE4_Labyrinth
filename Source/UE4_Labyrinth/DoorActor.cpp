// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Labyrinth.h"
#include "DoorActor.h"
#include <string>

// Sets default values for this component's properties
UDoorActor::UDoorActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorActor::BeginPlay()
{
	Super::BeginPlay();
	DoorActor = GetOwner();
}


// Called every frame
void UDoorActor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (GetTotalMassOfTheActorsOnPlate() > MaxMass)
	{
		OpenDoor();
	}
	else {
		CloseDoor();
	}
}

void UDoorActor::OpenDoor()
{
	OnOpenRequest.Broadcast();
}

void UDoorActor::CloseDoor()
{
	OnCloseRequest.Broadcast();
}

float UDoorActor::GetTotalMassOfTheActorsOnPlate()
{
	float TotallMass = 0.f;
	float ActorMass = 0.f;
	TArray<AActor *> OverlappingActors;
	for (const auto & Trigger : DoorTriggers)
	{
		if (Trigger == nullptr) return 0.f;
		Trigger->GetOverlappingActors(OverlappingActors);
		for (const auto & Actor : OverlappingActors)
		{
			ActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			TotallMass += ActorMass;
			UE_LOG(LogTemp, Warning, TEXT("%s on the trigger volume. Mass: %s"), *Actor->GetName(), *FString::SanitizeFloat(ActorMass));
		}
	}
	return TotallMass;
}

