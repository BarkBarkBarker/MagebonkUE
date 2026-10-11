#include "MegaBonkPlayerController.h"

AMegaBonkPlayerController::AMegaBonkPlayerController()
{
    // “ик контроллеру не нужен Ч вс€ логика событийна€ (ввод, пауза).
    PrimaryActorTick.bCanEverTick = false;
}

void AMegaBonkPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("[PlayerController] BeginPlay"));
}

void AMegaBonkPlayerController::ToggleGamePause()
{
    bIsGamePaused = !bIsGamePaused;

    // SetPause Ч встроенный метод APlayerController.
    // ќстанавливает тик всех актЄров, но Ќ≈ тик UI и не ввод.
    SetPause(bIsGamePaused);

    UE_LOG(LogTemp, Log, TEXT("[PlayerController] Pause = %d"), bIsGamePaused ? 1 : 0);

    OnGamePausedChanged(bIsGamePaused);
}