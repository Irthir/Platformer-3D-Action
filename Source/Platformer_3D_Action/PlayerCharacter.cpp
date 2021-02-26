// @Ludus Académie Etudiant


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*m_CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = m_CapsuleCollider;
	m_CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	m_CharacterMesh->SetupAttachment(RootComponent);*/

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(RootComponent);
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
	//m_CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));


	static ConstructorHelpers::FClassFinder<UUserWidget> LevelsWidget(TEXT("/Game/Blueprints/Widgets/WBP_IU_Levels"));
	if (LevelsWidget.Class)
	{
		LevelsWidgetBPReference = LevelsWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseWidget(TEXT("/Game/Blueprints/Widgets/WBP_IU_Pause"));
	if (PauseWidget.Class)
	{
		PauseWidgetBPReference = PauseWidget.Class;
	}

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initialisation
	m_bCanTakeDamage = true;
	p_GameInstance = Cast<UPlatformer_GameInstance>(GetGameInstance());
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::TakeDamage);
	CreateUI(LevelsWidgetBPReference);
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpingStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpingStop);
	PlayerInputComponent->BindAxis("Move_Forward/Backward", this, &APlayerCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("Move_Right/Left", this, &APlayerCharacter::MoveRightLeft);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::Pause);
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

void APlayerCharacter::JumpingStart()
/***********************************************************\
* BUT		: Faire sauter le personnage.
* ENTREE	: N/A
* SORTIE	: Le saut du personnage.
\***********************************************************/
{
	Jump();
}

void APlayerCharacter::JumpingStop()
/***********************************************************\
* BUT		: Faire cesser le saut du personnage.
* ENTREE	: N/A
* SORTIE	: L'arrêt du saut du personnage.
\***********************************************************/
{
	StopJumping();
}

void APlayerCharacter::MoveForwardBackward(float AxisValue)
/***********************************************************\
* BUT		: Faire avancer et reculer le personnage.
* ENTREE	: La valeur à rajouter à l'axe X.
* SORTIE	: Le déplacement en X du joueur par cette valeur.
\***********************************************************/
{
	FRotator CharacterDirection = GetControlRotation();
	FVector WorldDirection = UKismetMathLibrary::GetForwardVector(CharacterDirection);
	AddMovementInput(WorldDirection, AxisValue);
}

void APlayerCharacter::MoveRightLeft(float AxisValue)
/***********************************************************\
* BUT		: Faire avancer et reculer le personnage.
* ENTREE	: La valeur à rajouter à l'axe Y.
* SORTIE	: Le déplacement en Y du joueur par cette valeur.
\***********************************************************/
{
	FRotator CharacterDirection = GetControlRotation();
	FVector WorldDirection = UKismetMathLibrary::GetRightVector(CharacterDirection);
	AddMovementInput(WorldDirection, AxisValue);
}

void APlayerCharacter::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
/***********************************************************\
* BUT		: Gérer la gestion de dégâts.
* ENTREE	: Les paramètres de l'évènement OnTakeAnyDamage.
* SORTIE	: La vie réduite et le niveau qui recommence.
\***********************************************************/
{
	if (m_bCanTakeDamage) //Pour éviter un double appel de cette méthode.
	{
		m_bCanTakeDamage = false;
		LifeDown();
		CameraFade();
		GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &APlayerCharacter::OpenNextLevel, m_fCameraFadeTime, false);
	}
}

void APlayerCharacter::LifeDown()
/***********************************************************\
* BUT		: Réduire la vie du joueur.
* ENTREE	: La référence au gameinstance portant la vie.
* SORTIE	: La vie réduite.
\***********************************************************/
{
	if (p_GameInstance)
	{
		p_GameInstance->VieMoins();
	}
}

bool APlayerCharacter::IsAlive()
/***********************************************************\
* BUT		: Vérifier si le joueur possède encore des vies.
* ENTREE	: La référence au GameInstance stockant la vie.
* SORTIE	: Vrai si il reste de la vie, Faux sinon.
\***********************************************************/
{
	return p_GameInstance->m_Life>0;
}

void APlayerCharacter::CameraFade()
/***********************************************************\
* BUT		: Réaliser un fondu sur la caméra.
* ENTREE	: La référence au camera manager.
* SORTIE	: Un fondu rendant l'écran noir.
\***********************************************************/
{
	APlayerCameraManager* p_Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);
	p_Camera->StartCameraFade(0,1,m_fCameraFadeTime,FLinearColor(0.f,0.f,0.f,1.f),false,true);
}

void APlayerCharacter::OpenNextLevel()
/***********************************************************\
* BUT		: Charger le niveau actuel ou le niveau de fin de jeu.
* ENTREE	: La condition si oui ou non le joueur a perdu.
* SORTIE	: Le nouveau niveau chargé.
\***********************************************************/
{
	GetWorld()->GetTimerManager().ClearTimer(RestartTimerHandle);
	if (IsAlive())
	{
		UGameplayStatics::OpenLevel(GetWorld(),FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName("Fin"));
	}
}

void APlayerCharacter::CreateUI(TSubclassOf<UUserWidget> WidgetBPReference)
/***********************************************************\
* BUT		: Créer et afficher l'UI en jeu.
* ENTREE	: La référence au blueprint de l'UI.
* SORTIE	: L'UI affiché.
\***********************************************************/
{
	if (WidgetBPReference)
	{
		UUserWidget* UI = CreateWidget<UUserWidget>(p_GameInstance, WidgetBPReference, FName("UI"));
		UI->AddToViewport();
	}
}


void APlayerCharacter::Pause()
/***********************************************************\
* BUT		: Enclencher la Pause.
* ENTREE	: L'action de Pause.
* SORTIE	: La pause et l'UI de pause affiché.
\***********************************************************/
{
	if (PauseWidgetBPReference)
	{
		//Affichage de l'UI de Pause.
		UUserWidget* PauseUI = CreateWidget<UUserWidget>(p_GameInstance, PauseWidgetBPReference, FName("Pause UI"));
		PauseUI->AddToViewport();

		//Changement du mode d'input pour un accès à la souris pendant la pause.
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (PlayerController && PauseUI)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(PauseUI->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
