// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MazeGameInstance.h"
#include "MazeGameGameModeBase.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter() {

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	PlayerSpawn = Cube->GetComponentLocation();

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	GameMode = CastChecked<AMazeGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
	}



	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) {
			if (InputMappingContext) {
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
			else {

			}
		}
	}

	if (Cube) {
		Cube->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		//const FVector CubeForce = FVector(ForwardForce, 0.0f, 0.0f);
		//Cube->AddForce(CubeForce, NAME_None, true);
		if (Cube->GetComponentLocation().Z < KillZ)
		{
			PlayerDied();
		}
		Cube->SetPhysicsLinearVelocity(Cube->GetPhysicsLinearVelocity() * 0.9f);
		
		//

	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) {
		if (MoveRightLeft) {
			EnhancedInputComponent->BindAction(MoveRightLeft, ETriggerEvent::Triggered, this,
				&APlayerCharacter::Move);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value) {
	const FVector2D MovementAxis = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Move called"));
	if (!bLevelEnded) {
		const FVector CubeForce = FVector(MovementAxis.X * SideForce, MovementAxis.Y * SideForce, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

void APlayerCharacter::PlayerDied()
{
	bLevelEnded = true;
	Cube->SetPhysicsLinearVelocity({ 0, 0, 0 });
	GetWorldTimerManager().SetTimer(PlayerDiedTimer, [this]() {GameMode->GameCompleted(false); }, 2.0f, false);
	//GetWorldTimerManager().SetTimer(PlayerDiedTimer,[this](bool bGameOver) {GameMode->GameCompleted(bGameOver); }, 2.0f, false);
	//GetWorldTimerManager().SetTimer(PlayerDiedTimer, this, &APlayerCharacter::GameOver, 2.0f);
	//GameMode->GameCompleted(false);
	//Cube->SetWorldLocationAndRotation(PlayerSpawn, FRotator(0, 0, 0));
	//Cube->SetWorldLocation(PlayerSpawn);
}



void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit) {
	//if (OtherActor && OtherActor->IsA(AObstacle::StaticClass())) {
	//	PlayerDied();
	//}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//if (OtherActor && OtherActor->IsA(AEndPoint::StaticClass())) {
	//	bLevelEnded = true;
	//	Cube->SetPhysicsLinearVelocity(Cube->GetPhysicsLinearVelocity() * 0.9f);
	//	GameMode->LevelCompleted();
	//}
}

void APlayerCharacter::GameOver()
{
	GameMode->GameCompleted(false);
}


