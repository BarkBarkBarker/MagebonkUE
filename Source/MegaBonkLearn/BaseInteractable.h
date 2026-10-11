#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"   // ОБЯЗАТЕЛЬНО последним

UCLASS(Blueprintable)   // Blueprintable = от этого класса можно наследоваться в BP
class MEGABONKLEARN_API ABaseInteractable : public AActor
{
    GENERATED_BODY()

public:
    ABaseInteractable();

    /** Стартовое здоровье. EditAnywhere — видно в Details; BlueprintReadWrite — читается и пишется из BP. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    float CurrentHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    bool bIsDead = false;

    /** Нанести урон. BlueprintCallable — можно вызвать из BP. */
    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void TakeDamage(float DamageAmount);

    /** Хук для BP: что сделать при смерти (VFX, звук, дроп). Реализация ТОЛЬКО в Blueprint. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnDeath();

    /** Хук с реализацией по умолчанию в C++, BP может переопределить. */
    UFUNCTION(BlueprintNativeEvent, Category = "Combat")
    void OnDamaged(float DamageAmount);

protected:
    virtual void BeginPlay() override;
    virtual void OnDamaged_Implementation(float DamageAmount);
};