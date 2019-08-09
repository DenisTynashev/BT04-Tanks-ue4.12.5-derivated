// Battle Tank Game ver 1.0

#include "BattleTank.h"
#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

// Sets default values for this component's properties

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<class ASprungWheel*>ResultArray;
	TArray<USceneComponent*> Children;
	//UE_LOG(LogTemp, Warning, TEXT("this: %s"), *this->GetName());
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();	
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

/*
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//DriveTrack(); ??????
	//ApplySidewaysForce();
	//CurrentThrottle = 0;
}*/


/*void  UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}*/

/*
void UTankTrack::ApplySidewaysForce()
{
	// Calculate the sleepage speed
	FVector ForwardVector = GetComponentVelocity();
	FVector RightVector = GetOwner()->GetActorRightVector();
	float SleepageSpeed = FVector::DotProduct(ForwardVector, RightVector);
	//float SleepageSpeed = GetComponentVelocity().Size()*cos;
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = (-SleepageSpeed / DeltaTime)*GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}*/

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);	
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel: Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
