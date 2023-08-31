// Copyright Epic Games, Inc. All Rights Reserved.


#include "MazeGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

void AMazeGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = CastChecked<UMazeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!DefaultHUDWidget) {

	}
	else {
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultHUDWidget);
		if (HUDWidget) {
			HUDWidget->AddToViewport();
		}
	}
}

void AMazeGameGameModeBase::NextLevel()
{
	if (GameInstance->IsPlayerOnFinalLevel()) {
		if (LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromViewport();
		}

		GameCompleted(true);
	}
	else {
		GameInstance->LoadNextLevel();
	}
}

void AMazeGameGameModeBase::LevelCompleted()
{
	if (DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		if (LevelCompleteWidget) {
			LevelCompleteWidget->AddToViewport();
		}
	}
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &AMazeGameGameModeBase::NextLevel, 2.0f);
}

void AMazeGameGameModeBase::GameCompleted(bool PlayerWon)
{
	GameInstance->SetInputMode(false);
	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
		}
		UTextBlock* LostOrComplete = Cast<UTextBlock>(GameCompleteWidget->GetWidgetFromName(FName("LostOrComplete")));
		const FText EndStateMessage = PlayerWon ? FText::FromString("You Won!") : FText::FromString("You Lost!");
	}
	else {

	}
}

void AMazeGameGameModeBase::IncreaseScore(float ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}
