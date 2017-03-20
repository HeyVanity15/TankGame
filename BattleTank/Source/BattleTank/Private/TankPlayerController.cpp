// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Enable tick event
	PrimaryActorTick.bCanEverTick = true;

	ATank* Tank = GetPlayerTank();

	if (!Tank)
	{
		
	}
	else
	{
		
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
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
		// Get world location if linetrace through crosshair
		// If it hits the landscape
			// Tell controlled tank to aim at this point
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
		GetPlayerTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	float ScreenLocationX = ViewportSizeX * CrosshairXLocation;
	float ScreenLocationY = ViewportSizeY * CrosshairYLocation;

	auto ScreenLocation = FVector2D(ScreenLocationX, ScreenLocationY);

	FVector LookDirection;

	bool gotLookDirection = GetLookDirection(ScreenLocation, LookDirection);

	if (gotLookDirection)
	{
		//UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *LookDirection.ToString());

		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// De-project the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to some maximum range)
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	// Line-trace
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	// If line-trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
