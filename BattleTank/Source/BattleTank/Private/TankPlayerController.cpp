// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Enable tick event
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ATank* Tank = GetPlayerTank();

	if (!Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Tank Not Found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(Tank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();

	// UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
}

ATank* ATankPlayerController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPlayerTank())
	{
		return;
	}

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		// Get world location if linetrace through crosshair
		// If it hits the landscape
			// Tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}