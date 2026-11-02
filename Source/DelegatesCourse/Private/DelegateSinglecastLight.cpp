// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateSinglecastLight.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADelegateSinglecastLight::ADelegateSinglecastLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
    LightMesh->SetupAttachment(SceneRoot);

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(SceneRoot);
    PointLight->SetMobility(EComponentMobility::Movable);
    PointLight->SetVisibility(false);

    BatteryPivot = CreateDefaultSubobject<USceneComponent>(TEXT("BatteryPivot"));
    BatteryPivot->SetupAttachment(SceneRoot);
    BatteryPivot->SetMobility(EComponentMobility::Movable);

    BatteryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BatteryMesh"));
    BatteryMesh->SetupAttachment(BatteryPivot);
    BatteryMesh->SetMobility(EComponentMobility::Movable);
    BatteryMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADelegateSinglecastLight::BeginPlay()
{
	Super::BeginPlay();

    SetLightState(false);
    SetConnectionState(false);	
}

// Called every frame
void ADelegateSinglecastLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastLight::SetLightState(bool bActive)
{
    PointLight->SetVisibility(bActive);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateSinglecastLight::SetConnectionState(bool bConnected)
{
    UpdateConnectionVisuals(bConnected);
}