// Battle Tank Game ver 1.0

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 100000; // Assume 40 tonne tank, and 1g accelleration

private:
	//Constructor
	UTankTrack();

	//
	TArray<class ASprungWheel*> GetWheels()const;
	//Tick	
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//void ApplySidewaysForce();

	//Begin Play
	virtual void BeginPlay() override;

	//
	void DriveTrack(float CurrentThrottle);

	//float CurrentThrottle = 0.f;

	/*UFUNCTION()
	void OnHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);*/
};
