// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegatePressurePlate.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

// ESERCIZIO_BEGIN: signature
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegatePlateEventSignature);
// ESERCIZIO_END

UCLASS()
class DELEGATESCOURSE_API ADelegatePressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegatePressurePlate();

	// ESERCIZIO_BEGIN: proprietà dei delegate
	UPROPERTY(BlueprintAssignable, Category = "PressurePlate|Events")
	FDelegatePlateEventSignature OnActivated;

	UPROPERTY(BlueprintAssignable, Category = "PressurePlate|Events")
	FDelegatePlateEventSignature OnDeactivated;
	// ESERCIZIO_END

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ActivationBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlateMesh;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "PressurePlate|Visual")
	void UpdatePlateVisuals(bool bPressed);
	
	bool bIsPressed = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
