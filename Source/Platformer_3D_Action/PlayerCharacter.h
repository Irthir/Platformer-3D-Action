// @Ludus Académie Etudiant

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Platformer_GameInstance.h"
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
	UCapsuleComponent* m_CapsuleCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* m_CharacterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COMPONENTS", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* m_CharacterMovementComponent;
	
	//VARIABLES
	bool m_bCanTakeDamage = false;
	float m_fCameraFadeTime = 1.f;
	FTimerHandle RestartTimerHandle;

	//REFERENCES
	UPlatformer_GameInstance* p_GameInstance; //Référence au GameInstance.

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

	//Mouvements du joueur.
	void RotateYawInput(float AxisValue);
	void RotatePitchInput(float AxisValue);
	void JumpingStart();
	void JumpingStop();
	void MoveForwardBackward(float AxisValue);
	void MoveRightLeft(float AxisValue);

	//Gestion des dégâts
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	void LifeDown();
	bool IsAlive();

	//Gestion de la caméra
	void CameraFade();

	//Gestion de la redirection
	void OpenNextLevel();
};
