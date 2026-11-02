// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateLightPanel.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLightSettingsChangedSignature, float, NewIntensity, FLinearColor, NewLightColor, FRotator, NewTargetRotation);


UCLASS()
class DELEGATESCOURSE_API ADelegateLightPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateLightPanel();

	UPROPERTY(BlueprintAssignable, Category = "Panel")
	FLightSettingsChangedSignature OnLightSettingsChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonAMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonBMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonCMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonABox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonBBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonCBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IntensityA = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FLinearColor LightColorA = FLinearColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FRotator TargetRotationA = FRotator(0.0f, 40.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IntensityB = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FLinearColor LightColorB = FLinearColor(1.0f, 0.25f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FRotator TargetRotationB = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IntensityC = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FLinearColor LightColorC = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Presets")
	FRotator TargetRotationC = FRotator(0.0f, -40.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel|State")
	float CurrentIntensity = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel|State")
	FLinearColor CurrentLightColor = FLinearColor::White;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel|State")
	FRotator CurrentTargetRotation = FRotator::ZeroRotator;
	
	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Panel|Visual")
	void UpdateButtonVisuals(UStaticMeshComponent* ButtonMesh, bool bActive);

	UFUNCTION(BlueprintCallable, Category = "Panel")
	void SetLightSettings( float NewIntensity, FLinearColor NewLightColor, FRotator NewTargetRotation);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Panel")
	float GetCurrentIntensity() const { return CurrentIntensity; }

	UFUNCTION(BlueprintPure, Category = "Panel")
	FLinearColor GetCurrentLightColor() const { return CurrentLightColor; }

	UFUNCTION(BlueprintPure, Category = "Panel")
	FRotator GetCurrentTargetRotation() const { return CurrentTargetRotation; }

};
