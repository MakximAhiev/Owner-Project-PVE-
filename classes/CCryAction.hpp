#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CCryAction_hpp
#define CCryAction_hpp
#include "CActionGame.hpp"
#include "CItemSystem.hpp"
#include "CActorSystem.hpp"
#include "CGameStartup.hpp"
#include "../struct/IGameFrameworkListener.hpp"
#include "../enum/EFRAMEWORKLISTENERPRIORITY.hpp"
#include "CGameRules.hpp"
#include "CEntitySystem.hpp"
#include "../math/Vec2.hpp"

class CCryAction
{
public:
	CItemSystem* GetItemSystem() {
		return v_spoof<CItemSystem*>(this, 0xD0);
	}
	CActorSystem* GetActorSystem() {
		return *reinterpret_cast<CActorSystem**>(this + 0x4E0);
	}
	CGameRules* GetGameRules() {
		return v_spoof<CGameRules*>(this, 0x448);
	}
	CEntitySystem* GetEntitySystem() {
		return *reinterpret_cast<CEntitySystem**>(this + 0x30);
	}
	int GetClientActorId() {
		auto pActionGame = this->GetActionGame();
		if (pActionGame != nullptr) {
			auto pGameClientNub = pActionGame->GetGameClientNub();
			if (pGameClientNub != nullptr) {
				auto pGameClientiChannel = pGameClientNub->GetGameClientChannel();
				if (pGameClientiChannel != nullptr) {
					return static_cast<int>(pGameClientiChannel->GetPlayerId());
				}
			}
		}
	}
	void RegisterListener(
		IGameFrameworkListener* pGameFrameworkListener,
		const char* name,
		EFRAMEWORKLISTENERPRIORITY eFrameworkListenerPriority)
	{
		v_spoof<void>(this, 0x360, pGameFrameworkListener, name, eFrameworkListenerPriority);
	}
	void UnregisterListener(IGameFrameworkListener* pGameFrameworkListener) {
		v_spoof<void>(this, 0x368, pGameFrameworkListener);
	}
	const char* GetLevelName() {
		return v_spoof<const char*>(this, 0x2F8);
	}
private:
	CActionGame* GetActionGame() {
		return *reinterpret_cast<CActionGame**>(this + 0x50);
	}
};
#endif // !CCryAction_hpp
