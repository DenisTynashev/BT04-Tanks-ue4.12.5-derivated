// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
		UE_LOG(LogTemp, Warning, TEXT("Tank died"))
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}