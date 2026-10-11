#include "MegaBonkGameMode.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AMegaBonkGameMode::AMegaBonkGameMode()
{
    // Здесь задаём, КТО создаётся при старте уровня.
    // Пока оставляем шаблонные классы — заменим в T-010, когда появится ABaseCharacter.

    // GameMode — единственный класс во фреймворке, которому тик ДЕЙСТВИТЕЛЬНО нужен:
    // он один на уровень, и он ведёт таймер забега.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.0f;   // каждый кадр
}

void AMegaBonkGameMode::BeginPlay()
{
    Super::BeginPlay();   // ← обязательно, иначе BP Event BeginPlay не сработает

    bRunActive = true;
    ElapsedRunTime = 0.0f;

    UE_LOG(LogTemp, Log, TEXT("[GameMode] Run started. Duration = %.0f s"), RunDurationSeconds);
}

void AMegaBonkGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!bRunActive || bRunEnded) { return; }

    ElapsedRunTime += DeltaSeconds;

    if (ElapsedRunTime >= RunDurationSeconds)
    {
        EndRunAsVictory();
    }
}

void AMegaBonkGameMode::RegisterEnemyKill()
{
    EnemiesKilled++;
}

void AMegaBonkGameMode::EndRunAsDefeat()
{
    FinishRun(false);
}

void AMegaBonkGameMode::EndRunAsVictory()
{
    FinishRun(true);
}

void AMegaBonkGameMode::FinishRun(bool bVictory)
{
    if (bRunEnded) { return; }   // защита от двойного вызова

    bRunEnded = true;
    bRunActive = false;

    UE_LOG(LogTemp, Warning, TEXT("[GameMode] Run ENDED. Victory=%d | time=%.1fs | kills=%d"),
        bVictory ? 1 : 0, ElapsedRunTime, EnemiesKilled);

    OnRunEnded(bVictory);   // Blueprint покажет экран Game Over / Victory
}