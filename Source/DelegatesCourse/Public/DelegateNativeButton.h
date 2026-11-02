// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateNativeButton.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FNativeButtonStateChangedSignature, bool);

UCLASS()
class DELEGATESCOURSE_API ADelegateNativeButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADelegateNativeButton();

	FNativeButtonStateChangedSignature OnStateChanged;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ActivationBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Button|Visual")
	void UpdateButtonVisuals(bool bActive);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

