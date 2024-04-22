#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

                𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CEntitySystem_hpp
#define CEntitySystem_hpp
#include "CEntityIterator.hpp"
#include "../syscall/spoof_call.hpp"
class CPhysicalEntity;
class CEntitySystem {
public:
    virtual ~CEntitySystem() {}//0
    virtual void Relese() = 0;//1
    virtual void OnNetworkGameSync(unsigned int syncType) = 0;//2
    virtual void PrePhysicsUpdate() = 0;//3
    virtual void Update() = 0;//4
    virtual void Reset() = 0;//5
    virtual void Unload() = 0;//6
    virtual void DeletePendingEntities() = 0;//7
    virtual void Function8(); //
    virtual void Function9(); //
    virtual void Function10(); //
    virtual CEntity* GetEntity(unsigned __int64 id) = 0; //
    virtual void Function12(); //
    virtual void Function13(); //
    virtual void Function14(); //
    virtual void Function15(); //
    virtual void Function16(); //
    virtual void Function17(); //
    virtual void Function18(); //
    virtual void Function19(); //by classname
    virtual void Function20(); //by class
    virtual CEntityIterator* GetEntityIterator() = 0; //
    virtual void Function22(); //
    virtual void Function23(); //
    virtual void Function24(); //
    virtual void Function25(); //
    virtual void Function26(); //
	CEntity* GetEntityFromPhysics(CPhysicalEntity* pPhysEntity) {
        
		return v_spoof<CEntity*>(this, 0xD0, pPhysEntity);
        
	}
};
#endif // !CEntitySystem_hpp
