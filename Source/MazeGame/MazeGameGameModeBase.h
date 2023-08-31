// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeGameInstance.h"
#include "MazeGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGAME_API AMazeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	void NextLevel();
public:
	void LevelCompleted();
	void GameCompleted(bool PlayerWon);
	void IncreaseScore(float ScoreToAdd);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerStats")
	float PlayerScore;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMazeGameInstance* GameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;
	UPROPERTY()
	UUserWidget* LevelCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultHUDWidget;
	UPROPERTY()
	UUserWidget* HUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UPROPERTY()
	UUserWidget* GameCompleteWidget;

	FTimerHandle LevelSwapTimer;
};
