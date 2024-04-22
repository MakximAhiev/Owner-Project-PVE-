#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef CRenderer_hpp
#define CRenderer_hpp
#include "CCamera.hpp"

class CRenderer {
	struct SProjectToScreen {
		SProjectToScreen() { }
		SProjectToScreen(Vec3_tpl<float> to, Vec3_tpl<float>& out)
			: ptx(to.x), pty(to.y), ptz(to.z), sx(&out.x), sy(&out.y), sz(&out.z) { }

		float ptx;
		float pty;
		float ptz;
		float* sx;
		float* sy;
		float* sz;
	};
public:
	using FN_DrawText = void(__thiscall*)(CRenderer*, float, float, float, const float*, bool, const char*);
	void DrawTextAw(float x, float y, float font_size, const float* col, bool center, const char* label_text, ...) {
		return FN_DrawText(0x14020B6A0)(this, x, y, font_size, col, center, label_text);//48 8B C4 48 83 EC 68 F3 0F 11 58	
	}
	bool ProjectToScreen(SProjectToScreen* proj) {	
		return v_spoof<bool>(this, 0x378, proj);	
	}
	bool WorldToScreen(Vec3_tpl< float > vPos, Vec3_tpl< float >& vOut) {	
		SProjectToScreen pWorldToScreen;

		pWorldToScreen.ptx = vPos.x;
		pWorldToScreen.pty = vPos.y;
		pWorldToScreen.ptz = vPos.z;
		pWorldToScreen.sx = &vOut.x;
		pWorldToScreen.sy = &vOut.y;
		pWorldToScreen.sz = &vOut.z;

		ProjectToScreen(&pWorldToScreen);

		vOut.x *= (r_width() * 0.01f);
		vOut.y *= (r_height() * 0.01f);
		vOut.z *= 1.0f;

		return ((vOut.z < 1.0f) && (vOut.x > 0) && (vOut.x < r_width()) && (vOut.y > 0) && (vOut.y < r_height()));
	}
	/*Vec3 GetViewCamera() {
		return *reinterpret_cast<Vec3*>(this + 0x17C0);
	}*/
	CCamera* GetViewCamera(const CCamera* camera, bool bSet) {
		return v_spoof<CCamera*>(this, 0x218, camera, bSet);
	}
	
private:
	int r_width() {
		return *reinterpret_cast<int*>(this + 0x14B7F8);
	}
	int r_height() {
		return *reinterpret_cast<int*>(this + 0x14B7FC);
	}
};
#endif // !CRenderer_hpp
