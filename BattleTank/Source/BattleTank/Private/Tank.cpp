// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "Tank.h"
#include "Classes/Components/AudioComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;	
	/*auto TempRootComponent = GetRootComponent();
	if (!ensure(TempRootComponent)) {return;}
	UE_LOG(LogTemp, Warning, TEXT("RootComponents Name: %s"), *(TempRootComponent->GetName()));
	SpawnPoint = NewObject<USpawnPoint>(this);
	SpawnPoint->RegisterComponent();
	SpawnPoint->AttachToComponent(TempRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	if (!ensure(SpawnPoint)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("New component name: %s"), *(SpawnPoint->GetName()));
	auto Parent = SpawnPoint->GetAttachParent();
	UE_LOG(LogTemp, Warning, TEXT("Parent name: %s"), *(Parent->GetName()));*/
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	Super::TakeDamage(DamagePoints, DamageEvent, EventInstigator,DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth: %d"), CurrentHealth);
	int32 DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Damage: %f, DamageToApply: %i, CurrentHealth: %i"), Damage, DamageToApply, CurrentHealth);
	if (CurrentHealth <= 0)
	{
		auto TankName = GetName();
		OnTankDied.Broadcast(TankName);		
		UE_LOG(LogTemp, Warning, TEXT("Broadcasting the Tank %s death"), *TankName)
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return ((float)CurrentHealth/(float)StartingHealth);
}