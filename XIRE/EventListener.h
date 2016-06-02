#pragma once

#include "XIRE_Afx.h"
#include "EventHandler.h"
#include <map>
#include <vector>
#include "Root.h"

NS_Begin(XIRE) 

enum EventType
{
	ET_KeyBoardEvent = 0x1,
	ET_MouseEvent = 0x1<<1,
	ET_MiscEvent = 0x1<<2
};

class XIREAPI EventListener : public Root
{
public:

	typedef std::map<EventType, std::vector<Window*, EventListener*>> EventRegistry;

	EventListener(void *parent = nullptr);

	virtual ~EventListener(); 

	void RegisterEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);

	void RemoveEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);

	static void DispatchEvent();

protected:

	U32 registeredEventType;

private:  


};

NS_End(XIRE)