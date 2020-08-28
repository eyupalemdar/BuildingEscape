// Copyrights AlemdarLabs 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// Door must rotate to 90 degree in Yaw axis.
	// So TargetYaw start with 90 axis and plus Door's Current Yaw value.
	// Because Door can be different positions on Map.
	TargetYaw += GetOwner()->GetActorRotation().Yaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Before Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor(0.f, TargetYaw, 0.f);

	// It is time independent so on a faster computer it will run faster, bad computing
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.02f);

	// Time dependant to Unreal Tick (DeltaTime)
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45);
	
	// Time dependant to Unreal Tick (DeltaTime)
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);

	GetOwner()->SetActorRotation(OpenDoor);

	UE_LOG(LogTemp, Warning, TEXT("After Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
}

