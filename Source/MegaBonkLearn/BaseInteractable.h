#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"   // ќЅя«ј“≈Ћ№Ќќ последним

UCLASS(Blueprintable)   // Blueprintable = от этого класса можно наследоватьс€ в BP
class MEGABONKLEARN_API ABaseInteractable : public AActor
{
    GENERATED_BODY()

public:
    ABaseInteractable();

    /** —тартовое здоровье. EditAnywhere Ч видно в Details; BlueprintReadWrite Ч читаетс€ и пишетс€ из BP. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    float CurrentHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    bool bIsDead = false;

    /** Ќанести урон. BlueprintCallable Ч можно вызвать из BP. */
    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void TakeDamage(float DamageAmount);

    /** ’ук дл€ BP: что сделать при смерти (VFX, звук, дроп). –еализаци€ “ќЋ№ ќ в Blueprint. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnDeath();

    /** ’ук с реализацией по умолчанию в C++, BP может переопределить. */
    UFUNCTION(BlueprintNativeEvent, Category = "Combat")
    void OnDamaged(float DamageAmount);

protected:
    virtual void BeginPlay() override;
    virtual void OnDamaged_Implementation(float DamageAmount);
};