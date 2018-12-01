// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "TankTrack.h"

// Sets default values for this component's properties

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void  UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate the sleepage speed
	FVector ForwardVector = GetComponentVelocity().GetSafeNormal();
	FVector RightVector = GetOwner()->GetActorRightVector().GetSafeNormal();	
	float cos = FVector::DotProduct(ForwardVector, RightVector);
	float SleepageSpeed = GetComponentVelocity().Size()*cos;
	UE_LOG(LogTemp, Warning, TEXT("Cosinus: %f, SleepageSpeed: %f"), cos, SleepageSpeed);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}