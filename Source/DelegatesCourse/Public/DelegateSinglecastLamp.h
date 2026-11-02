// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateSinglecastLamp.generated.h"

class ADelegateSinglecastButton;
class UPointLightComponent;
class USceneComponent;
class UStaticMeshComponent;


UCLASS()
class DELEGATESCOURSE_API ADelegateSinglecastLamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateSinglecastLamp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLightState(bool bActive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Delegates")
	TObjectPtr<ADelegateSinglecastButton> Button = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
