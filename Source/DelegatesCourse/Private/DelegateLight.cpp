// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateLight.h"
#include "DelegateButton.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADelegateLight::ADelegateLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	LightMesh->SetupAttachment(SceneRoot);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ADelegateLight::BeginPlay()
{
	Super::BeginPlay();
	
	TurnOffLight();

	if (IsValid(Button))
	{
		Button->OnActivated.AddDynamic(this, &ADelegateLight::TurnOnLight);
		Button->OnDeactivated.AddDynamic(this, &ADelegateLight::TurnOffLight);
	}
}

// Called every frame
void ADelegateLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(Button))
	{
		Button->OnActivated.RemoveDynamic(this, &ADelegateLight::TurnOnLight);
		Button->OnDeactivated.RemoveDynamic(this, &ADelegateLight::TurnOffLight);
	}

	Super::EndPlay(EndPlayReason);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLight::TurnOnLight()
{
	PointLight->SetVisibility(true);
}

void ADelegateLight::TurnOffLight()
{
	PointLight->SetVisibility(false);
}
