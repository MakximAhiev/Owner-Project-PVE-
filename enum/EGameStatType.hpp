﻿/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef EGameStatType_hpp
#define EGameStatType_hpp
enum EGameStatType : short
{
	eGS_InvalidStat = -1,
	eGS_Absorption = 0,
	eGS_Accuracy,
	eGS_ActivateDuration,
	eGS_AimAccuracy,
	eGS_AiSoundRadius,
	eGS_AmmoAmount,
	eGS_ArmorHealth,
	eGS_ArmorRegenHps,
	eGS_ArmorRegenTimeout,
	eGS_ArmsDamageMult,
	eGS_AutoZoomIn,
	eGS_AutoZoomOut,
	eGS_BallisticIronsight,
	eGS_BayonetMeleeDuration,
	eGS_BayonetMeleeOutDuration,
	eGS_BlindAmountMul,
	eGS_BodyDamageMult,
	eGS_BoltAction,
	eGS_BoltActionDuration,
	eGS_BulletPierceability,
	eGS_ClaymoreActivationDelayMul,
	eGS_ClaymoreDetectorRadius,
	eGS_ClipSize,
	eGS_CrouchSpeedMul,
	eGS_CustomizeInDuration,
	eGS_CustomizeOutDuration,
	eGS_Damage,
	eGS_DamageDropMinDistance,
	eGS_DamageDropPerMeter,
	eGS_DamageMin,
	eGS_DamageUnderbarrel,
	eGS_DeselectDuration,
	eGS_DeselectDurationBuff,
	eGS_ExtraAmmoPistolMul,
	eGS_ExtraAmmoPrimaryMul,
	eGS_FireUnderbarrelDuration,
	eGS_FireUnderbarrelOnRelease,
	eGS_FlashbangTimeMul,
	eGS_FovMul,
	eGS_HeadDamageMult,
	eGS_HealthMul,
	eGS_HipAccuracy,
	eGS_HolsterInDuration,
	eGS_HpRegenerationHps,
	eGS_HpRegenerationTimeout,
	eGS_IgnoreBulletBody,
	eGS_SuppressIgnoreBulletBody,
	eGS_IgnoreBulletHead,
	eGS_SuppressIgnoreBulletHead,
	eGS_KnockBackChance,
	eGS_KnockBackMinDistance,
	eGS_KnockBackMaxDistance,
	eGS_KnockBackResistance,
	eGS_KnockBackStaminaDamage,
	eGS_LegsDamageMult,
	eGS_Unk55,
	eGS_Unk56,
	eGS_MeleeDamage,
	eGS_MeleeDuration,
	eGS_MeleeDurationBuff,
	eGS_MeleeKnockBackChance,
	eGS_MeleeKnockBackStaminaDamage,
	eGS_CyborgDamageBuff,
	eGS_MeleeOutDuration,
	eGS_MeleeRadius,
	eGS_MeleeRange,
	eGS_MeleeRes,
	eGS_Range,
	eGS_RclAtt,
	eGS_RclDec,
	eGS_RclDecDelay,
	eGS_RclMax,
	eGS_RclRnd,
	eGS_RclSmth,
	eGS_ReloadDuration,
	eGS_ReloadDurationBuff,
	eGS_ReloadUnderbarrelDuration,
	eGS_ResArms,
	eGS_ResBody,
	eGS_ResHead,
	eGS_ResLegs,
	eGS_Resistance,
	eGS_Rpm,
	eGS_MoveSoundVolumeDamping,
	eGS_SecondaryMeleeDamage,
	eGS_SecondaryMeleeDuration,
	eGS_SecondaryMeleeDurationBuff,
	eGS_SecondaryMeleeOutDuration,
	eGS_SecondaryMeleeRadius,
	eGS_SecondaryMeleeRange,
	eGS_SelectDuration,
	eGS_SelectDurationBuff,
	eGS_SlideDistMul,
	eGS_SplashRes,
	eGS_SprdAtt,
	eGS_SprdDec,
	eGS_SprdDecDelay,
	eGS_SprdMax,
	eGS_SprdMin,
	eGS_SprintSpeedMul,
	eGS_SprintTimeMul,
	eGS_StaminaMul,
	eGS_SwayDec,
	eGS_SwayMinX,
	eGS_SwayMinY,
	eGS_SwaySpeedMult,
	eGS_ThrowDelayDuration,
	eGS_ThrowDuration,
	eGS_ThrowFireDelayDuration,
	eGS_TossDuration,
	eGS_ZoomFactor,
	eGS_ZoomInDuration,
	eGS_ZoomInDurationBuff,
	eGS_ZoomOutDuration,
	eGS_ZoomOutDurationBuff,
	eGS_ZoomedBoltActionDuration,
	eGS_PoisonGrenadeDamageMul,
	eGS_InSlotSelectDuration,
	eGS_InSlotDeselectDuration,
	eGS_UseInSlotWeaponChange,
	eGS_CameraShakeMul,
	eGS_SprdInverted,
	eGS_StrafeMultiplier,
	eGS_ClimbExtraHeight,
	eGS_ArmorAbsorbRatio,
};
#endif // !EGameStatType_hpp
