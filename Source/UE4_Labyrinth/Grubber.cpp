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
	// Looked for attached physics handle
	FindPhysicsComponent();
	SetupInputComponent();
	
}

void UGrubber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr)
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	else
	{
		InputComponent->BindAction("Grub", IE_Pressed, this, &UGrubber::Grub);
		InputComponent->BindAction("Grub", IE_Released, this, &UGrubber::Release);
	}
}

void UGrubber::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}


// Called every frame
void UGrubber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UGrubber::Grub()
{
	UE_LOG(LogTemp, Warning, TEXT("Grub pressed"));
	AActor * HitActor = GetFirstPhysicsBodyInReach().GetActor();
	if(HitActor)
		UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *(HitActor->GetName()));
}

void UGrubber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grub released"));
}

const FHitResult UGrubber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerLocation;
	FRotator PlayerRotator;
	Player->GetPlayerViewPoint(PlayerLocation, PlayerRotator);
	FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * Reach;
	//DrawDebugLine(
	//	GetWorld(),
	//	PlayerLocation,
	//	LineTraceEnd,
	//	FColor(255, 0, 0),
	//	false,
	//	0.f,
	//	0.f,
	//	10.f
	//);
	///false mean that we use simply collider
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	/// Linetrace(ray-cast) uot reach distance
	FHitResult ObjectTrace;
	GetWorld()->LineTraceSingleByObjectType(
		ObjectTrace,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return ObjectTrace;
}


