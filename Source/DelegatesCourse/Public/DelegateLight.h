// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "Components/PointLightComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateLight.generated.h"

class ADelegateButton;


UCLASS()
class DELEGATESCOURSE_API ADelegateLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateLight();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UFUNCTION()
	void TurnOnLight();

	UFUNCTION()
	void TurnOffLight();

	UPROPERTY(EditInstanceOnly, Category = "Delegates")
	TObjectPtr<ADelegateButton> Button = nullptr;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
