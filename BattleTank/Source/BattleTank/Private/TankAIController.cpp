// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetAiTank();
	auto PlayerPawn = GetPlayerTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s"), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Found"));
	}

	if (PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Pawn: %s"), *(PlayerPawn->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController could not find player pawn."));
	}
}


ATank* ATankAIController::GetAiTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!Tank)
	{
		return nullptr;
	}

	return Tank;
}