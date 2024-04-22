#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef Aim_hpp
#define Aim_hpp
#include "../classes/CGameStartup.hpp"
#include "../enum/HitType.hpp"
#include "../struct/STimerState.hpp"
#include "../enum/HitMaterialId.hpp"
#include "../enum/EKey.hpp"
#include <vector>
using namespace std;
class Aim
	: public IGameFrameworkListener {
public:
	void OnPreRender() {
		this->StartAim();
	}
private:
	bool IsEnemyTeam(CActor* mActor, CActor* pActor)
	{
		return (mActor != pActor) && (mActor->GetTeamId() > 0) && (mActor->GetTeamId() != pActor->GetTeamId());
	}
	bool check_actor(CActor* pClientActor, CActor* pActor)
	{
		return (pActor == pClientActor);
	}
	Vec3 GetBonePosID(CEntity* pExp, CSkeletonPose* m_pSkeleton, int vBoneId)
	{
		return pExp->GetWorldTM() * m_pSkeleton->GetAbsJointByID(vBoneId).t;
	}

	struct SvRequestShootHit {
		struct RequestHit {
			RequestHit(unsigned int targetId, int material, int type, int partId, Vec3 pos, float damageReduction, char physCounter)
				: targetId(targetId), material(material), typeId(type), partId(partId), pos(pos), damageReduction(damageReduction), physCounter(physCounter) {}
			unsigned int targetId; // 0x00
			int material; // 0x04
			int typeId; // 0x08
			int partId; // 0x0C
			Vec3 pos; // 0x10
			float damageReduction; // 0x1C
			char physCounter; // 0x20
		};

		Vec3 shootPos; // 0x00
		int predictionHandle; // 0x0C
		Vec3 dir; // 0x10
		char physCounter; // 0x1C
		std::vector<pair<unsigned int, std::vector<RequestHit>>> projectiles; // 0x20
		char fireCounter; // 0x38
		float spreadMax; // 0x3C
		char b_0x40; // 0x40
		char pad_0x41[7]; // 0x41
		__int64 prevTimestamp; // 0x48
		__int64 timestamp; // 0x50
		int dw_0x58; // 0x58
		int pAmmoCount; // 0x5C
		Vec3 vDirFire; // 0x60
	};

	int GetBoned(CSkeletonPose* m_pSkeletone, const char* name, const char* className, CEntity* pEntity) {

		if (m_strstr(name, XORSTR("Drone_MG"))) return 12;
		if (m_strstr(name, XORSTR("ZSD_Crusher"))) return 15;
		if (f_get_key_state(F10) && m_strstr(name, XORSTR("Iron"))) return 9;
		if (m_strstr(name, XORSTR("ZSD_Destroyer"))) return 75;
		if (!m_strcmp(className, XORSTR("SEDSoldier"))) return m_pSkeletone->GetJointIdName(XORSTR("Bip01 L Calf"));
		if (m_strstr(name, XORSTR("HeavyTurret"))) return m_pSkeletone->GetJointIdName(XORSTR("bone_hitpoint"));
		if (m_strstr(name, XORSTR("HeavyDroid"))) return m_pSkeletone->GetJointIdName(XORSTR("Bip01 R ForeArm"));
		if (m_strstr(name, XORSTR("_Droid_"))) return m_pSkeletone->GetJointIdName(XORSTR("Box001"));
		if (m_strstr(name, XORSTR("_Flagship_Artillery"))
			|| m_strstr(name, XORSTR("_Flagship_MainArtillery"))) return m_pSkeletone->GetJointIdName(XORSTR("weaponPos_law"));
		if (m_strstr(name, XORSTR("JP_Flamethrower"))) return m_pSkeletone->GetJointIdName(XORSTR("Bip01 Neck"));
		if (m_strstr(name, XORSTR("Destroyer"))) return 9;
		if (m_strstr(name, XORSTR("Turret"))) return m_pSkeletone->GetJointIdName(XORSTR("bone_head"));
		if (!m_strcmp(className, XORSTR("BugMelee")) && m_strstr(name, XORSTR("Bug_Melee"))) return m_pSkeletone->GetJointIdName(XORSTR("$bugs_range_hitpoint1"));	//Beetle fighter (Swarm)
		if (!m_strcmp(className, XORSTR("BugMelee")) && m_strstr(name, XORSTR("Bug_Kamikaze"))) return m_pSkeletone->GetJointIdName(XORSTR("Sphere001"));			//Kamikaze Beetle (Swarm)
		if (!m_strcmp(className, XORSTR("BugRanged")) && m_strstr(name, XORSTR("Bug_Range"))) return m_pSkeletone->GetJointIdName(XORSTR("$physics_Bip01_Spine"));	//Arrow Beetle (Swarm)
		if (!m_strcmp(className, XORSTR("TurretBug")) && m_strstr(name, XORSTR("TurretFloor"))) return m_pSkeletone->GetJointIdName(XORSTR("$physicsproxy_03"));	//Predatory flower (Swarm)
		return m_pSkeletone->GetJointIdName(XORSTR("Bip01 Head"));

	}
	int GetMaterial(CGameRules* pGameRules, const char* name, const char* className) {
		if (m_strstr(name, XORSTR("Iron")) || m_strstr(name, XORSTR("TurretWall")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint1"));
		if (m_strstr(name, XORSTR("TurretWall"))
			|| m_strstr(name, XORSTR("Drone_MG"))
			|| m_strstr(name, XORSTR("MID_T_MG")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint1"));
		if (f_get_key_state(F10) && m_strstr(name, XORSTR("Iron")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint1"));
		if (m_strstr(name, XORSTR("Turret"))
			|| m_strstr(name, XORSTR("_Flagship_MainArtillery"))
			|| m_strstr(name, XORSTR("_Flagship_Artillery"))
			|| m_strstr(name, XORSTR("MID_T_Heavy"))
			|| m_strstr(name, XORSTR("MID_T_ASR")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint3"));
		if (m_strstr(name, XORSTR("Droid")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_head_droid"));
		if (m_strstr(name, XORSTR("AIZSD.Crusher.ZSD_Crusher")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_head"));
		if (m_strstr(name, XORSTR("AIZSD.Destroyer.ZSD_Destroyer")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_head"));
		if (m_strstr(name, XORSTR("SEDSoldier"))
			|| m_strstr(name, XORSTR("SEDAssault"))
			|| m_strstr(name, XORSTR("Flamethrower")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint2"));
		if (m_strstr(name, XORSTR("TurretRail"))
			|| m_strstr(name, XORSTR("HeavyTurret"))
			|| m_strstr(name, XORSTR("TurretCeil"))
			|| m_strstr(name, XORSTR("TurretFloor"))
			|| m_strstr(name, XORSTR("Turret_MG"))
			|| m_strstr(name, XORSTR("Turret_ASR"))
			|| m_strstr(name, XORSTR("Turret_Ceil"))
			|| m_strstr(name, XORSTR("Turret_CQB"))
			|| m_strstr(name, XORSTR("TurretHunt"))
			|| m_strstr(name, XORSTR("_Flagship_Artillery"))
			|| m_strstr(name, XORSTR("MID_T_Heavy"))
			|| m_strstr(name, XORSTR("MID_T_MG"))
			|| m_strstr(name, XORSTR("MID_T_ASR"))
			|| m_strstr(name, XORSTR("_Flagship_MainArtillery")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_hitpoint3"));

		if (m_strstr(name, XORSTR("TurretAPC"))
			|| m_strstr(name, XORSTR(".Drone.")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_metal"));

		if (m_strstr(name, XORSTR("HeavyDroid"))
			|| m_strstr(name, XORSTR("_Droid_")))
			return pGameRules->RegisterHitMaterial(XORSTR("mat_head_droid"));
		if (!m_strcmp(className, XORSTR("BugMelee")) && m_strstr(name, XORSTR("Bug_Melee"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head_arachnid"));	//Beetle fighter (Swarm)
		if (!m_strcmp(className, XORSTR("BugMelee")) && m_strstr(name, XORSTR("Bug_Kamikaze"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head_arachnid"));	//Kamikaze Beetle (Swarm)
		if (!m_strcmp(className, XORSTR("BugRanged")) && m_strstr(name, XORSTR("Bug_Range"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head_arachnid"));	//Arrow Beetle (Swarm)
		if (!m_strcmp(className, XORSTR("TurretBug")) && m_strstr(name, XORSTR("TurretFloor"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head_arachnid")); //Predatory flower (Swarm)
		if (m_strstr(name, XORSTR("Destroyer"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head"));
		if (m_strstr(name, XORSTR("Crusher"))) return pGameRules->RegisterHitMaterial(XORSTR("mat_head"));
		return pGameRules->RegisterHitMaterial(XORSTR("mat_head"));
	}
	bool Entity(CGameRules* pGameRules, CEntity* pEntity, CCompoundCharacter* pActorCC, const char* name, const char* Animation, const char* className, int& boneId, Vec3& bonePosition, int& material) {

		if (!m_strcmp(className, XORSTR("Mantis")) || m_strstr(name, XORSTR("mech2300"))
			|| m_strstr(name, XORSTR("Black_Wolf")) || m_strstr(name, XORSTR("Mech2300"))
			|| m_strstr(name, XORSTR("Tank_Turret")) || !m_strcmp(className, XORSTR("Helicopter")) || m_strstr(name, XORSTR("Helicopter"))) return false;
		if (m_strstr(name, XORSTR("HeavyDroid")) && (m_strstr(Animation, XORSTR("hit_reaction"))
			|| m_strstr(Animation, XORSTR("X_Spawn")) || !m_strstr(Animation, XORSTR("X_combat_")))) return false;
		if (m_strstr(Animation, XORSTR("hit_reaction")) && (m_strstr(name, XORSTR("SEDAssault")) || m_strstr(name, XORSTR("Flamethrower")))) return false;
		if (m_strstr(Animation, XORSTR("fixedLoc")) && (m_strstr(name, XORSTR("Shield")))) return false;
		if (!m_strcmp(className, XORSTR("SEDTeleporter"))) {
			if (m_strstr(Animation, XORSTR("hit_reaction")) || m_strstr(Animation, XORSTR("interaction_action"))
				|| m_strstr(Animation, XORSTR("X_Stun_finiher")) || m_strstr(Animation, XORSTR("SpawnRappelAssault"))
				|| m_strstr(Animation, XORSTR("SpawnRifle_R_01")) || m_strstr(Animation, XORSTR("x_stealth_MoveToIdle"))) return false;
		}

		if (!pActorCC->GetInstance()) return false;
		auto pSkeleton = pActorCC->GetInstance()->GetSkeletonPose();

		boneId = GetBoned(pSkeleton, name, className, pEntity);
		if (!boneId) return false;

		bonePosition = GetBonePosID(pEntity, pSkeleton, boneId);

		material = GetMaterial(pGameRules, name, className);
		if (!material) return false;

		return true;

	}
	SvRequestShootHit request;
	void update(Vec3 ShootPos, CActor* pClient) {

		request.shootPos = ShootPos;
		request.physCounter = pClient->physCounter();
		request.dw_0x58 = 1;
		request.dir = request.vDirFire = { 0, 0, 1 };

	}
	void AddProjectile(std::vector<SvRequestShootHit::RequestHit> hits) {

		request.pAmmoCount = 1;
		request.projectiles.push_back({ 1, hits });

	}
	void clear() {

		for (auto it = request.projectiles.begin(); it != request.projectiles.end(); ++it) it->second.clear();
		request.projectiles.clear();

	}
	void RequestShootHit(CItemProxy* pItemProxy) {

		if (pItemProxy && !request.projectiles.empty()) {
			spoof_call(
				(PVOID)0x1414960F0,
				pItemProxy->GetGameObject(),
				*(PVOID*)0x14269E848,
				&request,
				256,
				-1
			);
		}

	}
	STimerState hitsTimer;

	void StartAim() {

		auto pEnv = CGameStartup::sm_game_startup(); if (!pEnv) return;

		auto pGame = pEnv->GetGame(); if (!pGame) return;

		auto pCryAction = pGame->GetCryAction(); if (!pCryAction) return;

		auto pActorSystem = pCryAction->GetActorSystem(); if (!pActorSystem) return;

		auto pActor = pActorSystem->GetActor(pCryAction->GetClientActorId()); if (!pActor) return;

		auto pEntitySystem = pEnv->GetEntitySystem(); if (!pEntitySystem) return;

		auto pEntityIterator = pEntitySystem->GetEntityIterator(); if (!pEntityIterator) return;

		auto pRenderer = pEnv->GetRenderer(); if (!pRenderer) return;

		auto pGameRules = pCryAction->GetGameRules(); if (!pGameRules) return;

		auto pInventory = pActor->GetInventory(); if (!pInventory) return;

		auto pItemSystem = pCryAction->GetItemSystem(); if (!pItemSystem) return;

		auto pItemProxy = pItemSystem->GetItem(pInventory->GetCurrentItemId()); if (!pItemProxy) return;

		auto pPhysicalWorld = pEnv->GetPhysicsWorld(); if (!pPhysicalWorld) return;

		auto pTimer = pEnv->GetTimer(); if (!pTimer) return;

		auto pWorld = pEnv->GetPhysicsWorld(); if (!pWorld) return;
		const char* mission = pCryAction->GetLevelName();
		hitsTimer.SetFrameTime(pTimer->GetFrameTime());
		hitsTimer.SetDurationTime(8.f);

		Vec3 cameraPos = pRenderer->GetViewCamera(0, 0)->m_Matrix.GetTranslation();
		update(cameraPos, pActor);

		std::vector<SvRequestShootHit::RequestHit> hit;
		AABB aabb;

		while (CEntity* pEntity = pEntityIterator->Next()) {
			/*if (ShouldIgnore(pActor, true)) continue;*/
			if (CActor* mActor = pActorSystem->GetActor(pEntity->GetEntityId())) {
				if (!IsEnemyTeam(pActor, mActor)) continue;
				if (check_actor(pActor, mActor)) continue;

				auto name = pEntity->GetName();
				auto animation = mActor->GetAnimationGraphState()->GetCurrentStateName();
				auto className = pEntity->GetEntityClass()->GetName();
				auto pActorCC = mActor->GetActorCC(); if (!pActorCC) continue;
				pEntity->GetWolrdBounds(aabb);
			
				static int hits = 15;

				
				Vec3 bonePos = { 0,0,0 };
				int idBone = 0;
				int materialId = 0;

				if (mActor->IsDead()) continue;

				if (Entity(pGameRules, pEntity, pActorCC, name, animation, className, idBone, bonePos, materialId)) {
					if (f_get_key_state(F1) || pWorld->isVisible(pEntitySystem, pEntity, cameraPos, bonePos)) {
						hit.push_back(SvRequestShootHit::RequestHit(pActor->GetEntityId(), 12, 6, 12, cameraPos, 0.0f, pActor->physCounter()));
						for (int i = 0; i < 5; ++i) hit.push_back(SvRequestShootHit::RequestHit(pEntity->GetEntityId(), materialId, HitType::bullet, idBone, bonePos, 0.0f, mActor->physCounter()));
						continue;
					}
				}

			}
		}

		if (f_get_key_state(F1)) {
			if (hitsTimer.IsInitTime()) {
				if (!hit.empty()) {
					if (pItemProxy->IsWeapon()) {
						this->AddProjectile(hit);
						this->RequestShootHit(pItemProxy);
						this->clear();
					}
					hitsTimer.ResetTime();

				}
			}
		}
	}
};
#endif // !Aim_hpp
