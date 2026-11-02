// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateGears.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class ADelegatePressurePlate;


UCLASS()
class DELEGATESCOURSE_API ADelegateGears : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateGears();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Gear1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Gear2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Gear3;

	UPROPERTY(EditInstanceOnly, Category = "Delegates")
	TObjectPtr<ADelegatePressurePlate> PressurePlate = nullptr;

	UFUNCTION(BlueprintCallable)
	void StartGears();

	UFUNCTION(BlueprintCallable)
	void StopGears();

	bool bIsRunning = false;

	float RotationSpeed = 80.0f;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
