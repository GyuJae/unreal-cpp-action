#include "R1Actor.h"
#include "R1Object.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AR1Actor::AR1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOx"));
}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{


}

