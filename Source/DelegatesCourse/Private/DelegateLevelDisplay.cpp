// Copyright 2026 deriusim.one. Tutti i diritti riservati.


#include "DelegateLevelDisplay.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "DelegateDimmer.h"

// Sets default values
ADelegateLevelDisplay::ADelegateLevelDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    LevelWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LevelWidget"));
    LevelWidget->SetupAttachment(SceneRoot);
    LevelWidget->SetWidgetSpace(EWidgetSpace::World);
    LevelWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ADelegateLevelDisplay::BeginPlay()
{
	Super::BeginPlay();

    LevelWidget->InitWidget();

    if (IsValid(Dimmer))
    {
        Dimmer->OnLevelChanged.AddDynamic(this, &ADelegateLevelDisplay::HandleLevelChanged);
        HandleLevelChanged(Dimmer->GetCurrentLevel());
    }
	
}

// Called every frame
void ADelegateLevelDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADelegateLevelDisplay::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (IsValid(Dimmer))
    {
        Dimmer->OnLevelChanged.RemoveDynamic(this, &ADelegateLevelDisplay::HandleLevelChanged);
    }

    Super::EndPlay(EndPlayReason);
}

////////////////////////////////////////////////////////////////////////////////////////
void ADelegateLevelDisplay::HandleLevelChanged(float NewLevel)
{
    UpdateDisplayVisuals(NewLevel);
}