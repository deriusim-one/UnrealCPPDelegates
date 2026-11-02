// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#include "DelegateNativeButton.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateNativeButton::ADelegateNativeButton()
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
void ADelegateNativeButton::BeginPlay()
{
	Super::BeginPlay();

	ActivationBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateNativeButton::HandleBeginOverlap);
	ActivationBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateNativeButton::HandleEndOverlap);

	UpdateButtonVisuals(false);
}

// Called every frame
void ADelegateNativeButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateNativeButton::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
	{
		return;
	}

	UpdateButtonVisuals(true);
	OnStateChanged.Broadcast(true);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateNativeButton::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
	{
		return;
	}

	UpdateButtonVisuals(false);
	OnStateChanged.Broadcast(false);
}


