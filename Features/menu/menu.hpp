#pragma once
#ifndef menu_hpp
#define menu_hpp
#include "../../classes/CGameStartup.hpp"
#include <string>
#include <strsafe.h>
#include "../../imports/imports.hpp"
#include <vector>
Multihit mh;
WallHack wh;
struct CButton;

enum ElemTypes : DWORD {
	eCheckBox = 1,
	/*eSelectKey,
	eCrool,
	eCroolI,
	eComboList,
	eScroolI,
	TextBox*/
};

#define ButtonColor 0xFF222222
#define ButtonBorderColor 0xFF505050
#define ButtonTextColor 0xFFBFBFBF
#define HeightObject	20.0f
#define BtnWidth		20.0f


int correct = 0;

struct CElements {
	CElements(std::string Caption, int Type, int* pValue, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), Enabled(Enabled) {}
	CElements(std::string Caption, int Type, std::vector<CElements*> Elements, int* pValue, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), Elements(Elements), Enabled(Enabled) {}


	CElements(std::string Caption, int Type, int* pValue, std::vector<std::string> Strings, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), Strings(Strings), Enabled(Enabled) {}

	CElements(std::string Caption, int Type, int* pValue, int iMin, int* iPtrMax, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), iMin(iMin), iPtrMax(iPtrMax), PtrMaxEnabled(1), Enabled(Enabled) {}
	CElements(std::string Caption, int Type, int* pValue, int iMin, int iMax, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), iMin(iMin), iMax(iMax), Enabled(Enabled) {}
	CElements(std::string Caption, int Type, int* pValue, float fMin, float fMax, BOOLEAN Enabled = 1) : Caption(Caption), Type(Type), pValue(pValue), fMin(fMin), fMax(fMax), Enabled(Enabled) {}

	static int GetSize(std::vector<CElements*> Elements) {
		int idx = 0;
		for (size_t i = 0; i < Elements.size(); i++) {
			if (Elements[i]->Type != ElemTypes::eCheckBox || *Elements[i]->pValue > 0)
				idx += GetSize(Elements[i]->Elements);
			++idx;
		}
		return idx;
	}
	static int GetSize(CElements* Elem, std::vector<CElements*> Elements) {//���� ��������
		int idx = 0;
		if (Elem->Type != ElemTypes::eCheckBox || *Elem->pValue > 0)
			for (size_t i = 0; i < Elements.size(); i++) {
				if (Elements[i]->Type != ElemTypes::eCheckBox || *Elements[i]->pValue > 0)
					idx += GetSize(Elements[i]->Elements);
				++idx;
			}
		return idx;
	}
	static int GetSizeBtn(CButton* Elem, std::vector<CElements*> Elements) {//���� ��������
		int idx = 0;
		for (size_t i = 0; i < Elements.size(); i++) {
			if (Elements[i]->Type != ElemTypes::eCheckBox || *Elements[i]->pValue > 0)
				idx += GetSize(Elements[i]->Elements);
			++idx;
		}
		return idx;
	}

	std::string Caption;
	int Type;
	int iMin, iMax;
	int* iPtrMax;
	float fMin, fMax;
	int* pValue;
	BOOLEAN Enabled, SelectKeyTicked, PtrMaxEnabled;
	std::vector<CElements*> Elements;
	std::vector<std::string> Strings;

};
struct CButton {
	CButton(std::string Caption, BOOLEAN Enabled = 1) : Caption(Caption), Enabled(Enabled) {}
	CButton(std::string Caption, std::vector<CElements*> Elements, BOOLEAN Enabled = 1) : Caption(Caption), Elements(Elements), Enabled(Enabled) {}
	std::string Caption;
	std::vector<CElements*> Elements;
	BOOLEAN Enabled;
};
struct CMain {
	CMain(float x, float y, float w, std::string Caption, BOOLEAN Move_Enabled = 0, BOOLEAN Showed = 0) : x(x), y(y), w(w), Caption(Caption), Move_Enabled(Move_Enabled), Showed(Showed) {}
	CMain(float x, float y, float w, std::string Caption, std::vector<CButton*> Buttons, BOOLEAN Move_Enabled = 0, BOOLEAN Showed = 0) : x(x), y(y), w(w), Caption(Caption), Buttons(Buttons), Move_Enabled(Move_Enabled), Showed(Showed) {}

	void CreateButton(CButton* Button) { Buttons.push_back(Button); }
	std::string Caption;
	std::vector<CButton*> Buttons;
	int ButtonOpened;
	float x, y, w;
	BOOLEAN Move_Enabled, Showed;
};
class CRender {
public:
	CRender(IUIDraw* _m_pDraw) {
		this->m_pDraw = _m_pDraw;
		_x = _y = __y = 20.0f;
		_w = 300.0f;
	}
	void render_Border(float x, float y, float w, float h, DWORD color);
	void render_Box(float x, float y, float w, float h, DWORD color);

	bool xIsInBox(float x, float y, float w, float h);

	void DrawLRBox(float x, float y, float w, float h, bool Active = false);

	void CreateMain(CMain* Main) { Mains.push_back(Main); }

	void DrawCheckBox(float x, float y, float w, float h, int* bVar);
	void Draw();
	float DrawElements(float x, float y, float w, CElements* Elem);


	IUIDraw* m_pDraw;
private:
	std::vector<CMain*> Mains;
	float _x, _y, _w;
	float __y;
};
extern CRender* Render;
struct VIRTUALKEY {
	UINT uiKey;
	PCHAR szKey;
};
extern VIRTUALKEY VirtualKeyTable[];
enum {
	VKTSize = 113// sizeof(VirtualKeyTable) / sizeof(VIRTUALKEY) - 1
};
CRender* Render = nullptr;

DWORD MainBoxColor = 0xFF6A5ACD;
DWORD MainBorderColor = 0xFFfffffffd;
DWORD MainHeadTextColor = 0xFF6C6C6C;

struct D3DTLVERTEX {
	D3DTLVERTEX(float X, float Y, float Z, DWORD Color) : x(X), y(Y), z(Z), color(Color) {};
	float x;
	float y;
	float z;
	float rhw = 2.0f;
	DWORD color;
};

void CRender::render_Border(float x, float y, float w, float h, DWORD color) {
	m_pDraw->DrawBorder(x, y, w, h, 1.f, color);
}

void CRender::render_Box(float x, float y, float w, float h, DWORD color) {
	m_pDraw->DrawQuadSimple(x, y, w, h, color);
}
bool CRender::xIsInBox(float x, float y, float w, float h) {
	POINT MousePosition;
	GetCursorPos(&MousePosition);
	ScreenToClient(GetForegroundWindow(), &MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}
void CRender::DrawLRBox(float x, float y, float w, float h, bool Active) {
	DWORD BoxColor = MainBoxColor;
	if (Active) BoxColor = 0xFF6495ED;
	else if (xIsInBox(x + 1, y + 1, w - 2, h - 2)) BoxColor = 0xFFff0092;
	render_Box(x, y, 5, h, BoxColor);
	render_Border(x, y, 5, h, MainBorderColor);
	render_Box(x + w - 5, y, 5, h, BoxColor);
	render_Border(x + w - 5, y, 5, h, MainBorderColor);
}
VOID CRender::DrawCheckBox(float x, float y, float w, float h, int* bVar) {
	if (xIsInBox(x, y, w, h) && (f_get_async_key_state(VK_LBUTTON) & 1)) *bVar = !*bVar;
	render_Box(x, y + 2, w, h, 0xFFfffffffb);
	switch (*bVar)
	{
	case 0: render_Box(x, y + 2, w / 2, h, 0xFFe6ebe7); break;
	case 1: render_Box(x + w / 2, y + 2, w / 2, h, 0xFF595c5a); break;
	}
	render_Border(x, y + 2, w, h, MainBorderColor);
}
float CRender::DrawElements(float x, float y, float w, CElements* Elem) {
	int szElem = CElements::GetSize(Elem, Elem->Elements);
	float h = 23.0f + szElem * 23.0f + szElem * 5.0f;
	float _y = y;
	render_Box(x, y, w, h, MainBoxColor);
	render_Border(x, y, w, h, MainBorderColor);
	DrawLRBox(x, y, w, h);
	m_pDraw->DrawString(x + 10, y + HeightObject / 2 - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_LEFT, Elem->Caption.c_str());

	switch (Elem->Type)
	{
	case ElemTypes::eCheckBox:
		render_Border(x + w - 80 - 10, y + 2 + 2, 80, HeightObject - 4, MainBorderColor);
		DrawCheckBox(x + w - 80 - 10, y + 2, 80, HeightObject - 4, Elem->pValue);
		break;
	/*case ElemTypes::eCrool:
		if (*Elem->pValue > 0 && xIsInBox(x + w - 140, y + 1, 20, h - 2) && (GetAsyncKeyState(VK_LBUTTON) & 1))--*Elem->pValue;
		if (*Elem->pValue < Elem->Strings.size() - 1 && xIsInBox(x + w - 030, y + 1, 20, h - 2) && (GetAsyncKeyState(VK_LBUTTON) & 1))++*Elem->pValue;
		m_pDraw->DrawStringW(x + w - 120, y + HeightObject / 2.0f, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_RIGHT, XORWSTR(L"<<"));
		m_pDraw->DrawStringW(x + w - 30, y + HeightObject / 2.0f, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_LEFT, XORWSTR(L">>"));
		m_pDraw->DrawStringW(x + w - 30 - 45, y + HeightObject / 2.0f, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, Elem->Strings[*Elem->pValue].c_str());
		break;
	case ElemTypes::eScroolI:
		if (*Elem->pValue > (Elem->PtrMaxEnabled ? *Elem->iPtrMax : Elem->iMax)) *Elem->pValue = (Elem->PtrMaxEnabled ? *Elem->iPtrMax : Elem->iMax);
		if (*Elem->pValue < Elem->iMin) *Elem->pValue = Elem->iMin;
		if (*Elem->pValue > Elem->iMin && xIsInBox(x + w - 140, y + 1, 20, h - 2) && (GetAsyncKeyState(VK_LBUTTON) & 1))--*Elem->pValue;
		if (*Elem->pValue < (Elem->PtrMaxEnabled ? *Elem->iPtrMax : Elem->iMax) && xIsInBox(x + w - 030, y + 1, 20, h - 2) && (GetAsyncKeyState(VK_LBUTTON) & 1))++*Elem->pValue;
		m_pDraw->DrawStringW(x + w - 120, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_RIGHT, XORWSTR(L"<<"));
		m_pDraw->DrawStringW(x + w - 30, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_LEFT, XORWSTR(L">>"));
		m_pDraw->DrawStringW(x + w - 30 - 45, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, XORWSTR(L"%d"), Elem->pValue);
		break;
	case ElemTypes::eCroolI: {
		x += 50.0f;
		w -= 60.0f;

		POINT CursorPos;
		GetCursorPos(&CursorPos);
		ScreenToClient(GetForegroundWindow(), &CursorPos);
		render_Box(x, y, w, h, 0xFF10232E);

		if (*Elem->pValue > Elem->iMax) *Elem->pValue = Elem->iMax;
		if (*Elem->pValue < Elem->iMin) *Elem->pValue = Elem->iMin;

		int valueW = ((*Elem->pValue - Elem->iMin) * w / (Elem->iMax - Elem->iMin));
		if ((CursorPos.x >= x && CursorPos.x <= x + w && CursorPos.y >= y && CursorPos.y <= y + HeightObject) && GetKeyState(VK_LBUTTON) < 0)
			*Elem->pValue = (CursorPos.x - x) * (Elem->iMax - Elem->iMin) / w + 1;

		render_Box(x, y, valueW, HeightObject + 2, 0xFFFF3031);
		render_Border(x, y, w, HeightObject + 2, MainBorderColor);
		m_pDraw->DrawStringW(x + w / 2, y + HeightObject / 2, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, XORWSTR(L"%d"), *Elem->pValue);

		x -= 50.0f;
		w += 60.0f;

	}break;
	case ElemTypes::eSelectKey: {
		render_Box(x + w - 130, y + 2, 120, HeightObject - 4, 0xFF10232E);
		render_Border(x + w - 130, y + 2, 120, HeightObject - 4, MainBorderColor);
		if (Elem->SelectKeyTicked) {
			for (int i = 0; i < VKTSize; i++) {
				if (f_get_async_key_state(VirtualKeyTable[i].uiKey) & 0x8000) {
					*Elem->pValue = i;
					m_pDraw->DrawStringW(x + w - 70, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, XORWSTR(L"�������: %s"), VirtualKeyTable[*Elem->pValue].szKey);
					Elem->SelectKeyTicked = false;
					break;
				}
				else m_pDraw->DrawStringW(x + w - 70, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, XORWSTR(L"[������� �������]"));
			}
		}
		else {
			if (xIsInBox(x + w - 130, y + 2, 120, HeightObject - 4) && (f_get_async_key_state(VK_LBUTTON) & 1)) {
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Elem->SelectKeyTicked = true;
			}
			m_pDraw->DrawStringW(x + w - 70, y + HeightObject / 2.0f - 8, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, XORWSTR(L"�������: %s"), VirtualKeyTable[*Elem->pValue].szKey);
		}
	}break;
	case ElemTypes::eComboList:

		break;*/
	}
	_y += 23.0f;

	if (Elem->Type != ElemTypes::eCheckBox || *Elem->pValue > 0) {
		for (int i = 0; i < Elem->Elements.size(); i++) {
			_y += DrawElements(x + 10, _y, w - 20.0f, Elem->Elements[i]);
		}
	}
	return _y - y + 5.0f;
}
void CRender::Draw() {
	for (int i = 0; i < Mains.size(); i++) {//����� ����
		float x = Mains[i]->x, y = Mains[i]->y, w = Mains[i]->w;
		render_Box(x, y, w, HeightObject, MainBoxColor);
		render_Border(x, y, w, HeightObject, MainBorderColor);
		m_pDraw->DrawString(x + w / 2, y + HeightObject / 2, 16.5f, ColorB(240, 248, 255), TextFlags::TEXT_CENTERED, Mains[i]->Caption.c_str());
		DrawLRBox(x, y, w, HeightObject);
		for (int BtnId = 0; BtnId < Mains[i]->Buttons.size(); BtnId++) {
			CButton* Btn = Mains[i]->Buttons[BtnId];
			y += 22.0f;
			if (Mains[i]->ButtonOpened != BtnId && xIsInBox(x, y, w, HeightObject) && (f_get_async_key_state(VK_LBUTTON) & 1)) Mains[i]->ButtonOpened = BtnId;
			render_Box(x, y, w, HeightObject, MainBoxColor);
			render_Border(x, y, w, HeightObject, MainBorderColor);
			DrawLRBox(x, y, w, HeightObject, Mains[i]->ButtonOpened == BtnId);
			m_pDraw->DrawString(x + w / 2, y + HeightObject / 2, 16.5f, ColorB(240, 248, 255), TextFlags::TEXT_CENTERED, Btn->Caption.c_str());

			if (Mains[i]->ButtonOpened == BtnId) {//������ ����
				float _x = x + w + 5.0f, _y = Mains[i]->y, _w = 350.0f;
				if (Btn->Elements.size()) {
					render_Box(_x, _y, _w, HeightObject, MainBoxColor);
					render_Border(_x, _y, _w, HeightObject, MainBorderColor);
					m_pDraw->DrawString(_x + _w / 2, _y + HeightObject / 2, 16.5f, ColorB(240, 248, 255), TextFlags::TEXT_CENTERED, Btn->Caption.c_str());
					DrawLRBox(_x, _y, _w, HeightObject);
					_y += 22.0f;
				}

				for (int ElemId = 0; ElemId < Btn->Elements.size(); ElemId++) {//���������� ��� �������� ����
					if (ElemId > 0) render_Box(_x, _y - 4, _w, 4, MainBoxColor);
					_y += DrawElements(_x, _y, _w, Btn->Elements[ElemId]);// ��������� ������ ���.��������� ������� �������
				}
			}
		}
	}
	if (f_get_async_key_state(VK_LBUTTON)) return;
}
VIRTUALKEY VirtualKeyTable[] = {
	{ VK_LBUTTON },
	{ VK_RBUTTON },
	{ VK_CANCEL },
	{ VK_MBUTTON },
	{ VK_BACK },
	{ VK_NUMPAD0 },
	{ VK_NUMPAD1 },
	{ VK_NUMPAD2 },
	{ VK_NUMPAD3 },
	{ VK_NUMPAD4 }, // 72
	{ VK_NUMPAD5 },
	{ VK_NUMPAD6 },
	{ VK_NUMPAD7 },
	{ VK_NUMPAD8 },
	{ VK_NUMPAD9 },
	{ VK_SEPARATOR },
	{ VK_SUBTRACT },
	{ VK_DECIMAL },
	{ VK_DIVIDE },
	{ VK_F1 },
	{ VK_F2 },
	{ VK_F3 },
	{ VK_F4 },
	{ VK_F5 },
	{ VK_F6 },
	{ VK_F7 },
	{ VK_F8 },
	{ VK_F9 },
	{ VK_F10 },
	{ VK_F11 },
	{ VK_F12 },
	{ VK_F13 },
	{ VK_F14 },
	{ VK_F15 },
	{ VK_F16 },
	{ VK_F17 },
	{ VK_F18 },
	{ VK_F19 },
	{ VK_F20 },
	{ VK_F21 },
	{ VK_F22 },
	{ VK_F23 },
	{ VK_F24 },
	{ VK_NUMLOCK },
	{ VK_SCROLL},
	{ VK_LSHIFT },
	{ VK_RSHIFT },
	{ VK_LCONTROL },
	{ VK_RCONTROL },
	{ VK_LMENU },
	{ VK_RMENU },
	{ VK_PLAY },
	{ VK_ZOOM },
	//{ VK_XBUTTON1, "XBtn1" },
	//{ VK_XBUTTON2, "XBtn2" },
};
#define POSButtonBox(x) 23+90*x
#define POSCheckBox(y) 7+19*y
#define POSTargetScrollBox(y) 7+19*y


class Menu
:public IGameFrameworkListener 
{
	bool show;
public:
	void OnPostUpdate(float) {
		IUIDraw* Draw = CGameStartup::sm_game_startup()->GetGame()->GetCryAction()->GetIUIDraw();

		if ((f_get_async_key_state(VK_HOME) & 1) || (f_get_async_key_state(VK_END) & 1) || (f_get_async_key_state(VK_INSERT) & 1)) show = !show;
		if (show) {
			Draw->PreRender();
			if (!Render) {
				Render = new CRender(Draw);
				Render->CreateMain(
					new CMain(20.0f, 20.0f, 150.0f, XORSTR("Owner pve"), {
					//new CButton(L"Weapon",{
					//		//new CElements(L"Анти-отдача", ElemTypes::eCheckBox, &IFun.CRecoil),
					//		//new CElements(L"Анти-разброс", ElemTypes::eCheckBox, &IFun.CScatter),
					//		//new CElements(L"Анти-затвор", ElemTypes::eCheckBox, &IFun.CShutter),
					//		////new CElements(L"Быстрый нож", ElemTypes::eCheckBox, &IFun.СKnife),//Xspam
					//		//new CElements(L"Быстрая перезарядка", ElemTypes::eCheckBox, &IFun.CReloadAmmo),

					//	}),
						new CButton("Visuals", {
							new CElements("Силуэты врагов ", ElemTypes::eCheckBox, &wh.wallhack),
							new CElements("Nickname / CLasses ", ElemTypes::eCheckBox, &wh.Debug),
							}),
							new CButton(XORSTR("Aim"), {
									new CElements(XORSTR("Settings Multihit"), ElemTypes::eCheckBox, {
									new CElements(XORSTR("Eneble Multihit"), ElemTypes::eCheckBox, &mh.aim),//ExtrimHits
									new CElements(XORSTR("Wallshot"), ElemTypes::eCheckBox, &mh.wallshot),//ExtrimHits
									new CElements(XORSTR("Hits Object"), ElemTypes::eCheckBox,{
									new CElements(XORSTR("Drone Blackwood [H]"), ElemTypes::eCheckBox, &mh.Blackwood_Drone),//+
									new CElements(XORSTR("Argus [V]"), ElemTypes::eCheckBox, &mh.Blackwood_Argus),//+
									new CElements(XORSTR("KillJugger [H]"), ElemTypes::eCheckBox, &mh.killJug),//+
									new CElements(XORSTR("Objects [V/B] "), ElemTypes::eCheckBox, &mh.object),//+
									new CElements(XORSTR("Fyord Boss [V]"), ElemTypes::eCheckBox, &mh.Fyord_Boss),//+
									new CElements(XORSTR("Helicopter"), ElemTypes::eCheckBox, &mh.Heist_Helicopter),//+
									new CElements(XORSTR("Hive"), ElemTypes::eCheckBox, &mh.Swarm_Hive),//+
									new CElements(XORSTR("Fire Room [V]"), ElemTypes::eCheckBox, &mh.Swarm_Fire),//+
									new CElements(XORSTR("QueenSwarm [V]"), ElemTypes::eCheckBox, &mh.Swarm_QueenSwarm),//+
									},&mh.show_aim_targets),
									},&mh.CAim),
							}),
							//new CButton(L"Дополнительно", {
							//	
							//	}),
							//	new CButton(L"Телепорт", {
							//		/*new CElements(L"Включить телепорт ", ElemTypes::eCheckBox, {
							//		new CElements(L"Щит 1", ElemTypes::eCheckBox, &IFun.Teleport1),
							//		new CElements(L"Щит 2", ElemTypes::eCheckBox, &IFun.Teleport2),
							//		new CElements(L"Щит 3", ElemTypes::eCheckBox, &IFun.Teleport3),


							//		},&IFun.CEnableTP),
							//	new CElements(L"<<При телепорте отключать аим!>>", ElemTypes::TextBox,  &IFun.Text),
							//	new CElements(L"<<И взять в руки нож>>", ElemTypes::TextBox,  &IFun.Text),*/
							//	}),
								//new CButton(L"PVP", {
								//	/*new CElements(L"AutoShot", ElemTypes::eCheckBox, &IFun.CAutoshot),
								//	new CElements(L"WallHack", ElemTypes::eCheckBox, &IFun.CSilhouettesEnemy),*/



								//}),
						}, 1, 1)
						);
					}
			}
			if (f_get_async_key_state(VK_HOME) & 1) show = !show;
			//Draw->DrawString(15,15, 16.5f, ColorB(191, 191, 191), TextFlags::TEXT_CENTERED, "%i", correct);
			if (show) Render->Draw();
			Draw->PostRender();
	}
};
#endif // !menu_hpp
