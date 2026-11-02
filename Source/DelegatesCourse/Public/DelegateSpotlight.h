// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateSpotlight.generated.h"

class ADelegateLightPanel;
class USceneComponent;
class UStaticMeshComponent;
class USpotLightComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateSpotlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateSpotlight();

	UFUNCTION(BlueprintCallable, Category = "Spotlight")
	void ApplyLightSettings(float NewIntensity, FLinearColor NewLightColor, FRotator NewTargetRotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Delegates")
	TObjectPtr<ADelegateLightPanel> LightPanel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> RotationPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> HingeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> HeadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spotlight", meta = (ClampMin = "0.0"))
	float MaxIntensity = 10000.0f;

	UFUNCTION(BlueprintImplementableEvent, Category = "Spotlight|Visual")
	void AnimateLightSettings(float TargetIntensity, FLinearColor TargetColor, FRotator TargetRotation);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
