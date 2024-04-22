/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CPhysicalWorld_hpp
#define CPhysicalWorld_hpp
#include "../math/Vec3.hpp"
#include "../enum/phentity_flags.hpp"
#include "CEntitySystem.hpp"
#include "../imports/imports.hpp"
struct CPhysicalWorld {
public:
	struct ray_hit
	{
		ray_hit() { m_RtlSecureZeroMemory(this, sizeof(*this)); }
		float dist;
		CPhysicalEntity* pCollider;
		int ipart;
		int partid;
		short surface_idx;
		short idmatOrg;
		int foreignIdx;
		int iNode;
		Vec3 pt;
		Vec3 n;
		int bTerrain;
		int iPrim;
		ray_hit* next;
	};
	struct ray_hit_cached : ray_hit
	{
		ray_hit_cached() { pCollider = 0; ipart = 0; }
		ray_hit_cached(const ray_hit& hit)
		{
			pCollider = hit.pCollider; ipart = hit.ipart;
			iNode = hit.iNode;
		}
		ray_hit_cached& operator=(const ray_hit& hit)
		{
			pCollider = hit.pCollider; ipart = hit.ipart;
			iNode = hit.iNode; return *this;
		}
	};

	int RayWorldIntersection(const Vec3& org, const Vec3& dir, int objtypes, unsigned int flags, ray_hit* hits, int nMaxHits, CPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, void* pForeignData = 0, INT iForeignData = 0, const char* pNameTag = "", ray_hit_cached* phitLast = 0, int iCaller = 4)
	{
		return v_spoof<int>(this, 0x310, org, dir, objtypes, flags, hits, nMaxHits, pSkipEnts, nSkipEnts, pForeignData, iForeignData, pNameTag, phitLast, iCaller);		
	}

	bool isVisible(CEntitySystem* pEntitySystem, CEntity* pEntity, Vec3 shootPos, Vec3 pos, CPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, int pierceability = 10) {		
		ray_hit rayhit;
		if (this->RayWorldIntersection(shootPos, pos - shootPos, 1 | 2 | 4 | 256, 0xA0001500 | pierceability, &rayhit, 1, pSkipEnts, nSkipEnts) > 0) {
			return pEntitySystem->GetEntityFromPhysics(rayhit.pCollider) == pEntity;
		}
		return true;		
	}
};
#endif // !CPhysicalWorld_hpp
