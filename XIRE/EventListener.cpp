#include "EventListener.h"
#include <algorithm>

NS_Using(XIRE)
 
EventListener::EventListener(void *parent)
	:Root(parent)
{

}

EventListener::~EventListener()
{ 

}
	
void EventListener::RegisterEventListener(const U32& type)
{
	/*
	if (type & ET_KeyBoardEvent)
	{
		std::vector<EventListener*> _delegates = RegisteredDelegates[ET_KeyBoardEvent];
		auto itr = std::find(_delegates.begin(), _delegates.end(), this);
		if (_delegates.end() == itr)
		{
			RegisteredDelegates[ET_KeyBoardEvent].push_back(this); 
		} 
	}

	if (type & ET_MouseEvent)
	{
		std::vector<EventListener*> _delegates = RegisteredDelegates[ET_MouseEvent];
		auto itr = std::find(_delegates.begin(), _delegates.end(), this);
		if (_delegates.end() == itr)
		{
			RegisteredDelegates[ET_MouseEvent].push_back(this);
		}
	}

	if (type & ET_MiscEvent)
	{
		std::vector<EventListener*> _delegates = RegisteredDelegates[ET_MiscEvent];
		auto itr = std::find(_delegates.begin(), _delegates.end(), this);
		if (_delegates.end() == itr)
		{
			RegisteredDelegates[ET_MiscEvent].push_back(this);
		}
	}*/
	registeredEventType |= type;
}

void EventListener::RemoveEventListener(const U32 &type)
{
	registeredEventType &= ~type;

	//if (type & ET_KeyBoardEvent)
	//{
	//	/*std::vector<EventListener*> _delegates = RegisteredDelegates[ET_KeyBoardEvent];
	//	auto itr = std::find(_delegates.begin(), _delegates.end(), this);
	//	if (_delegates.end() != itr)
	//	{
	//		RegisteredDelegates[ET_KeyBoardEvent].erase(itr);
	//	}*/ 
	//}

	//if (type & ET_MouseEvent)
	//{
	//	/*std::vector<EventListener*> _delegates = RegisteredDelegates[ET_MouseEvent];
	//	auto itr = std::find(_delegates.begin(), _delegates.end(), this);
	//	if (_delegates.end() != itr)
	//	{
	//		RegisteredDelegates[ET_MouseEvent].erase(itr);
	//	}*/
	//}

	//if (type & ET_MiscEvent)
	//{
	//	/*std::vector<EventListener*> _delegates = RegisteredDelegates[ET_MiscEvent];
	//	auto itr = std::find(_delegates.begin(), _delegates.end(), this);
	//	if (_delegates.end() != itr)
	//	{
	//		RegisteredDelegates[ET_MiscEvent].erase(itr);
	//	}*/
	//}
}

void EventListener::DispatchEvent()
{

}