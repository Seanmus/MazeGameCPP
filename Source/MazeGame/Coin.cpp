// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetSimulatePhysics(false);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Sphere;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	if (Sphere) {
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);
	}
	GameMode = CastChecked<AMazeGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) {
		GameMode->IncreaseScore(Score);
		this->Destroy();
	}
}

