// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetPlayerTank() const;

	void AimAtCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
