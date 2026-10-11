#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MegaBonkGameMode.generated.h"

/**
 * Правила забега: длительность, сложность, условия победы и поражения,
 * какие классы создавать для игрока и контроллера.
 * Существует только на сервере и только пока загружен уровень.
 */
UCLASS(Blueprintable)
class MEGABONKLEARN_API AMegaBonkGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMegaBonkGameMode();

    /** Длительность забега в секундах. 15 минут = 900. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Run")
    float RunDurationSeconds = 900.0f;

    /** Сколько времени прошло с начала забега. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Run")
    float ElapsedRunTime = 0.0f;

    /** Сколько врагов убито за забег (для статистики и кривой сложности). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Run")
    int32 EnemiesKilled = 0;

    UFUNCTION(BlueprintCallable, Category = "Run")
    void RegisterEnemyKill();

    /** Забег провален. Вызывается, когда HP игрока дошло до нуля. */
    UFUNCTION(BlueprintCallable, Category = "Run")
    void EndRunAsDefeat();

    /** Забег пройден. Вызывается, когда таймер дошёл до RunDurationSeconds. */
    UFUNCTION(BlueprintCallable, Category = "Run")
    void EndRunAsVictory();

    /** Хук для Blueprint: что показать на экране (Game Over / Victory). */
    UFUNCTION(BlueprintImplementableEvent, Category = "Run")
    void OnRunEnded(bool bVictory);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    bool bRunActive = false;
    bool bRunEnded = false;

    void FinishRun(bool bVictory);
};