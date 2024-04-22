#pragma once
#ifndef CSkeletonPose_hpp
#define CSkeletonPose_hpp
#include "../math/QuatT.hpp"
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
class CSkeletonPose {
public:
	QuatT GetAbsJointID(int nJointID) {
		return v_spoof<QuatT>(this, 0x38, nJointID);
	}
	QuatT GetAbsJointByID(int boneID) {
		return *reinterpret_cast<QuatT*>(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x1B8) + 0x1C * boneID); 
	}
	int GetJointIdName(const char* sz_joint_name) {
		return v_spoof<int>(this, 0x18, sz_joint_name);
	}
	unsigned int GetJointCount() {
		return v_spoof<unsigned int>(this, 0x10);
	}
};
#endif // !CSkeletonPose_hpp
