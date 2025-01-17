// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	void AddDrivingForce(float ForceMagnitude);
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent * MassAxleConstraint = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent * AxleWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * Wheel = nullptr;
		//UPrimitiveComponent* Wheel = nullptr;

	float TotalForceMagnitudeThisFrame = 0;

	void SetupConstrain();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//
	void ApplyForce();
};
