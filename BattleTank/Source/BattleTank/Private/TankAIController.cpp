// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();	
	auto ControlledTank = GetPawn();
	//If there is no player controlled tank
	if (!ensure(PlayerTank && ControlledTank)) { return; }
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
