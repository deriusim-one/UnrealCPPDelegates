// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateLiftConsole.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DelegateLift.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateLiftConsole::ADelegateLiftConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    GroundButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundButtonMesh"));
    GroundButtonMesh->SetupAttachment(SceneRoot);
    GroundButtonMesh->SetRelativeLocation(FVector(0.0f, -100.0f, 0.0f));

    UpperButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpperButtonMesh"));
    UpperButtonMesh->SetupAttachment(SceneRoot);
    UpperButtonMesh->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));

    GroundBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundBox"));
    GroundBox->SetupAttachment(GroundButtonMesh);
    GroundBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    UpperBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UpperBox"));
    UpperBox->SetupAttachment(UpperButtonMesh);
    UpperBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    GroundButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    GroundButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    GroundButtonMesh->SetGenerateOverlapEvents(false);

    UpperButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    UpperButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    UpperButtonMesh->SetGenerateOverlapEvents(false);
  
    GroundBox->SetBoxExtent(FVector(30.0f, 30.0f, 100.0f));
    GroundBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    GroundBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    GroundBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    GroundBox->SetGenerateOverlapEvents(true);

    UpperBox->SetBoxExtent(FVector(30.0f, 30.0f, 100.0f));
    UpperBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    UpperBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    UpperBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    UpperBox->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ADelegateLiftConsole::BeginPlay()
{
	Super::BeginPlay();
	
    GroundBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateLiftConsole::HandleBeginOverlap);
    GroundBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateLiftConsole::HandleEndOverlap);
    
    UpperBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateLiftConsole::HandleBeginOverlap);
    UpperBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateLiftConsole::HandleEndOverlap);

    UpdateButtonVisuals(GroundButtonMesh.Get(), false);
    UpdateButtonVisuals(UpperButtonMesh.Get(), false);
}

// Called every frame
void ADelegateLiftConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLiftConsole::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    if (OverlappedComponent == GroundBox.Get())
    {
        UpdateButtonVisuals(GroundButtonMesh.Get(), true);
        RequestFloor(0);
    }
    else if (OverlappedComponent == UpperBox.Get())
    {
        UpdateButtonVisuals(UpperButtonMesh.Get(), true);
        RequestFloor(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLiftConsole::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    if (OverlappedComponent == GroundBox.Get())
    {
        UpdateButtonVisuals(GroundButtonMesh.Get(), false);
    }
    else if (OverlappedComponent == UpperBox.Get())
    {
        UpdateButtonVisuals(UpperButtonMesh.Get(), false);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
bool ADelegateLiftConsole::RequestFloor(int32 TargetFloor)
{
    if (!IsValid(Lift))
    {
        return false;
    }

    bool bCanMove = false;

    if (bCanMove)
    {
        Lift->MoveToFloor(TargetFloor);
    }

    return bCanMove;
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLiftConsole::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}