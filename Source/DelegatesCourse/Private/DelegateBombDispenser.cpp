// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateBombDispenser.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateBombSpawner.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

// Sets default values
ADelegateBombDispenser::ADelegateBombDispenser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
 
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    ActivationBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivationBox"));
    ActivationBox->SetupAttachment(SceneRoot);

    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    ButtonMesh->SetupAttachment(SceneRoot);

    ActivationBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ActivationBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ActivationBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ActivationBox->SetGenerateOverlapEvents(true);

    ButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ButtonMesh->SetGenerateOverlapEvents(false);

}

// Called when the game starts or when spawned
void ADelegateBombDispenser::BeginPlay()
{
	Super::BeginPlay();
	
    ActivationBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateBombDispenser::HandleBeginOverlap);
    ActivationBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateBombDispenser::HandleEndOverlap);

    UpdateButtonVisuals(false);

    if (IsValid(BombSpawner))
    {
        CanSpawnBombDelegate.BindUObject(BombSpawner.Get(), &ADelegateBombSpawner::CanSpawnBomb);
    }
}

void ADelegateBombDispenser::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CanSpawnBombDelegate.Unbind();

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADelegateBombDispenser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateBombDispenser::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UpdateButtonVisuals(true);

    if (!IsValid(BombSpawner) || !CanSpawnBombDelegate.IsBound())
    {
        return;
    }

    const bool bCanSpawn = CanSpawnBombDelegate.Execute();

    if (bCanSpawn)
    {
        BombSpawner->SpawnBomb();
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateBombDispenser::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UpdateButtonVisuals(false);
}