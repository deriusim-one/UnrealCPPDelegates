// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateChargingStation.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADelegateChargingStation::ADelegateChargingStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(SceneRoot);
    BaseMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    BaseMesh->SetGenerateOverlapEvents(false);

    BatteryPivot = CreateDefaultSubobject<USceneComponent>(TEXT("BatteryPivot"));
    BatteryPivot->SetupAttachment(SceneRoot);
    BatteryPivot->SetMobility(EComponentMobility::Movable);

    BatteryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BatteryMesh"));
    BatteryMesh->SetupAttachment(BatteryPivot);
    BatteryMesh->SetMobility(EComponentMobility::Movable);
    BatteryMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ChargeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChargeWidget"));
    ChargeWidget->SetupAttachment(SceneRoot);
    ChargeWidget->SetWidgetSpace(EWidgetSpace::World);
    ChargeWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ADelegateChargingStation::BeginPlay()
{
	Super::BeginPlay();
	
    ChargeWidget->InitWidget();

    SetCharge(CurrentCharge);
}

void ADelegateChargingStation::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    bOperationInProgress = false;
    SetActorTickEnabled(false);

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADelegateChargingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bOperationInProgress || bWaitingForBatteryMovement)
    {
        return;
    }

    OperationElapsedTime += DeltaTime;

    const float Alpha = FMath::Clamp(OperationElapsedTime / OperationDuration, 0.0f, 1.0f);

    SetCharge(FMath::Lerp(OperationStartCharge, OperationTargetCharge, Alpha));

    if (Alpha >= 1.0f)
    {
        SetActorTickEnabled(false);

        if (OperationTargetCharge >= 1.0f && !bBatteryAtLight)
        {
            bWaitingForBatteryMovement = true;
            UpdateConnectionVisuals(true);
        }
        else
        {
            FinishOperation();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::SetCharge(float NewCharge)
{
    CurrentCharge = FMath::Clamp(NewCharge, 0.0f, 1.0f);

    UpdateChargeVisuals(CurrentCharge);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::StartCharge(FChargeOperationCompletedSignature OnCompleted)
{
    StartOperation(1.0f, ChargeDuration, OnCompleted);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::StartDischarge(FChargeOperationCompletedSignature OnCompleted)
{
    StartOperation(0.0f, DischargeDuration, OnCompleted);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::StartOperation(float TargetCharge, float Duration, const FChargeOperationCompletedSignature& OnCompleted)
{
    if (bOperationInProgress)
    {
        return;
    }

    OperationStartCharge = CurrentCharge;
    OperationTargetCharge = FMath::Clamp(TargetCharge, 0.0f, 1.0f);
    OperationElapsedTime = 0.0f;
    OperationDuration = FMath::Max(Duration, 0.1f);

    bOperationInProgress = true;

    bWaitingForBatteryMovement = OperationTargetCharge >= 1.0f && bBatteryAtLight;

    if (bWaitingForBatteryMovement)
    {
        SetActorTickEnabled(false);
        UpdateConnectionVisuals(false);
    }
    else
    {
        SetActorTickEnabled(true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::FinishOperation()
{
    bOperationInProgress = false;
    SetActorTickEnabled(false);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateChargingStation::NotifyBatteryMovementFinished(
    bool bAtLight)
{
    if (!bOperationInProgress || !bWaitingForBatteryMovement || bAtLight == bBatteryAtLight)
    {
        return;
    }

    bBatteryAtLight = bAtLight;
    bWaitingForBatteryMovement = false;

    if (bBatteryAtLight)
    {
        FinishOperation();
    }
    else
    {
        SetActorTickEnabled(true);
    }
}