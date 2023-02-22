#pragma once
#include "tdprojet-tricount.h"
#include "event.h"

class person
{
private:
	IDENTITY _identity;
	MONEY _capital;
	EVENT_LIST _events;
	void receiveConstuit(MONEY rcv);
public:
	person(IDENTITY id = IDENTITY("Alex","Socrate"), MONEY rcv = 0, EVENT_LIST events = EVENT_LIST());
	IDENTITY getIdentity() { return _identity; };
	void setIdentity(IDENTITY newidentity);
	void participe(event eve);
};

