// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateLift.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADelegateLift::ADelegateLift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
    FrameMesh->SetupAttachment(SceneRoot);
    FrameMesh->SetCollisionProfileName(TEXT("BlockAll"));

    PlatformPivot = CreateDefaultSubobject<USceneComponent>(TEXT("PlatformPivot"));
    PlatformPivot->SetupAttachment(SceneRoot);
    PlatformPivot->SetMobility(EComponentMobility::Movable);

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    PlatformMesh->SetupAttachment(PlatformPivot);
    PlatformMesh->SetMobility(EComponentMobility::Movable);
    PlatformMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    PlatformMesh->SetGenerateOverlapEvents(false);

}

// Called when the game starts or when spawned
void ADelegateLift::BeginPlay()
{
	Super::BeginPlay();

    GroundFloorLocation = PlatformPivot->GetRelativeLocation();
}

// Called every frame
void ADelegateLift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsMoving)
    {
        SetActorTickEnabled(false);
        return;
    }

    TravelElapsedTime += DeltaTime;

    const float Alpha = FMath::Clamp(TravelElapsedTime / TravelDuration, 0.0f, 1.0f);
    const float EasedAlpha = FMath::InterpEaseInOut(0.0f, 1.0f, Alpha, 2.0f);

    PlatformPivot->SetRelativeLocation(FMath::Lerp(MovementStartLocation, MovementTargetLocation, EasedAlpha));

    if (Alpha >= 1.0f)
    {
        PlatformPivot->SetRelativeLocation(MovementTargetLocation);

        CurrentFloor = DestinationFloor;
        bIsMoving = false;

        SetActorTickEnabled(false);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
bool ADelegateLift::CanMoveToFloor(int32 TargetFloor) const
{
    return !bIsMoving
        && TargetFloor >= 0
        && TargetFloor <= 1
        && TargetFloor != CurrentFloor
        && TravelDuration > 0.0f
        && UpperFloorHeight > 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLift::MoveToFloor(int32 TargetFloor)
{
    if (!CanMoveToFloor(TargetFloor))
    {
        return;
    }

    DestinationFloor = TargetFloor;

    MovementStartLocation = PlatformPivot->GetRelativeLocation();

    const float HeightOffset = TargetFloor == 1 ? UpperFloorHeight : 0.0f;

    MovementTargetLocation = GroundFloorLocation + FVector(0.0f, 0.0f, HeightOffset);

    TravelElapsedTime = 0.0f;
    bIsMoving = true;

    SetActorTickEnabled(true);
}