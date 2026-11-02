// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateDimmer.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateDimmer::ADelegateDimmer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	IncreaseButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IncreaseButtonMesh"));
	IncreaseButtonMesh->SetupAttachment(SceneRoot);
	IncreaseButtonMesh->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	IncreaseButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	IncreaseButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	IncreaseButtonMesh->SetGenerateOverlapEvents(false);

	DecreaseButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecreaseButtonMesh"));
	DecreaseButtonMesh->SetupAttachment(SceneRoot);
	DecreaseButtonMesh->SetRelativeLocation(FVector(0.0f, -100.0f, 0.0f));
	DecreaseButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DecreaseButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	DecreaseButtonMesh->SetGenerateOverlapEvents(false);

	IncreaseBox = CreateDefaultSubobject<UBoxComponent>(TEXT("IncreaseBox"));
	IncreaseBox->SetupAttachment(IncreaseButtonMesh);
	IncreaseBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	IncreaseBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	IncreaseBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	IncreaseBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	IncreaseBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	IncreaseBox->SetGenerateOverlapEvents(true);

	DecreaseBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DecreaseBox"));
	DecreaseBox->SetupAttachment(DecreaseButtonMesh);
	DecreaseBox->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	DecreaseBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	DecreaseBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DecreaseBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DecreaseBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DecreaseBox->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ADelegateDimmer::BeginPlay()
{
	Super::BeginPlay();

	IncreaseBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateDimmer::HandleBeginOverlap);
	DecreaseBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateDimmer::HandleBeginOverlap);

	IncreaseBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateDimmer::HandleEndOverlap);
	DecreaseBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateDimmer::HandleEndOverlap);

	UpdateButtonVisuals(IncreaseButtonMesh.Get(), false);
	UpdateButtonVisuals(DecreaseButtonMesh.Get(), false);
}

// Called every frame
void ADelegateDimmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateDimmer::IncreaseLevel()
{
	SetDimmerLevel(CurrentLevel + StepSize);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateDimmer::DecreaseLevel()
{
	SetDimmerLevel(CurrentLevel - StepSize);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateDimmer::SetDimmerLevel(float NewLevel)
{
	const float ClampedLevel = FMath::Clamp(NewLevel, 0.0f, 1.0f);

	if (FMath::IsNearlyEqual(CurrentLevel, ClampedLevel))
	{
		return;
	}

	CurrentLevel = ClampedLevel;
	OnLevelChanged.Broadcast(CurrentLevel);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateDimmer::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
	{
		return;
	}

	if (OverlappedComponent == IncreaseBox.Get())
	{
		UpdateButtonVisuals(IncreaseButtonMesh.Get(), true);
		IncreaseLevel();
	}
	else if (OverlappedComponent == DecreaseBox.Get())
	{
		UpdateButtonVisuals(DecreaseButtonMesh.Get(), true);
		DecreaseLevel();
	}
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateDimmer::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
	{
		return;
	}

	if (OverlappedComponent == IncreaseBox.Get())
	{
		UpdateButtonVisuals(IncreaseButtonMesh.Get(), false);
	}
	else if (OverlappedComponent == DecreaseBox.Get())
	{
		UpdateButtonVisuals(DecreaseButtonMesh.Get(), false);
	}
}