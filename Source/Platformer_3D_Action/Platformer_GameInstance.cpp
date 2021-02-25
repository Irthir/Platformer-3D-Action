// @Ludus Académie Etudiant


#include "Platformer_GameInstance.h"
#include "Math/UnrealMathUtility.h"

void UPlatformer_GameInstance::Init()
{
	m_Life = m_Max_Life;
	m_Score = 0;
}

void UPlatformer_GameInstance::ViePlus()
{
	m_Life++;
	m_Life = FMath::Clamp(m_Life, 0, m_Max_Life);
}

void UPlatformer_GameInstance::VieMoins()
{
	m_Life--;
	m_Life = FMath::Clamp(m_Life, 0, m_Max_Life);
}

void UPlatformer_GameInstance::ScorePlus()
{
	m_Score++;
}
