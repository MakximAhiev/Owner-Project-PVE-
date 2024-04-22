#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef EActionEvent_hpp
#define EActionEvent_hpp
enum EActionEvent {

	eAE_channelCreated = 0x0,
	eAE_channelDestroyed = 0x1,
	eAE_connectFailed = 0x2,
	eAE_connected = 0x3,
	eAE_disconnected = 0x4,
	eAE_clientDisconnected = 0x5,
	eAE_resetBegin = 0x6,
	eAE_resetEnd = 0x7,
	eAE_resetProgress = 0x8,
	eAE_preSaveGame = 0x9,
	eAE_postSaveGame = 0xA,
	eAE_inGame = 0xB,
	eAE_serverName = 0xC,
	eAE_serverIp = 0xD,
	eAE_earlyPreUpdate = 0xE,
	eAE_demoRecorderCreated = 0xF,
	eAE_mapCmdIssued = 0x10,
	eAE_unloadLevel = 0x11,
	eAE_postUnloadLevel = 0x12,
	eAE_loadLevel = 0x13,
	eAE_demoRecorderDestroyed = 0x14,
};
#endif // !EActionEvent_hpp
