// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Labyrinth.h"
#include "Grubber.h"


// Sets default values for this component's properties
UGrubber::UGrubber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrubber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grubber start"));
	Player = GetWorld()->GetFirstPlayerController();
	// ...
	
}


// Called every frame
void UGrubber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector PlayerLocation;
	FRotator PlayerRotator;
	Player->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerLocation.ToString(),
		*PlayerRotator.ToString()
	);
	// ...
}

