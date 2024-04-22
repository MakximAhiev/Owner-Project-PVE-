#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CItemProxy_hpp
#define CItemProxy_hpp
#include "CWeaponExt.hpp"
#include "../security/xorstr.hpp"
#include "CEntity.hpp"
#include "../imports/imports.hpp"
class CGameObject {
public:
	char pad_0x0000[0x18];
	CEntity* m_pEntity;
};
class CItemProxy {
public:
	
	CWeaponExt* GetWeaponExt() {
		return *reinterpret_cast<CWeaponExt**>(this + 0x30);
	}
	CEntity* GetEntity() {
		return *reinterpret_cast<CEntity**>(this + 0x10);
	}
	CGameObject* GetGameObject() {
		return *reinterpret_cast<CGameObject**>(this + 0x18);
	}
	unsigned __int64 GetEntityId() {		
		return *reinterpret_cast<unsigned __int64*>(this + 0x20);		
	}
	bool IsWeapon()
	{		
		bool IsGun = m_strstr(this->GetEntity()->GetName(), XORSTR("arl")) || m_strstr(this->GetEntity()->GetName(), XORSTR("fl0")) // граник - флешка
			|| m_strstr(this->GetEntity()->GetName(), XORSTR("fg0")) || m_strstr(this->GetEntity()->GetName(), XORSTR("sg0")) // хаешка - смок
			|| m_strstr(this->GetEntity()->GetName(), XORSTR("ap")) || m_strstr(this->GetEntity()->GetName(), XORSTR("mk0")) // патроны на шт - аптечка
			|| m_strstr(this->GetEntity()->GetName(), XORSTR("df0")) || m_strstr(this->GetEntity()->GetName(), XORSTR("cm0")) // дефы на меда - мина
			|| m_strstr(this->GetEntity()->GetName(), XORSTR("ak0")) || m_strstr(this->GetEntity()->GetName(), XORSTR("mcg01")) // ремка инжа - молик
			|| m_strstr(this->GetEntity()->GetName(), XORSTR("kn"));
		if (!IsGun) return 1;
		else return 0;		
	}
};
#endif // !CItemProxy_hpp
