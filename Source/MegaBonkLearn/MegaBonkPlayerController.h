// ============================================================
//  MegaBonkPlayerController.h — ДОПОЛНЕННАЯ ВЕРСИЯ
//  Добавлено: регистрация Input Mapping Context.
//
//  ЗАЧЕМ: в шаблоне 5.8 этим занимается BP_ThirdPersonPlayerController
//  (проверено разбором бинарника: там есть AddMappingContext,
//  IMC_Default, IMC_MouseLook, EnhancedInputLocalPlayerSubsystem).
//  Заменив его своим контроллером, мы теряем ввод - персонаж
//  перестанет реагировать на WASD. Поэтому делаем то же самое в C++.
//
//  Кодировка: UTF-8 with BOM
// ============================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MegaBonkPlayerController.generated.h"

// Forward declaration only. That is enough for a TObjectPtr member,
// and it lets us keep "EnhancedInput" as a PRIVATE module dependency.
class UInputMappingContext;

/**
 * Player brain and hands. Outlives the Pawn: character death does not
 * destroy the controller, which is why Game Over and pause live here.
 */
UCLASS(Blueprintable)
class MEGABONKLEARN_API AMegaBonkPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMegaBonkPlayerController();

    // ------------------------------------------------ Input

    /**
     * Mapping context registered on BeginPlay.
     * Set it to IMC_Default in BP_MegaBonkPlayerController Class Defaults.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    /** Higher priority contexts win when bindings conflict. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    int32 DefaultMappingPriority = 0;

    // ------------------------------------------------ Game state

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGamePaused = false;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void ToggleGamePause();

    /** Blueprint hook: show/hide the pause UI. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Game")
    void OnGamePausedChanged(bool bPaused);

protected:
    virtual void BeginPlay() override;
};
