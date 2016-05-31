#pragma once

#include "XIRE_Afx.h"

#include <process.h>

NS_Begin(XIRE)

class Thread
{
public:

	Thread() : m_hThread(INVALID_HANDLE_VALUE) {}

	virtual ~Thread()
	{
		if (m_hThread != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(m_hThread);
		}
	}

	HANDLE GetHandle() const;

	void Wait() const;

	bool Wait(DWORD timeoutMillis) const;

	void Start();

	virtual int Run() = 0;

	void Terminate(
		DWORD exitCode = 0);

private: 

	static unsigned int __stdcall ThreadFunction(void *pV);

	HANDLE m_hThread;

	// No copies do not implement
	Thread(const Thread &rhs);

	Thread &operator=(const Thread &rhs);
};

inline HANDLE Thread::GetHandle() const
{
	return m_hThread;
}

inline void Thread::Start()
{
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		unsigned int threadID = 0;

		m_hThread = (HANDLE)::_beginthreadex(0, 0, ThreadFunction, (void*)this, 0, &threadID);

		if (m_hThread == INVALID_HANDLE_VALUE)
		{

		}
	}
	else
	{

	}
}

inline void Thread::Wait() const
{
	if (!Wait(INFINITE))
	{

	}
}

inline bool Thread::Wait(DWORD timeoutMillis) const
{

	bool ok;

	DWORD result = ::WaitForSingleObject(m_hThread, timeoutMillis);
	if (result == WAIT_TIMEOUT)
	{
		ok = false;
	}
	else if (result == WAIT_OBJECT_0)
	{
		ok = true;
	}
	else
	{

	}

	return ok;
}

inline unsigned int __stdcall Thread::ThreadFunction(void *pV)
{
	int result = 0;

	Thread* pThis = (Thread*)pV;

	if (pThis)
	{
		try
		{
			result = pThis->Run();
		}
		catch (...)
		{
		}
	}

	return result;
}

inline void Thread::Terminate(DWORD exitCode)
{
	if (!::TerminateThread(m_hThread, exitCode))
	{

	}
}

NS_End(XIRE)