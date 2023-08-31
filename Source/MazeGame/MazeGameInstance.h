// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MazeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGAME_API UMazeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray < TSoftObjectPtr<UWorld>> Worlds;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentLevel = 0;

public:
	void LoadNextLevel();
	bool IsPlayerOnFinalLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
	void SetInputMode(bool GameOnly) const;
	UFUNCTION(BlueprintCallable, Category = "Game Levels")
	void LoadFirstLevel();
};
