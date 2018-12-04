// Battle Tank Game ver 1.0

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();	
};
