#pragma once

#include "XIRE_Afx.h"
#include "EventHandler.h"
#include <map>
#include <vector>
#include "Root.h"

NS_Begin(XIRE) 

class XIREAPI EventListener : public Root
{
public:

	enum EventType
	{
		ET_KeyBoardEvent = 0x1,
		ET_MouseEvent = 0x1<<1,
		ET_MiscEvent = 0x1<<2
	};

	EventListener();

	virtual ~EventListener(); 

	void RegisterEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);

	void RemoveEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);

	static void DispatchEvent();

private:

	static std::map<EventType, std::vector<EventListener*>> RegisteredDelegates;
};

NS_End(XIRE)