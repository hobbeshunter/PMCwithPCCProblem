// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "withSMC.generated.h"

UCLASS()
class AwithSMC : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AwithSMC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMesh* CubeVisualMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
