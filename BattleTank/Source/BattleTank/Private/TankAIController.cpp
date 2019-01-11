// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!PossesedTank) { return; }
		PossesedTank->OnTankDied.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

//Delegate Method
void ATankAIController::OnPossesedTankDeath(FString TankName)
{
	ATank	* PossesedTank = Cast<ATank>(GetPawn());
	if (!PossesedTank) { return; }
	PossesedTank->DetachFromControllerPendingDestroy();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	//If there is no player controlled tank
	if (!(PlayerTank && ControlledTank)) { return; }
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
	// Aim towards the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());	
	//Fire at Player Tank
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{ 
		TankAimingComponent->Fire(); // TODO limit firing rate
	}
	
}
