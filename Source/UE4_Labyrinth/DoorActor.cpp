// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Labyrinth.h"
#include "DoorActor.h"


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
	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	DoorActor = GetOwner();
}


// Called every frame
void UDoorActor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (DoorTrigger->IsOverlappingActor(PlayerActor))
	{
		OpenDoor(DeltaTime);
		LastOpenDoorTime = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() > LastOpenDoorTime + CloseWaitTime)
			CloseDoor(DeltaTime);
	}
}

void UDoorActor::OpenDoor(float DeltaTime)
{
	auto DoorRotator = DoorActor->GetActorRotation();
	if (DoorRotator.Yaw < MaxDoorAngle)
	{
		DoorRotator.Yaw += DeltaTime * 10;
		DoorActor->SetActorRotation(DoorRotator);
	}
}

void UDoorActor::CloseDoor(float DeltaTime)
{
	auto DoorRotator = DoorActor->GetActorRotation();
	if (DoorRotator.Yaw > 0)
	{
		DoorRotator.Yaw -= DeltaTime * 10;
		DoorActor->SetActorRotation(DoorRotator);
	}

}

