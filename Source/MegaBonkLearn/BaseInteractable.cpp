// ============================================================
//  BaseInteractable.cpp — ИСПРАВЛЕННАЯ ВЕРСИЯ
//  Кодировка: сохранить как UTF-8 with BOM
// ============================================================
#include "BaseInteractable.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/Controller.h"

ABaseInteractable::ABaseInteractable()
{
    // Constructor: only component creation and defaults.
    // No GetWorld(), no SpawnActor - the CDO is constructed before a world exists.
    PrimaryActorTick.bCanEverTick = false;
}

void ABaseInteractable::BeginPlay()
{
    Super::BeginPlay();   // Without this, BP "Event BeginPlay" never fires.

    CurrentHealth = MaxHealth;
    UE_LOG(LogTemp, Log, TEXT("[%s] spawned with HP = %.1f"), *GetName(), CurrentHealth);
}

float ABaseInteractable::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent,
                                    AController* EventInstigator, AActor* DamageCauser)
{
    // ALWAYS call Super first: it broadcasts OnTakeAnyDamage / OnTakePointDamage
    // delegates that other systems may be listening to.
    const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (bIsDead || ActualDamage <= 0.0f)
    {
        return ActualDamage;
    }

    LastDamageInstigator = EventInstigator;

    CurrentHealth = FMath::Max(0.0f, CurrentHealth - ActualDamage);

    UE_LOG(LogTemp, Warning, TEXT("[%s] took %.1f dmg (causer: %s), HP left %.1f"),
        *GetName(), ActualDamage,
        DamageCauser ? *DamageCauser->GetName() : TEXT("none"),
        CurrentHealth);

    OnDamaged(ActualDamage);   // BlueprintNativeEvent - call WITHOUT the _Implementation suffix

    if (CurrentHealth <= 0.0f)
    {
        bIsDead = true;
        OnDeath();             // BlueprintImplementableEvent - body lives in Blueprint only
    }

    return ActualDamage;
}

void ABaseInteractable::OnDamaged_Implementation(float ActualDamage)
{
    // Default implementation is intentionally empty. Blueprint may override.
}
