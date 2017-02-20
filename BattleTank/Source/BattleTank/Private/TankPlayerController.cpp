// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

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


ATank* ATankPlayerController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}