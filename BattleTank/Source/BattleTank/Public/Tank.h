// Battle Tank Game ver 1.0

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTankDelegate, FString, TankName);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Return CurrentHealth as percentage  of starting 
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnTankDied;


private:
	// Sets default values for this pawn's properties
	ATank();	

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


};
