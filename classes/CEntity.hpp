#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CEntity_hpp
#define CEntity_hpp
#include "../enum/EEntityProxy.hpp"
#include "CEntityClass.hpp"
#include "CScriptProxy.hpp"
#include "../math/AABB.hpp"
#include "../math/Matrix34.hpp"
#include "CCharacterInstance.hpp"
#include "../syscall/spoof_call.hpp"

class CEntity {
public:
	unsigned __int64 GetEntityId() {
		return v_spoof<unsigned __int64>(this, 0x8);
	}
	const char* GetName() {
		return v_spoof<const char*>(this, 0x60);
	}
	void GetWolrdBounds(AABB& bbox) {
		v_spoof<void>(this, 0xC8, bbox);
	}
	bool IsHidden() {
		return v_spoof<bool>(this, 0x178);
	}
	CCharacterInstance* GetCharacterIstance(int slot) {
		return v_spoof<CCharacterInstance*>(this, 0x2A0, slot);
	}
	Vec3& GetPos() {
		return v_spoof<Vec3&>(this, 0xE0);
	}
	class CRenderProxy* GetEntityRenderProxy(EEntityProxy proxy) {
		return v_spoof<CRenderProxy*>(this, 0x1D8, proxy);
	}
	CScriptProxy* GetScriptProxy() {
		return (CScriptProxy*)GetEntityRenderProxy(EEntityProxy::ENTITY_PROXY_SCRIPT);
	}
	Matrix34& GetWorldTM() {
		return v_spoof<Matrix34&>(this, 0xB8);
	}
	Matrix34& GetProjectedWorldBBox() {
		return v_spoof<Matrix34&>(this, 0x70);
	}
	CEntityClass* GetEntityClass() {
		return v_spoof<CEntityClass*>(this, 0x18);
	}
	class CMaterial* GetMaterial() {
		return v_spoof<CMaterial*>(this, 0x230);
	}
};
#endif // !CEntity_hpp
