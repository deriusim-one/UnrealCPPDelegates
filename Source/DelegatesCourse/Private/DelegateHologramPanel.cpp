// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateHologramPanel.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ADelegateHologramPanel::ADelegateHologramPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    ShapeButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeButtonMesh"));
    ShapeButtonMesh->SetupAttachment(SceneRoot);
    ShapeButtonMesh->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
    ShapeButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ShapeButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ShapeButtonMesh->SetGenerateOverlapEvents(false);

    ColorButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ColorButtonMesh"));
    ColorButtonMesh->SetupAttachment(SceneRoot);
    ColorButtonMesh->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
    ColorButtonMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ColorButtonMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    ColorButtonMesh->SetGenerateOverlapEvents(false);

    ShapeButtonBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ShapeButtonBox"));
    ShapeButtonBox->SetupAttachment(ShapeButtonMesh);
    ShapeButtonBox->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
    ShapeButtonBox->SetBoxExtent(FVector(50.0f, 50.0f, 20.0f));
    ShapeButtonBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ShapeButtonBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ShapeButtonBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ShapeButtonBox->SetGenerateOverlapEvents(true);

    ColorButtonBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ColorButtonBox"));
    ColorButtonBox->SetupAttachment(ColorButtonMesh);
    ColorButtonBox->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
    ColorButtonBox->SetBoxExtent(FVector(50.0f, 50.0f, 20.0f));
    ColorButtonBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ColorButtonBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ColorButtonBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    ColorButtonBox->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ADelegateHologramPanel::BeginPlay()
{
	Super::BeginPlay();

    ShapeButtonBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateHologramPanel::HandleBeginOverlap); 
    ShapeButtonBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateHologramPanel::HandleEndOverlap);

    ColorButtonBox->OnComponentBeginOverlap.AddDynamic(this, &ADelegateHologramPanel::HandleBeginOverlap);
    ColorButtonBox->OnComponentEndOverlap.AddDynamic(this, &ADelegateHologramPanel::HandleEndOverlap);

    UpdateButtonVisuals(ShapeButtonMesh.Get(), false);
    UpdateButtonVisuals(ColorButtonMesh.Get(), false);
	
}

// Called every frame
void ADelegateHologramPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateHologramPanel::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

    if (OverlappedComponent == ShapeButtonBox.Get())
    {
        NextShape();
    }
    else if (OverlappedComponent == ColorButtonBox.Get())
    {
        NextColor();
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateHologramPanel::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
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
void ADelegateHologramPanel::NextShape()
{
    if (AvailableMeshes.IsEmpty())
    {
        return;
    }

    CurrentShapeIndex = (CurrentShapeIndex + 1) % AvailableMeshes.Num();
    NotifyHologramChanged();
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateHologramPanel::NextColor()
{
    if (AvailableColors.IsEmpty())
    {
        return;
    }

    CurrentColorIndex = (CurrentColorIndex + 1) % AvailableColors.Num();
    NotifyHologramChanged();
}

////////////////////////////////////////////////////////////////////////////////////////
UStaticMesh* ADelegateHologramPanel::GetCurrentMesh() const
{
    return AvailableMeshes.IsValidIndex(CurrentShapeIndex)
        ? AvailableMeshes[CurrentShapeIndex].Get()
        : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
FLinearColor ADelegateHologramPanel::GetCurrentColor() const
{
    return AvailableColors.IsValidIndex(CurrentColorIndex)
        ? AvailableColors[CurrentColorIndex]
        : FLinearColor::White;
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateHologramPanel::NotifyHologramChanged()
{
    UStaticMesh* SelectedMesh = GetCurrentMesh();

    if (!IsValid(SelectedMesh))
    {
        return;
    }
}