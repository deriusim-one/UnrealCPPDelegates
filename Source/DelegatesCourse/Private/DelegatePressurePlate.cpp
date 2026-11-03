// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegatePressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegatePressurePlate::ADelegatePressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
    PlateMesh->SetupAttachment(SceneRoot);
    PlateMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PlateMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    PlateMesh->SetGenerateOverlapEvents(false);

    ActivationBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivationBox"));
    ActivationBox->SetupAttachment(SceneRoot);
    ActivationBox->SetBoxExtent(FVector(50.0f, 50.0f, 20.0f));
    ActivationBox->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
    ActivationBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ActivationBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ActivationBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ActivationBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ADelegatePressurePlate::BeginPlay()
{
	Super::BeginPlay();

    UpdatePlateVisuals(false);

    ActivationBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegatePressurePlate::HandleBeginOverlap);

    ActivationBox->OnComponentEndOverlap.AddDynamic(this, &ADelegatePressurePlate::HandleEndOverlap);
}

// Called every frame
void ADelegatePressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegatePressurePlate::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent() || bIsPressed)
    {
        return;
    }

    bIsPressed = true;
    UpdatePlateVisuals(true);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegatePressurePlate::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex) 
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent() || !bIsPressed)
    {
        return;
    }

    bIsPressed = false;
    UpdatePlateVisuals(false);
}