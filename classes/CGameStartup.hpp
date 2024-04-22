#pragma optimize( "", on )
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CGameStartup_hpp
#define CGameStartup_hpp
#include "CGame.hpp"
#include "CRenderer.hpp"
#include "CEntitySystem.hpp"
#include "CPhysicalWorld.hpp"
#include "../struct/ITimer.hpp"
#include "../syscall/spoof_call.hpp"
class CGameStartup 
{
public:
	CEntitySystem* GetEntitySystem() {		
		return *reinterpret_cast<CEntitySystem**>(this + 0xE0);		
	}
	CRenderer* GetRenderer() {		
		return *reinterpret_cast<CRenderer**>(this + 0x48);		
	}
	CGame* GetGame() {
		return *reinterpret_cast<CGame**>(this + 0xD0);
	}
	CPhysicalWorld* GetPhysicsWorld() {
		return *reinterpret_cast<CPhysicalWorld**>(this + 0x70);
	}
	ITimer* GetTimer() {
		return *reinterpret_cast<ITimer**>(this + 0xC0);
	}
	static CGameStartup* sm_game_startup() {		
		return *reinterpret_cast<CGameStartup**>(0x142401210);		
	}
};
#endif // !CGameStartup_hpp
