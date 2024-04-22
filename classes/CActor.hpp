#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CActor_hpp
#define CActor_hpp
#include "CInventory.hpp"
#include "CCompoundCharacter.hpp"
#include "CActorAnimation.hpp"
#include "CEntity.hpp"
class CActor  
{
public:
	CInventory* GetInventory() {
		return v_spoof<CInventory*>(this, 0x1E8);
	}
	CCompoundCharacter* GetActorCC() {
		return *reinterpret_cast<CCompoundCharacter**>(this + 0xA68);
	}
	CActorAnimation* m_pActorAnimation() {
		return *reinterpret_cast<CActorAnimation**>(this + 0x13B8);
	}
	CAnimationGraphState* GetAnimationGraphState() {
		return v_spoof<CAnimationGraphState*>(this, 304);
	}
	CEntity* GetEntity() {
		return *reinterpret_cast<CEntity**>(this + 0x10);
	}
	CGameObject* GetGameObject() {
		return *reinterpret_cast<CGameObject**>(this + 0x18);
	}
	__int8 physCounter() {
		return *reinterpret_cast<__int8*>(this + 0xCE4);
	}
	bool m_inSpawnAnimation() {
		return *reinterpret_cast<bool*>(this + 0x1424);
	}
	unsigned __int64 GetTeamId() {
		return *reinterpret_cast<unsigned __int64*>(this + 0x3E0);
	}
	unsigned __int64 GetEntityId() {
		return *reinterpret_cast<unsigned __int64*>(this + 0x20);
	}
	bool IsDead() {
		auto health = v_spoof<int>(this, 0xE0);
		return health <= 0;
	}
	unsigned int IsTriggerID()
	{
		unsigned int i = *(unsigned int*)(unsigned int(this + 0x18));
		if (!i) return 0;
		unsigned int i_1 = *(unsigned int*)(unsigned int(i + 0x68));
		if (!i_1) return 0;
		unsigned int i_2 = *(unsigned int*)(unsigned int(i_1 + 0x20));
		if (!i_2) return 0;
		return  *(unsigned int*)(unsigned int(i_2 + 0x170));
	}
};
#endif // !CActor_hpp
