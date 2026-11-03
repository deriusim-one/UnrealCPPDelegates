// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateChargingStation.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;

DECLARE_DYNAMIC_DELEGATE(FChargeOperationCompletedSignature);


UCLASS()
class DELEGATESCOURSE_API ADelegateChargingStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateChargingStation();

	UFUNCTION(BlueprintCallable, Category = "Charge")
	void StartCharge(FChargeOperationCompletedSignature OnCompleted);

	UFUNCTION(BlueprintCallable, Category = "Charge")
	void StartDischarge(FChargeOperationCompletedSignature OnCompleted);

	UFUNCTION(BlueprintCallable, Category = "Charge|Visual")
	void NotifyBatteryMovementFinished(bool bAtLight);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> BatteryPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BatteryMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> ChargeWidget;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Charge")
	float CurrentCharge = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Charge", meta = (ClampMin = "0.1"))
	float ChargeDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Charge", meta = (ClampMin = "0.1"))
	float DischargeDuration = 5.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Charge")
	bool bOperationInProgress = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Charge|Visual")
	bool bBatteryAtLight = false;

	bool bWaitingForBatteryMovement = false;

	float OperationStartCharge = 0.0f;

	float OperationTargetCharge = 0.0f;

	float OperationElapsedTime = 0.0f;

	float OperationDuration = 1.0f;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Charge|Visual")
	void UpdateChargeVisuals(float NewCharge);

	UFUNCTION(BlueprintImplementableEvent, Category = "Charge|Visual")
	void UpdateConnectionVisuals(bool bConnected);

	void SetCharge(float NewCharge);

	void FinishOperation();

	void StartOperation(float TargetCharge, float Duration, const FChargeOperationCompletedSignature& OnCompleted);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
