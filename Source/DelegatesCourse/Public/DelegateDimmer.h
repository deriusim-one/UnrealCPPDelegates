// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateDimmer.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDimmerLevelChangedSignature, float, NewLevel);


UCLASS()
class DELEGATESCOURSE_API ADelegateDimmer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateDimmer();

	UPROPERTY(BlueprintAssignable, Category = "Dimmer|Events")
	FDimmerLevelChangedSignature OnLevelChanged;

	UFUNCTION(BlueprintCallable, Category = "Dimmer")
	void IncreaseLevel();

	UFUNCTION(BlueprintCallable, Category = "Dimmer")
	void DecreaseLevel();

	UFUNCTION(BlueprintCallable, Category = "Dimmer")
	void SetDimmerLevel(float NewLevel);

	UFUNCTION(BlueprintPure, Category = "Dimmer")
	float GetCurrentLevel() const { return CurrentLevel; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> IncreaseButtonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DecreaseButtonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> IncreaseBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> DecreaseBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dimmer")
	float CurrentLevel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dimmer", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StepSize = 0.25f;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Dimmer|Visual")
	void UpdateButtonVisuals(UStaticMeshComponent* ButtonMesh, bool bActive);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
