// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateHologramDisplay.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateHologramPanel.h"
#include "Engine/StaticMesh.h"

// Sets default values
ADelegateHologramDisplay::ADelegateHologramDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);
    SceneRoot->SetMobility(EComponentMobility::Movable);

    HologramMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HologramMesh"));
    HologramMesh->SetupAttachment(SceneRoot);
    HologramMesh->SetMobility(EComponentMobility::Movable);
    HologramMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    HologramMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ADelegateHologramDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void ADelegateHologramDisplay::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADelegateHologramDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateHologramDisplay::ApplyHologramSettings(UStaticMesh* NewMesh, FLinearColor NewColor)
{
    if (!IsValid(NewMesh))
    {
        return;
    }

    HologramMesh->SetStaticMesh(NewMesh);
    UpdateHologramVisuals(NewMesh, NewColor);
    HologramMesh->SetHiddenInGame(false);
}