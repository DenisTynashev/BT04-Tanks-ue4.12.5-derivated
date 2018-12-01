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
	FVector ForwardVector = GetComponentVelocity();
	FVector RightVector = GetOwner()->GetActorRightVector();	
	float SleepageSpeed = FVector::DotProduct(ForwardVector, RightVector);
	//float SleepageSpeed = GetComponentVelocity().Size()*cos;
	auto CorrectionAcceleration = (-SleepageSpeed / DeltaTime)*GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration)/2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}