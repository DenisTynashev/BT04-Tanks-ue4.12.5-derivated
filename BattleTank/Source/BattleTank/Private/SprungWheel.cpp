// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxelConstraint"));
	SetRootComponent(MassAxleConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(MassAxleConstraint, FAttachmentTransformRules::KeepRelativeTransform); //Alternativ Wheel->SetupAttachment(Mass);	
	//Axle->SetupAttachment(MassAxelConstraint);
	
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	//AxleWheelConstraint->SetupAttachment(Axle);
	AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	

	Wheel=CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstrain();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("Tick: %f"), GetWorld()->GetTimeSeconds());

}

void ASprungWheel::SetupConstrain()
{
	auto pParentActor = GetAttachParentActor();
	if (!pParentActor) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No Parent!")); 
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("ParentActor Name: %s"), *(pParentActor->GetName()));
	if (pParentActor)
	{
		UPrimitiveComponent * BodyRoot = Cast<UPrimitiveComponent>(pParentActor->GetRootComponent());
		if (!BodyRoot) { return; }
		MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
		AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Null"))
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame); 
}
