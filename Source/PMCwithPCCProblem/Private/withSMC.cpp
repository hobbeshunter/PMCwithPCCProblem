// Fill out your copyright notice in the Description page of Project Settings.

#include "withSMC.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AwithSMC::AwithSMC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject< USceneComponent >(TEXT("RootSMC"));
	static ConstructorHelpers::FObjectFinder< UStaticMesh > CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		CubeVisualMesh = CubeVisualAsset.Object;
	}
}

// Called when the game starts or when spawned
void AwithSMC::BeginPlay()
{
	Super::BeginPlay();

	auto Cube1 = NewObject< UStaticMeshComponent >(this, TEXT("CubeSMC1"));
	Cube1->SetStaticMesh(CubeVisualMesh);

	Cube1->SetSimulatePhysics(true);
	Cube1->SetEnableGravity(true);
	Cube1->SetCollisionProfileName(TEXT("Pawn"));
	Cube1->SetRelativeRotation(FRotator(0));
	Cube1->SetRelativeLocation(FVector(0, 0, 0));
	Cube1->SetWorldScale3D(FVector(0.2f));
	Cube1->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Cube1->RegisterComponent();

	auto Cube2 = NewObject< UStaticMeshComponent >(this, TEXT("CubeSMC2"));
	Cube2->SetStaticMesh(CubeVisualMesh);

	Cube2->SetSimulatePhysics(true);
	Cube2->SetEnableGravity(true);
	Cube2->SetCollisionProfileName(TEXT("Pawn"));
	Cube2->SetRelativeRotation(FRotator(0));
	Cube2->SetRelativeLocation(FVector(150, 0, 150));
	// Cube2->SetWorldScale3D(FVector(0.2f));
	Cube2->AttachToComponent(Cube1, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Cube2->RegisterComponent();

	auto ConstraintComponent = NewObject< UPhysicsConstraintComponent >(this, TEXT("PhysicsTestSMC"));

	ConstraintComponent->SetDisableCollision(true);
	ConstraintComponent->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearBreakable(false, 140.0f);
	ConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularBreakable(false, 140.0f);

	FVector JointShift = FVector(0);
	FRotator JointRotation = FRotator(0);
	ConstraintComponent->SetRelativeRotation(JointRotation);
	ConstraintComponent->SetRelativeLocation(JointShift);
	// ConstraintComponent->AttachToComponent(Cube1, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ConstraintComponent->SetConstrainedComponents(Cube1, NAME_None, Cube2, NAME_None);
	// ConstraintComponent->ComponentName1.ComponentName = TEXT("CubeSMC1");
	// ConstraintComponent->ComponentName2.ComponentName = TEXT("CubeSMC2");

	ConstraintComponent->RegisterComponent();
}

// Called every frame
void AwithSMC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
