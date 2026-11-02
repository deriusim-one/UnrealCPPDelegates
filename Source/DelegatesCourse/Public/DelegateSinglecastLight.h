// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateSinglecastLight.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UPointLightComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateSinglecastLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateSinglecastLight();

	void SetLightState(bool bActive);

	void SetConnectionState(bool bConnected);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> BatteryPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BatteryMesh;

	UFUNCTION(BlueprintImplementableEvent, Category = "Light|Visual")
	void UpdateConnectionVisuals(bool bConnected);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
