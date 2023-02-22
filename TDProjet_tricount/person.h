#pragma once
#include "tdprojet-tricount.h"

class person
{
private:
	IDENTITY _identity;
	MONEY _receivable;
	EVENT_LIST _events;
public:
	person(IDENTITY id = IDENTITY("Alex","Lucas"), MONEY rcv = 0, EVENT_LIST events = EVENT_LIST());

};

