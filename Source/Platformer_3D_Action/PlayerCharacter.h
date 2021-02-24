// @Ludus Académie Etudiant

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

//Prédéfinitions des classes dans le .h
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PLATFORMER_3D_ACTION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* CharacterMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
