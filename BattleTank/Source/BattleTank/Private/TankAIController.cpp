// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetAiTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s"), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Found"));
	}
}


ATank* ATankAIController::GetAiTank() const
{
	return Cast<ATank>(GetPawn());
}