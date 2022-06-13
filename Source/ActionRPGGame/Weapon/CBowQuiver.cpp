#include "Weapon/CBowQuiver.h"
#include "Components/InstancedStaticMeshComponent.h"

ACBowQuiver::ACBowQuiver()
{
	// PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	QuiverStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("QuiverStaticMesh");
	QuiverStaticMesh->SetupAttachment(Root);
	// StaticMesh'/Game/Weapons/Meshes/HuntingQuiver.HuntingQuiver'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> quiverStaticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/HuntingQuiver.HuntingQuiver'"));
	if(quiverStaticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = quiverStaticMeshAsset.Object;
		QuiverStaticMesh->SetStaticMesh(staticMesh);
		QuiverStaticMesh->SetCollisionProfileName("NoCollision");
	}
	
	ArrowInstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ArrowInstancedStaticMesh");
	ArrowInstancedStaticMesh->SetupAttachment(QuiverStaticMesh);
	ArrowInstancedStaticMesh->SetCollisionProfileName("NoCollision");

	// StaticMesh 초기화
	// StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> arrowStaticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'"));
	if(arrowStaticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = arrowStaticMeshAsset.Object;
		ArrowInstancedStaticMesh->SetStaticMesh(staticMesh);
	}
}

void ACBowQuiver::BeginPlay()
{
	Super::BeginPlay();

	// QuiverStaticMesh의 소켓의 위치을 가져와 Arrow Instance를 만든다.
	TArray<FName> quiverSocketNames = QuiverStaticMesh->GetAllSocketNames();
	for(FName socketName : quiverSocketNames)
	{
		FTransform transform = QuiverStaticMesh->GetSocketTransform(socketName);
		ArrowInstancedStaticMesh->AddInstance(transform, true);
	}
}


