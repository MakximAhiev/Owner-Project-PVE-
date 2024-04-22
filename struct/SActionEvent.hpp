#pragma once
#ifndef SActionEvent_hpp
#define SActionEvent_hpp 
#include "../enum/EActionEvent.hpp"
struct SActionEvent {

	EActionEvent m_event;
	int m_value;
	const char* m_description;
};
#endif // !SActionEvent_hpp
