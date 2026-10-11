// ============================================================
//  BaseInteractable.h — ИСПРАВЛЕННАЯ ВЕРСИЯ
//  Замена: скрытие AActor::TakeDamage (warnings C4263/C4264)
//
//  Кодировка: сохранить как UTF-8 with BOM
//  Комментарии намеренно на английском — см. правило в devlog
// ============================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

class AController;

/**
 * Base class for anything that has health and can die.
 * Demonstrates the hybrid pattern: logic in C++, presentation hooks in Blueprint.
 */
UCLASS(Blueprintable)
class MEGABONKLEARN_API ABaseInteractable : public AActor
{
    GENERATED_BODY()

public:
    ABaseInteractable();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    float CurrentHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    bool bIsDead = false;

    /**
     * Controller that dealt the last damage.
     * Needed in M4 to award XP to whoever got the kill.
     * Kept as a property (not an event parameter) so existing Blueprint
     * event signatures stay valid.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<AController> LastDamageInstigator;

    /**
     * Override of the ENGINE damage pipeline. The signature MUST match
     * AActor::TakeDamage exactly, otherwise we hide the base function and
     * UGameplayStatics::ApplyDamage() would call the empty base version.
     *
     * Call it from Blueprint via the "Apply Damage" node, NOT directly.
     */
    virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser) override;

    /** Blueprint hook: damage VFX / sound / floating numbers. */
    UFUNCTION(BlueprintNativeEvent, Category = "Combat")
    void OnDamaged(float ActualDamage);

    /** Blueprint hook: death VFX / sound / loot. Implemented only in Blueprint. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
    void OnDeath();

protected:
    virtual void BeginPlay() override;
    virtual void OnDamaged_Implementation(float ActualDamage);
};
