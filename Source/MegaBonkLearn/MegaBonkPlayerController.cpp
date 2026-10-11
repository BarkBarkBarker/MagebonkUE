// ============================================================
//  MegaBonkPlayerController.cpp — ДОПОЛНЕННАЯ ВЕРСИЯ
//  Кодировка: UTF-8 with BOM
// ============================================================
#include "MegaBonkPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AMegaBonkPlayerController::AMegaBonkPlayerController()
{
    // All controller logic is event driven (input, pause). No tick needed.
    PrimaryActorTick.bCanEverTick = false;
}

void AMegaBonkPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ---- Register the Enhanced Input mapping context ----
    // This is what BP_ThirdPersonPlayerController did in the template.
    // The subsystem lives on the LocalPlayer, not on the controller.
    if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, DefaultMappingPriority);

                UE_LOG(LogTemp, Log, TEXT("[PlayerController] Added mapping context: %s (priority %d)"),
                    *DefaultMappingContext->GetName(), DefaultMappingPriority);
            }
            else
            {
                UE_LOG(LogTemp, Error,
                    TEXT("[PlayerController] DefaultMappingContext is NULL - input will not work. ")
                    TEXT("Set it in BP_MegaBonkPlayerController Class Defaults."));
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[PlayerController] BeginPlay"));
}

void AMegaBonkPlayerController::ToggleGamePause()
{
    bIsGamePaused = !bIsGamePaused;

    // Built-in APlayerController method. Stops actor ticking but keeps
    // input and UI alive - otherwise you could not unpause.
    SetPause(bIsGamePaused);

    UE_LOG(LogTemp, Log, TEXT("[PlayerController] Pause = %d"), bIsGamePaused ? 1 : 0);

    OnGamePausedChanged(bIsGamePaused);
}
