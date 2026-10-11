#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MegaBonkPlayerController.generated.h"

/**
 * «Мозг и руки» игрока. Живёт дольше, чем Pawn:
 * смерть персонажа не уничтожает контроллер, поэтому именно он
 * показывает Game Over и обрабатывает паузу.
 */
UCLASS(Blueprintable)
class MEGABONKLEARN_API AMegaBonkPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMegaBonkPlayerController();

    /** Игра на паузе (например, открыт экран выбора апгрейда). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGamePaused = false;

    /** Поставить/снять игру с паузы. */
    UFUNCTION(BlueprintCallable, Category = "Game")
    void ToggleGamePause();

    /** Хук для BP: показать/скрыть UI паузы. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Game")
    void OnGamePausedChanged(bool bPaused);

protected:
    virtual void BeginPlay() override;
};