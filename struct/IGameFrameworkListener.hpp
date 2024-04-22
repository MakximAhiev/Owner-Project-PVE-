#pragma once
#ifndef IGameFrameworkListener_hpp
#define IGameFrameworkListener_hpp
#include "SActionEvent.hpp"
struct IGameFrameworkListener
{
	virtual ~IGameFrameworkListener() {};
	virtual void OnPostUpdate(float fDeltaTime) {};
	virtual void OnSaveGame(struct ISaveGame* pSaveGame) {};
	virtual void OnLoadGame(struct ILoadGame* pLoadGame) {};
	virtual void OnLevelEnd(const char* nextLevel) {};
	virtual void OnActionEvent(SActionEvent& event) {};
	virtual void OnPreRender() {};
};
#endif // !IGameFrameworkListener_hpp
