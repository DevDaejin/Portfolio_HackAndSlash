#include "Actor/Character/BasicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

ABasicCharacter::ABasicCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
}

void ABasicCharacter::Cmd_MoveAxis(const FVector2D& Axis)
{
	if (!Controller) return;
	if (Axis.IsNearlyZero()) return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Axis.Y * MoveSpeedScale);
	AddMovementInput(Right, Axis.X * MoveSpeedScale);
}

void ABasicCharacter::Cmd_Dash()
{
	if (!bCanDash) return;
	bCanDash = false;

	if (DashMontage)
	{
		PlayAnimMontage(DashMontage, DashPlayRate);
	}

	DoDashImpulse();
	GetWorldTimerManager().SetTimer(Timer_ResetData, this, &ABasicCharacter::ResetDash, DashCooldown, false);
}

void ABasicCharacter::DoDashImpulse()
{
	const FVector InputDir = GetLastMovementInputVector().IsNearlyZero()
		? GetActorForwardVector()
		: GetLastMovementInputVector().GetSafeNormal();

	LaunchCharacter(InputDir * DashStrength, true, true);
}

void ABasicCharacter::ResetDash()
{
	bCanDash = true;
}
