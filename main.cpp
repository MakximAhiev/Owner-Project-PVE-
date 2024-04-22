/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#pragma data_seg()
#pragma comment(linker, "/merge:.CRT=.rdata") 
#pragma comment(linker, "/merge:.rdata=.text")  

#include "Features/Visual.hpp"
#include "Features/Weapon.hpp"
#include "Features/Aim.hpp"
#include "imports/imports.hpp"

void* operator new(size_t size) noexcept
{
	return crt::f_malloc(size);
}
void* operator new[](size_t size) noexcept
	{
		return crt::f_malloc(size);
	}

void operator delete(void* data) noexcept
{
	crt::f_free(data);
}
void operator delete(void* data, size_t size) noexcept
{
	crt::f_free(data);
}
void operator delete[](void* data) noexcept
{
	crt::f_free(data);
}
void operator delete[](void* data, size_t size) noexcept
{
	crt::f_free(data);
}

int DllMain(void*, int a1, void*) {
	if (a1 == 1) {
		set_spoof_stub(find_pattern(XORSTR("FF 27")));
		CGameStartup::sm_game_startup()->GetGame()->GetCryAction()->RegisterListener(new Visual(), 0, EFRAMEWORKLISTENERPRIORITY::FRAMEWORKLISTENERPRIORITY_DEFAULT);
		//CGameStartup::sm_game_startup()->GetGame()->GetCryAction()->RegisterListener(new Weapon(), 0, EFRAMEWORKLISTENERPRIORITY::FRAMEWORKLISTENERPRIORITY_DEFAULT);		
		CGameStartup::sm_game_startup()->GetGame()->GetCryAction()->RegisterListener(new Aim(), 0, EFRAMEWORKLISTENERPRIORITY::FRAMEWORKLISTENERPRIORITY_DEFAULT);
	}
	
	return true;
}