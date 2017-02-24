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

	// De-project the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to some maximum range)
	HitLocation = FVector(1.0);
	return true;
}