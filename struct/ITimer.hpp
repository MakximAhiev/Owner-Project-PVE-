#pragma once
#ifndef ITimer_hpp
#define ITimer_hpp
#include "CTimeValue.hpp"
struct ITimer {
    struct tm
    {
        int tm_sec;   // seconds after the minute - [0, 60] including leap second
        int tm_min;   // minutes after the hour - [0, 59]
        int tm_hour;  // hours since midnight - [0, 23]
        int tm_mday;  // day of the month - [1, 31]
        int tm_mon;   // months since January - [0, 11]
        int tm_year;  // years since 1900
        int tm_wday;  // days since Sunday - [0, 6]
        int tm_yday;  // days since January 1 - [0, 365]
        int tm_isdst; // daylight savings time flag
    };

    enum ETimer
    {
        ETIMER_GAME,
        ETIMER_UI,
        ETIMER_LAST,
    };
    virtual ~ITimer() = 0;//0
    virtual void ResetTimer() = 0;//1
    virtual void UpdateOnFrameStart() = 0;//2
    virtual float GetCurrTime(ETimer which = ETIMER_GAME) const = 0;//3
    virtual const CTimeValue& GetFrameStartTime(ETimer which = ETIMER_GAME) const = 0;//4
    virtual CTimeValue GetAsyncTime() const = 0;//5
    virtual float GetAsyncCurTime() = 0;//6
    virtual float GetFrameTime(ETimer which = ETIMER_GAME) const = 0;//7
    virtual float GetRealFrameTime() const = 0;//8
    virtual float GetTimeScale() const = 0;//9
    virtual void SetTimeScale(float s) = 0;//10
    virtual void EnableTimer(const bool bEnable) = 0;//11
    virtual bool IsTimerEnabled() const = 0;//12
    virtual float GetFrameRate() = 0;//13
    virtual float GetProfileFrameBlending(float* pfBlendTime = 0, int* piBlendMode = 0) = 0;//14
    virtual void Serialize(struct TSerialize ser) = 0;//15
    virtual bool PauseTimer(ETimer which, bool bPause) = 0;//16
    virtual bool IsTimerPaused(ETimer which) = 0;//17
    virtual bool SetTimer(ETimer which, float timeInSeconds) = 0;//18
    virtual void SecondsToDateUTC(__int64 time, struct tm& outDateUTC) = 0;//19
    virtual __int64 DateToSecondsUTC(struct tm& timePtr) = 0;//20
    virtual float TicksToMillis(unsigned __int64 ticks) const = 0;//21
    virtual float TicksToSeconds(unsigned __int64 ticks) = 0;//22
    virtual ITimer* CreateNewTimer() = 0;//23
};
#endif // !ITimer_hpp
