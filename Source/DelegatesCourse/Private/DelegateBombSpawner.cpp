// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateBombSpawner.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

// Sets default values
ADelegateBombSpawner::ADelegateBombSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
    SpawnPoint->SetupAttachment(SceneRoot);
    SpawnPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

}

// Called when the game starts or when spawned
void ADelegateBombSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADelegateBombSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
bool ADelegateBombSpawner::CanSpawnBomb() const
{
    return BombClass.Get() != nullptr && !IsValid(ActiveBomb);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateBombSpawner::SpawnBomb()
{
    UWorld* World = GetWorld();

    if (!World || !CanSpawnBomb())
    {
        return;
    }

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ActiveBomb = World->SpawnActor<AActor>(BombClass.Get(), SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParameters);
}