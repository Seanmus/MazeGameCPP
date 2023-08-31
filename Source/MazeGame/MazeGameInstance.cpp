// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMazeGameInstance::LoadNextLevel()
{
	if (CurrentLevel >= Worlds.Num())
	{
		return;
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Worlds[CurrentLevel++], true);
}

bool UMazeGameInstance::IsPlayerOnFinalLevel() const
{
	return(CurrentLevel == Worlds.Num());
}

//Get the world.
//From the world get the first player controller. APlayerController*
//From that player controller set the input mode.(Call set input mode on controller with one of two structs:
//	-const FInputModeGameOnly InputMode;
//	-const FInputModeUIOnly InputMode;
//	4) Controller->bShowMouseCursor(UI mode true, Game mode false)
void UMazeGameInstance::SetInputMode(bool GameOnly) const
{
	UWorld* World = GetWorld();
	APlayerController* const PlayerController = World->GetFirstPlayerController();
	if (GameOnly)
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	else
	{
		const FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	PlayerController->bShowMouseCursor = !GameOnly;
}

void UMazeGameInstance::LoadFirstLevel()
{
	CurrentLevel = 0;
	SetInputMode(true);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Worlds[CurrentLevel++], true);
}
