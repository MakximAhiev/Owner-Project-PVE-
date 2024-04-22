#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef Visual_hpp
#define Visual_hpp
#include "../classes/CGameStartup.hpp"
#include "../imports/imports.hpp"
#include "../enum/EKey.hpp"
float red[4] = { 1.f, 0.f, 0.f, 1.f };
float yellow[4] = { 0.8f, 1.f, 0.15f, 1.f };

Vec3 GetPlayerPos(CEntity* pEntit)
{
	Vec3 vOffset = Vec3();
	Matrix34 pWorld = pEntit->GetWorldTM();
	vOffset = pWorld.GetTranslation();
	return vOffset;
}
class Visual
	: public IGameFrameworkListener
{
	Vec3 PlayerPos(CEntity* pEntit)
	{
		Vec3 vOffset = Vec3();
		Matrix34 pWorld = pEntit->GetWorldTM();
		vOffset = pWorld.GetTranslation();
		return vOffset;
	}
	bool IsEnemyTeam(CActor* mActor, CActor* pActor)
	{
		
		return (mActor != pActor) && (mActor->GetTeamId() > 0) && (mActor->GetTeamId() != pActor->GetTeamId());
		
	}

	bool IsFriendlyTeam(CActor* mActor, CActor* pActor)
	{
		
		return (mActor != pActor) && (mActor->GetTeamId() > 0) && (mActor->GetTeamId() == pActor->GetTeamId());
		
	}
	float pDistance(Vec3 m_Position, Vec3 e_Position) {
		
		return psqrt((((m_Position.x) - e_Position.x) * ((m_Position.x) - e_Position.x)) +
			(((m_Position.y) - e_Position.y) * ((m_Position.y) - e_Position.y)) +
			(((m_Position.z) - e_Position.z) * ((m_Position.z) - e_Position.z)));
		
	}
public:
	void OnPreRender() {
		
		auto pEnv = CGameStartup::sm_game_startup();														if (!pEnv) return;
		auto pRenderer = pEnv->GetRenderer();																if (!pRenderer) return;
		auto pGame = pEnv->GetGame();																		if (!pGame) return;
		auto pCryAction = pGame->GetCryAction();															if (!pCryAction) return;
		auto pEntitySystem = pEnv->GetEntitySystem();														if (!pEntitySystem) return;
		auto pEntityIterator = pEntitySystem->GetEntityIterator();											if (!pEntityIterator) return;
		auto pGameRules = pCryAction->GetGameRules();														if (!pGameRules) return;
		auto pProxyEntity = pGameRules->GetEntity();														if (!pProxyEntity) return;
		auto pScript = pProxyEntity->GetScriptProxy();														if (!pScript) return;
		auto mActor = pCryAction->GetActorSystem()->GetActor(pCryAction->GetClientActorId());				if (!mActor) return;
		auto pGameObject = mActor->GetGameObject();
		
		this->Watermark(pRenderer, pCryAction, pScript);
		this->hueta(pEntityIterator, pCryAction, mActor, pRenderer, pGameObject, pGameRules);
		
		/*if (!(pScript->IsInState(XORSTR("PreRound")) || pScript->IsInState(XORSTR("PostRound"))
			|| pScript->IsInState(XORSTR("PostGame")))) {
			if (0 != m_strcmp(pScript->GetState(), XORSTR("PostGame"))) {
				this->ESP(pEntityIterator, pCryAction, pScript, mActor);
			}
		}*/
	}
private:
	void Watermark(CRenderer* pRenderer, CCryAction* pCryAction, CScriptProxy* pScript) {
		
		pRenderer->DrawTextAw(15, 15, 1.5, red, 0, XORSTR("[#] owner pve | version: 1.0 | created: 26.03.2024"));
		pRenderer->DrawTextAw(15, 30, 1.5, red, 0, pCryAction->GetLevelName());
		pRenderer->DrawTextAw(15, 45, 1.5, red, 0, pScript->GetState());
		
	}
	void hueta(CEntityIterator* pEntityIterator, CCryAction* pCryAction, CActor* mActor, CRenderer* pRenderer, CGameObject* pGameObject, CGameRules* pGameRules) {
		
		while (CEntity* pEntity = pEntityIterator->Next()) {
			if (CActor* pActor = pCryAction->GetActorSystem()->GetActor(pEntity->GetEntityId())) {
				
				if (!IsEnemyTeam(mActor, pActor)) continue;
				auto name = pEntity->GetName();
				auto className = pEntity->GetEntityClass()->GetName();
				auto animation = pActor->GetAnimationGraphState()->GetCurrentStateName();
				auto pItemSystem = pCryAction->GetItemSystem(); if (!pItemSystem) continue;
				auto pItemProxy = pItemSystem->GetItem(pActor->GetInventory()->GetCurrentItemId()); if (!pItemProxy) continue;
				auto ItemName = pItemProxy->GetEntity()->GetName();
				
				/*auto material = pEntity->GetMaterial()->GetName();*/
				//auto material = pGameRules->GetHitMaterialName(75);
				Vec3 screen;
				
				if (f_get_key_state(F11)) {
					if (pRenderer->WorldToScreen(PlayerPos(pEntity), screen)) {
	
						float x = screen.x;
						float y = screen.y;

						pRenderer->DrawTextAw(x + 15, y + 15, 1.5, red, 0, name);
						pRenderer->DrawTextAw(x, y + 30, 1.5, yellow, 0, animation);
						pRenderer->DrawTextAw(x, y + 45, 1.5, yellow, 0, ItemName);
						pRenderer->DrawTextAw(x, y, 1.5, yellow, 0, className);
	
					}
				}
			}
		}
		
	}
private:
	//float RColor = 7;
	//float GColor = 242;
	//float BColor = 249;
};
#endif // !Visual_hpp
