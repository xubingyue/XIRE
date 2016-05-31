#pragma once
 
#include "EventArgs.h"

#include <functional>
#include <vector>
 
NS_Begin(XIRE)

template <class T>  
struct XIREAPI EventHandler
{
public: 

	typedef std::function<void(void*, EventArgs<T>)> Delegate;

	std::vector<Delegate> Delegates;

	void operator+=(Delegate callback)
	{
		AddDelegate(callback);
	}

	void operator-=(Delegate callback)
	{
		RemoveDelegate(callback);
	}

	void operator()(void *sender, T *data)
	{
		this->TriggerCallback(sender, data);
	}

	bool IsNull()
	{
		return Delegates.size() == 0;
	}

protected:

	void AddDelegate(Delegate callback)
	{
		Delegates.push_back(callback);
	}

	void RemoveDelegate(Delegate callback)
	{
		Delegates.erase(callback);
	} 

	void TriggerCallback(void *sender, T *data)
	{ 
		std::vector<Delegate>::iterator it;
		for (it = Delegates.begin(); it != Delegates.end(); ++it)
		{
			EventArgs<T> e(data);
			(*it)(sender, e);
			if (e.Handled == true)
			{
				break;
			} 
		}
	} 
}; 

NS_End(XIRE)

