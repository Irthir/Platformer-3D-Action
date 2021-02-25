// @Ludus Académie Etudiant

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Platformer_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_3D_ACTION_API UPlatformer_GameInstance : public UGameInstance
{
	GENERATED_BODY()
private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LIFE", meta = (AllowPrivateAccess = "true"))
	int m_Max_Life = 3;
public :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LIFE")
	int m_Life = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SCORE")
	int m_Score = 0;

	UFUNCTION(BlueprintCallable, Category="INITIALISATION")
	void Init();
	UFUNCTION(BlueprintCallable, Category = "LIFE")
	void ViePlus();
	UFUNCTION(BlueprintCallable, Category = "LIFE")
	void VieMoins();
	UFUNCTION(BlueprintCallable, Category = "SCORE")
	void ScorePlus();
};
