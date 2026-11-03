// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateNativeGears.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateNativeButton.h"

// Sets default values
ADelegateNativeGears::ADelegateNativeGears()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    Gear1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gear1"));
    Gear1->SetupAttachment(SceneRoot);
    Gear1->SetMobility(EComponentMobility::Movable);
    Gear1->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Gear2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gear2"));
    Gear2->SetupAttachment(SceneRoot);
    Gear2->SetMobility(EComponentMobility::Movable);
    Gear2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Gear3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gear3"));
    Gear3->SetupAttachment(SceneRoot);
    Gear3->SetMobility(EComponentMobility::Movable);
    Gear3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADelegateNativeGears::BeginPlay()
{
	Super::BeginPlay();

    SetGearsState(false);
}

// Called every frame
void ADelegateNativeGears::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsRunning)
    {
        return;
    }

    const float DeltaAngle = RotationSpeed * DeltaTime;

    Gear1->AddLocalRotation(FRotator(0.0f, DeltaAngle, 0.0f));
    Gear2->AddLocalRotation(FRotator(0.0f, -DeltaAngle, 0.0f));
    Gear3->AddLocalRotation(FRotator(0.0f, DeltaAngle, 0.0f));
}

void ADelegateNativeGears::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StateChangedHandle.Reset();

    Super::EndPlay(EndPlayReason);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateNativeGears::SetGearsState(bool bActive)
{
    bIsRunning = bActive;
}