//#pragma once
//#ifndef Multihit_hpp
//#define Multihit_hpp
//#include "../classes/CGameStartup.hpp"
//#include "../imports/imports.hpp"
//
//class Weapon
//	: public IGameFrameworkListener 
//{
//public:
//	void OnPreRender() {
//		auto pEnv = CGameStartup::sm_game_startup();													if (!pEnv) return;
//		auto pGame = pEnv->GetGame();																	if (!pGame) return;
//		auto pEntitySystem = pEnv->GetEntitySystem();													if (!pEntitySystem) return;
//		auto pEntityIterator = pEntitySystem->GetEntityIterator();										if (!pEntityIterator) return;
//		auto pCryAction = pGame->GetCryAction();														if (!pCryAction) return;
//		auto pActorSystem = pCryAction->GetActorSystem();												if (!pActorSystem) return;
//		auto pActor = pActorSystem->GetActor(pCryAction->GetClientActorId());							if (!pActor) return;
//		auto pInventory = pActor->GetInventory();														if (!pInventory) return;
//		auto pItemSystem = pCryAction->GetItemSystem();													if (!pItemSystem) return;
//		auto pItemProxy = pItemSystem->GetItem(pInventory->GetCurrentItemId());							if (!pItemProxy) return;
//		auto pWeaponExt = pItemProxy->GetWeaponExt();													if (!pWeaponExt) return;
//		auto pParameters = pWeaponExt->GetParameters();													if (!pParameters) return;
//		this->AntiRecoil(pParameters);
//		this->AntiSpread(pParameters);
//		this->FastChange(pParameters);
//		this->FastKnife(pParameters);
//		this->UseDeffibriliator(pWeaponExt, pEntityIterator, pCryAction);
//	}
//private:
//	void AntiRecoil(CWeaponParameters* pParameters) {
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclAtt, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclDec, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclDecDelay , 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclMax, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclRnd, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_RclSmth, 0.f);
//	}
//	void AntiSpread(CWeaponParameters* pParameters) {
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdAtt, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdDec, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdDecDelay, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdInverted, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdMax, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SprdMin, 0.f);
//	}
//	void FastChange(CWeaponParameters* pParameters) {
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SelectDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SelectDurationBuff, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_DeselectDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_DeselectDurationBuff, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_InSlotSelectDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_InSlotDeselectDuration, 0.f);
//	}
//	void FastKnife(CWeaponParameters* pParameters) {
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_MeleeDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_MeleeDurationBuff, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_MeleeOutDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SecondaryMeleeDuration, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SecondaryMeleeDurationBuff, 0.f);
//		pParameters->GetStats()->SetValue(EGameStatType::eGS_SecondaryMeleeOutDuration, 0.f);
//	}
//	void UseDeffibriliator(CWeaponExt* pWeaponExt, CEntityIterator* pEntityIterator, CCryAction* pCryAction) {
//		while (CEntity* pEntity = pEntityIterator->Next()) {
//			if (CActor* pActor = pCryAction->GetActorSystem()->GetActor(pEntity->GetEntityId())) {
//				/*if (f_get_async_key_state(VK_F1) & 1) {
//					for (int i = 0; i != 10; i++) {
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 0, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 1, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 2, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 3, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 0, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 1, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 2, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), pActor->GetEntityId(), 3, false);
//
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), 0xBAD1D01, 0, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), 0xBAD1D01, 1, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), 0xBAD1D01, 2, false);
//						pWeaponExt->UseDefibrillator(pActor->GetEntityId(), 0xBAD1D01, 3, false);
//					}
//				}*/
//			}
//		}
//	}
//	/*void Sway(CWeaponParameters* pWeaponParameters) {
//		pWeaponParameters->m_swayCurr = { 0,0 };
//	}*/
//};
//#endif // !Mulltihit_hpp
