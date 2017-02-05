// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_LABYRINTH_API UDoorActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorActor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(EditAnywhere)
	float CloseWaitTime = 0.0f;

	float LastOpenDoorTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float MaxDoorAngle = 85.0f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume * DoorTrigger;

	UPROPERTY(EditAnywhere)
	TArray<ATriggerVolume *> DoorTriggers;
	UPROPERTY(VisibleAnywhere)
	float MaxMass = 75.f;

	AActor * DoorActor;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMassOfTheActorsOnPlate();

};
