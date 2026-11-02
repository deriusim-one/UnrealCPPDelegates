// Copyright 2026 deriusim.one. Tutti i diritti riservati.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateNativeLight.generated.h"

class ADelegateNativeButton;
class UPointLightComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class DELEGATESCOURSE_API ADelegateNativeLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateNativeLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(EditInstanceOnly, Category = "Delegates")
	TObjectPtr<ADelegateNativeButton> Button = nullptr;

	FDelegateHandle StateChangedHandle;

	FDelegateHandle StaticMessageHandle;
	
	FDelegateHandle LambdaMessageHandle;

	void SetLightState(bool bActive);

	static void ShowStaticMessage(bool bActive);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
