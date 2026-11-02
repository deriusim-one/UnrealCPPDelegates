// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateLightPanel.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateLightPanel::ADelegateLightPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ButtonAMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonAMesh"));
    ButtonAMesh->SetupAttachment(SceneRoot);
    ButtonAMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonAMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ButtonAMesh->SetGenerateOverlapEvents(false);
    ButtonAMesh->SetRelativeLocation(FVector(250.0f, 10.0f, 0.0f));
    ButtonAMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 30.0f));

	ButtonBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonBMesh"));
    ButtonBMesh->SetupAttachment(SceneRoot);
    ButtonBMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonBMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ButtonBMesh->SetGenerateOverlapEvents(false);
    ButtonBMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	ButtonCMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonCMesh"));
    ButtonCMesh->SetupAttachment(SceneRoot);
    ButtonCMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonCMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ButtonCMesh->SetGenerateOverlapEvents(false);
    ButtonCMesh->SetRelativeLocation(FVector(-250.0f, 10.0f, 0.0f));
    ButtonCMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -30.0f));

    ButtonABox = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonABox"));
    ButtonABox->SetupAttachment(ButtonAMesh);
    ButtonABox->SetRelativeLocation(FVector(0.0f, -70.0f, 100.0f));
    ButtonABox->SetBoxExtent(FVector(30.0f, 30.0f, 100.0f));
    ButtonABox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonABox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ButtonABox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ButtonABox->SetGenerateOverlapEvents(true);
    
    ButtonBBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonBBox"));
    ButtonBBox->SetupAttachment(ButtonBMesh);
    ButtonBBox->SetRelativeLocation(FVector(0.0f, -70.0f, 100.0f));
    ButtonBBox->SetBoxExtent(FVector(30.0f, 30.0f, 100.0f));
    ButtonBBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonBBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ButtonBBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ButtonBBox->SetGenerateOverlapEvents(true);
    
    ButtonCBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCBox"));
    ButtonCBox->SetupAttachment(ButtonCMesh);
    ButtonCBox->SetRelativeLocation(FVector(0.0f, -70.0f, 100.0f));
    ButtonCBox->SetBoxExtent(FVector(30.0f, 30.0f, 100.0f));
    ButtonCBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonCBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ButtonCBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ButtonCBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ADelegateLightPanel::BeginPlay()
{
	Super::BeginPlay();

    ButtonABox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateLightPanel::HandleBeginOverlap);
    ButtonABox->OnComponentEndOverlap.AddDynamic(this, &ADelegateLightPanel::HandleEndOverlap);

    ButtonBBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateLightPanel::HandleBeginOverlap);
    ButtonBBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateLightPanel::HandleEndOverlap);

    ButtonCBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateLightPanel::HandleBeginOverlap);
    ButtonCBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateLightPanel::HandleEndOverlap);

    UpdateButtonVisuals(ButtonAMesh.Get(), false);
    UpdateButtonVisuals(ButtonBMesh.Get(), false);
    UpdateButtonVisuals(ButtonCMesh.Get(), false);
}

// Called every frame
void ADelegateLightPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLightPanel::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UStaticMeshComponent* ButtonMesh = Cast<UStaticMeshComponent>(OverlappedComponent->GetAttachParent());
    if (ButtonMesh)
    {
        UpdateButtonVisuals(ButtonMesh, true);
    }

    if (OverlappedComponent == ButtonABox.Get())
    {
        SetLightSettings(IntensityA, LightColorA, TargetRotationA);
    }
    else if (OverlappedComponent == ButtonBBox.Get())
    {
        SetLightSettings(IntensityB, LightColorB, TargetRotationB);
    }
    else if (OverlappedComponent == ButtonCBox.Get())
    {
        SetLightSettings(IntensityC, LightColorC, TargetRotationC);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLightPanel::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    const ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (!Character || !Character->IsPlayerControlled() || OtherComponent != Character->GetCapsuleComponent())
    {
        return;
    }

    UStaticMeshComponent* ButtonMesh = Cast<UStaticMeshComponent>(OverlappedComponent->GetAttachParent());

    if (ButtonMesh)
    {
        UpdateButtonVisuals(ButtonMesh, false);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLightPanel::SetLightSettings(float NewIntensity, FLinearColor NewLightColor, FRotator NewTargetRotation)
{
    CurrentIntensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f);
    CurrentLightColor = NewLightColor;
    CurrentTargetRotation = NewTargetRotation;

    OnLightSettingsChanged.Broadcast(CurrentIntensity, CurrentLightColor, CurrentTargetRotation);
}


