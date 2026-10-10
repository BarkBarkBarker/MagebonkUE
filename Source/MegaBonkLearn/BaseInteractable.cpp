#include "BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{
    // В конструкторе — только создание компонентов и дефолты.
    // Обращаться к GetWorld() и другим актёрам здесь НЕЛЬЗЯ.
    PrimaryActorTick.bCanEverTick = false;   // ← осознанно: нам не нужен тик
}

void ABaseInteractable::BeginPlay()
{
    Super::BeginPlay();                      // ← забыть = мистические баги
    CurrentHealth = MaxHealth;
    UE_LOG(LogTemp, Log, TEXT("[%s] spawned with HP = %.1f"), *GetName(), CurrentHealth);
}

void ABaseInteractable::TakeDamage(float DamageAmount)
{
    if (bIsDead) { return; }                 // мёртвые не умирают второй раз

    CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
    UE_LOG(LogTemp, Warning, TEXT("[%s] took %.1f dmg, HP left %.1f"),
        *GetName(), DamageAmount, CurrentHealth);

    OnDamaged(DamageAmount);                 // вызываем BlueprintNativeEvent

    if (CurrentHealth <= 0.0f)
    {
        bIsDead = true;
        OnDeath();                           // вызываем BlueprintImplementableEvent
    }
}

void ABaseInteractable::OnDamaged_Implementation(float DamageAmount)
{
    // Реализация по умолчанию — пустая. BP может переопределить.
}