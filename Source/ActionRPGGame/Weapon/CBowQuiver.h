// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBowQuiver.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACBowQuiver : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACBowQuiver();

protected:
	// BeginPlay
	virtual void BeginPlay() override;

public:	
	// Scene 컴포넌트, 루트 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UStaticMeshComponent* QuiverStaticMesh;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UInstancedStaticMeshComponent* ArrowInstancedStaticMesh; 
};
