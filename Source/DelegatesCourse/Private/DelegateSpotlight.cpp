// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateSpotlight.h"
#include "DelegateLightPanel.h"
#include "Components/SceneComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADelegateSpotlight::ADelegateSpotlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);
    SceneRoot->SetMobility(EComponentMobility::Movable);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(SceneRoot);
    BaseMesh->SetMobility(EComponentMobility::Movable);
    BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BaseMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    BaseMesh->SetGenerateOverlapEvents(false);

    RotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationPivot"));
    RotationPivot->SetupAttachment(SceneRoot);
    RotationPivot->SetMobility(EComponentMobility::Movable);

    HingeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HingeMesh"));
    HingeMesh->SetupAttachment(RotationPivot);
    HingeMesh->SetMobility(EComponentMobility::Movable);
    HingeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
    HeadMesh->SetupAttachment(HingeMesh);
    HeadMesh->SetMobility(EComponentMobility::Movable);
    HeadMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetupAttachment(HeadMesh);
    SpotLight->SetMobility(EComponentMobility::Movable);

}

// Called when the game starts or when spawned
void ADelegateSpotlight::BeginPlay()
{
	Super::BeginPlay();

    if (IsValid(LightPanel))
    {
        LightPanel->OnLightSettingsChanged.AddDynamic(this, &ADelegateSpotlight::ApplyLightSettings);
        ApplyLightSettings(LightPanel->GetCurrentIntensity(), LightPanel->GetCurrentLightColor(), LightPanel->GetCurrentTargetRotation());
    }
}

// Called every frame
void ADelegateSpotlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADelegateSpotlight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (IsValid(LightPanel))
    {
        LightPanel->OnLightSettingsChanged.RemoveDynamic(this, &ADelegateSpotlight::ApplyLightSettings);
    }

    Super::EndPlay(EndPlayReason);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSpotlight::ApplyLightSettings(float NewIntensity, FLinearColor NewLightColor, FRotator NewTargetRotation)
{
    const float TargetIntensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f) * MaxIntensity;
    AnimateLightSettings(TargetIntensity, NewLightColor, NewTargetRotation);
}
