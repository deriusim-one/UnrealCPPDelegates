// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateSinglecastButton.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateSinglecastButton::ADelegateSinglecastButton()
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
void ADelegateSinglecastButton::BeginPlay()
{
	Super::BeginPlay();

    ActivationBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateSinglecastButton::HandleBeginOverlap);
    ActivationBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateSinglecastButton::HandleEndOverlap);

    UpdateButtonVisuals(false);
}

void ADelegateSinglecastButton::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    ClearCommand();

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADelegateSinglecastButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastButton::SetCommand(FDynamicButtonCommandSignature InCommand)
{
    Command = InCommand;
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastButton::ClearCommand()
{
    Command.Unbind();
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastButton::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UpdateButtonVisuals(true);
    Command.ExecuteIfBound(true);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastButton::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UpdateButtonVisuals(false);
    Command.ExecuteIfBound(false);
}

