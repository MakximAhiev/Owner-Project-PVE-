#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

                𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CWeaponExt_hpp
#define CWeaponExt_hpp
#include "CClipMode.hpp"
enum EWeaponStates : __int32 {
    eWS_Disabled = 0x0,
    eWS_Idle = 0x1,
    eWS_IdleZoomed = 0x2,
    eWS_Fire = 0x3,
    eWS_IdleUnderBarrel = 0x4,
    eWS_HoldFireUnderBarrel = 0x5,
    eWS_FireUnderBarrel = 0x6,
    eWS_ReloadUnderBarrel = 0x7,
    eWS_HolsterInDisabled = 0x8,
    eWS_HolsterInUnderBarrel = 0x9,
    eWS_HolsteredUnderBarrel = 0xA,
    eWS_MeleeUnderBarrel = 0xB,
    eWS_ThrowingFire = 0xC,
    eWS_ThrowingFireActivate = 0xD,
    eWS_ZoomedFire = 0xE,
    eWS_ZoomInFire = 0xF,
    eWS_ZoomOutFire = 0x10,
    eWS_Reload = 0x11,
    eWS_ReloadBarrel = 0x12,
    eWS_BoltAction = 0x13,
    eWS_ZoomedBoltAction = 0x14,
    eWS_ZoomIn = 0x15,
    eWS_ZoomOut = 0x16,
    eWS_ZoomOutReloadAuto = 0x17,
    eWS_ZoomOutReloadManual = 0x18,
    eWS_ZoomOutQSA = 0x19,
    eWS_ZoomOutMelee = 0x1A,
    eWS_ZoomOutBoltAction = 0x1B,
    eWS_ZoomOutCustomize = 0x1C,
    eWS_Throwing = 0x1D,
    eWS_Toss = 0x1E,
    eWS_Melee = 0x1F,
    eWS_Select = 0x20,
    eWS_Deselect = 0x21,
    eWS_Holding = 0x22,
    eWS_Activate = 0x23,
    eWS_Customize = 0x24,
    eWS_CustomizeIn = 0x25,
    eWS_CustomizeOut = 0x26,
    eWS_HolsterIn = 0x27,
    eWS_Holstered = 0x28,
    eWS_StartRestoreSelf = 0x29,
    eWS_StartRestoreTeamMate = 0x2A,
    eWS_CancelRestore = 0x2B,
    eWS_RestoreSelf = 0x2C,
    eWS_RestoreTeamMate = 0x2D,
    eWS_TryingRestoreSelf = 0x2E,
    eWS_TryingRestoreTeamMate = 0x2F,
    eWS_DropAmmoPack = 0x30,
    eWS_Resurrect = 0x31,
    eWS_ResetClipAmmo = 0x32,
    eWS_Last = 0x33,
    eWS_Num = 0x33,
};
class CWeaponExt {
public:
	virtual class CWeaponView* GetView() = 0;
    virtual class CWeaponSettings* GetSettings() = 0;
	virtual class CWeaponParameters* GetParameters() = 0;
	virtual class CWeaponAttachment* GetAttachment() = 0;
	virtual class CItemBox* GetItemBox() = 0;
	virtual EWeaponStates GetCurrState() = 0;
};
#endif // !CWeaponExt_hpp
