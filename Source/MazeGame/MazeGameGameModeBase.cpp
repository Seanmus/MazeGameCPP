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
	if (DefaultPauseMenuWidget) {
		PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultPauseMenuWidget);
		if (PauseMenuWidget) {
			PauseMenuWidget->AddToViewport();
		}
	}
}

AMazeGameGameModeBase::AMazeGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructor on game mode called."));
}

void AMazeGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GameOver) {
		time -= DeltaTime;
		if (time <= 10 && !timerWarningEffectTriggered) 
		{
			UGameplayStatics::PlaySound2D(GetWorld(), TimerSoundEffect, 1, 1, 0);
			timerWarningEffectTriggered = true;
		}
		if (time <= 0) {
			time = 0;
			GameCompleted();
		}
	}
}


void AMazeGameGameModeBase::GameCompleted()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (HUDWidget) {
		HUDWidget->RemoveFromParent();
	}

	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
		}
	}
}

void AMazeGameGameModeBase::IncreaseScore(float ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Score : %f |"), PlayerScore);
	ScoreIncreased.Broadcast(PlayerScore);
}
