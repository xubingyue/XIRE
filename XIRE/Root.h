#pragma once

#include "XIRE_Afx.h"

NS_Begin(XIRE)

class XIREAPI Root
{
public:

	Root(void *parent = nullptr);

	virtual ~Root();

	String Name;

	void *Parent;
};

NS_End(XIRE)