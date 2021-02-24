// @Ludus Académie Etudiant


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = m_CapsuleCollider;
	m_CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	m_CharacterMesh->SetupAttachment(RootComponent);
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(RootComponent);
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
	m_CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::RotateYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::RotatePitchInput);
}

void APlayerCharacter::RotateYawInput(float AxisValue)
/***********************************************************\
* BUT		: Tourner la caméra et le joueur selon l'axe Z.
* ENTREE	: La valeur à rajouter à l'axe Z.
* SORTIE	: La rotation en Z du joueur par cette valeur.
\***********************************************************/
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::RotatePitchInput(float AxisValue)
/***********************************************************\
* BUT		: Tourner la caméra et le joueur selon l'axe Y.
* ENTREE	: La valeur à rajouter à l'axe Y.
* SORTIE	: La rotation en Y du joueur par cette valeur.
\***********************************************************/
{
	AddControllerPitchInput(AxisValue);
}