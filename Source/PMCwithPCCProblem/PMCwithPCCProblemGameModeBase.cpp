// Fill out your copyright notice in the Description page of Project Settings.

#include "PMCwithPCCProblemGameModeBase.h"

#include "withPMC.h"
#include "withSMC.h"

void APMCwithPCCProblemGameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("APMCwithPCCProblemGameModeBase::BeginPlay()"));
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	auto PhysicsTest1 = World->SpawnActor< AwithPMC >(FVector(-100.f, -100.f, 200.f), FRotator(0));
	auto PhysicsTest2 = World->SpawnActor< AwithSMC >(FVector(-100.f, 100.f, 200.f), FRotator(0));
}