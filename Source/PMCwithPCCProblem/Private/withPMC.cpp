// Fill out your copyright notice in the Description page of Project Settings.

#include "withPMC.h"
#include "KismetProceduralMeshLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AwithPMC::AwithPMC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject< USceneComponent >(TEXT("Root"));
}

// Called when the game starts or when spawned
void AwithPMC::BeginPlay()
{
	Super::BeginPlay();

	TArray< FVector > Vertices1;
	TArray< int32 > Triangles1;
	TArray< FVector > Normals1;
	TArray< FVector2D > UVs1;
	TArray< FLinearColor > Colors1;
	TArray< FProcMeshTangent > Tangents1;
	UKismetProceduralMeshLibrary::GenerateBoxMesh(FVector(10), Vertices1, Triangles1, Normals1, UVs1, Tangents1);

	auto Cube1 = NewObject< UProceduralMeshComponent >(this, TEXT("Cube1"));
	Cube1->bUseAsyncCooking = true;
	Cube1->bUseComplexAsSimpleCollision = false;

	Cube1->CreateMeshSection_LinearColor(0, Vertices1, Triangles1, Normals1, UVs1, Colors1, Tangents1, true);
	Cube1->AddCollisionConvexMesh(Vertices1);

	Cube1->SetSimulatePhysics(true);
	// Cube1->SetEnableGravity(true);
	Cube1->SetCollisionProfileName(TEXT("Pawn"));
	Cube1->SetRelativeRotation(FRotator(0));
	Cube1->SetRelativeLocation(FVector(0, 0, 0));
	Cube1->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Cube1->RegisterComponent();

	auto Cube2 = NewObject< UProceduralMeshComponent >(this, TEXT("Cube2"));
	Cube2->bUseAsyncCooking = true;
	Cube2->bUseComplexAsSimpleCollision = false;

	Cube2->CreateMeshSection_LinearColor(0, Vertices1, Triangles1, Normals1, UVs1, Colors1, Tangents1, true);
	Cube2->AddCollisionConvexMesh(Vertices1);

	Cube2->SetSimulatePhysics(true);
	// Cube2->SetEnableGravity(true);
	Cube2->SetCollisionProfileName(TEXT("Pawn"));
	Cube2->SetRelativeRotation(FRotator(0));
	Cube2->SetRelativeLocation(FVector(30, 0, 30));
	Cube2->AttachToComponent(Cube1, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Cube2->RegisterComponent();

	auto ConstraintComponent = NewObject< UPhysicsConstraintComponent >(this, TEXT("PhysicsTest"));

	ConstraintComponent->SetDisableCollision(true);
	ConstraintComponent->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	ConstraintComponent->SetLinearBreakable(false, 0.0f);
	ConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
	ConstraintComponent->SetAngularBreakable(false, 0.0f);

	FVector JointShift = FVector(0);
	FRotator JointRotation = FRotator(0);
	ConstraintComponent->SetRelativeRotation(JointRotation);
	ConstraintComponent->SetRelativeLocation(JointShift);
	// ConstraintComponent->AttachToComponent(Cube1, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	ConstraintComponent->SetConstrainedComponents(Cube1, NAME_None, Cube2, NAME_None);
	// ConstraintComponent->ComponentName1.ComponentName = TEXT("Cube1");
	// ConstraintComponent->ComponentName2.ComponentName = TEXT("Cube2");

	ConstraintComponent->RegisterComponent();
}

// Called every frame
void AwithPMC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
