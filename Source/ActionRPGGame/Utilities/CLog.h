#pragma once

#include "CoreMinimal.h"

class ACTIONRPGGAME_API CLog
{
public:
	// Print 함수
	// int형
	static void Print(int32 InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	// float형
	static void Print(float InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	// FString형
	static void Print(const FString& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Blue);
	// FVector형
	static void Print(const FVector& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Blue);
	// FRoator형
	static void Print(const FRotator& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Blue);

public: // Log 함수
	
	// int형
	static void Log(int32 InValue); 
	// float형
	static void Log(float InValue);
	// FString형
	static void Log(const FString& InValue);
	// FVector형
	static void Log(const FVector& InValue);
	// FRotator형
	static void Log(const FRotator& InValue);
};
