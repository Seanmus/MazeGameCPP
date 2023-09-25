// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeGameInstance.h"
#include "MazeGameGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreIncreased, int32, Score);

UCLASS()
class MAZEGAME_API AMazeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	AMazeGameGameModeBase();
	virtual void Tick(float DeltaTime) override;
	void GameCompleted();
	void IncreaseScore(float ScoreToAdd);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameState")
	bool GameOver = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStats")
	float PlayerScore;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMazeGameInstance* GameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultHUDWidget;
	UPROPERTY()
	UUserWidget* HUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultPauseMenuWidget;
	UPROPERTY()
	UUserWidget* PauseMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UPROPERTY()
	UUserWidget* GameCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float time = 0;
	bool timerWarningEffectTriggered = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* TimerSoundEffect;


	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FScoreIncreased ScoreIncreased;

	FTimerHandle LevelSwapTimer;
};
