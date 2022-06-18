#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_AbilitySlot.generated.h"

// 전방 선언
class UTextBlock;
enum class ESlotType : uint8;
class ACAbility;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_AbilitySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ProgressBar Image Change
	UFUNCTION()
	void ChangedProgressBarImage(UTexture2D* InTexture2D) const;

	// Set ProgressBar Visibility Hidden
	UFUNCTION()
	void HiddenProgressBar() const;

	// Set ProgressBar Visibility Visible
	UFUNCTION()
	void VisibleProgressBar() const;

	UTextBlock* GetRemainAbilityText() const { return RemainAbilityTimeText; }

	void SetAvailable(bool InIsAvailable);
	void SetAbility(ACAbility* InAbility);

	ACAbility* GetAbility() { return Ability; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	class UImage* Frame;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RemainAbilityTimeText;

private:
	// 초기 상태로 Reset
	void Reset();

	bool IsAvailable;
	
	float Value;
	float MaxValue;

	bool IsTimer;
	int32 AvailableAbilityTime;
	int32 RemainAbilityTime;

	UPROPERTY()
	ACAbility* Ability;
};
