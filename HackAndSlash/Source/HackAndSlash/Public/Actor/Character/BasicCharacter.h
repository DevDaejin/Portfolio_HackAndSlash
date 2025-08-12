#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PlayerCommand.h"
#include "BasicCharacter.generated.h"

class UAnimMontage;

UCLASS()
class HACKANDSLASH_API ABasicCharacter : public ACharacter, public IPlayerCommand
{
	GENERATED_BODY()
public:
	ABasicCharacter();

	virtual void Cmd_MoveAxis(const FVector2D& Axis) override;
	virtual void Cmd_Dash() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Move") float MoveSpeedScale = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Dash") float DashStrength = 1700.f;
	UPROPERTY(EditDefaultsOnly, Category = "Dash") float DashCooldown = 0.75f;
	UPROPERTY(EditDefaultsOnly, Category = "Dash") TObjectPtr<UAnimMontage> DashMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Dash") float DashPlayRate = 1.0f;

private:
	bool bCanDash = true;
	FTimerHandle Timer_ResetData;

	void DoDashImpulse();
	void ResetDash();
};
