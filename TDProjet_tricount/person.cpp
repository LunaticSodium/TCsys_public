#include "person.h"

person::person(IDENTITY id, MONEY rcv, ID_LIST events)
{
	_identity = id;
	_events = events;
	_capital = 0;
	if (rcv != 0) receiveConstuit(rcv);
}


void person::receiveConstuit(MONEY rcv)
{
	event eve(0, rcv,"Enter by paid",false,"Created by the construction of person "+_identity.first+" . " +_identity.second);
	participe(eve);
	return;
}


void person::setIdentity(IDENTITY newidentity)
{
	_identity = newidentity;
	return;
}


void person::participe(event eve)
{
	_events.push_back(eve);
	_capital += eve.getReceive();
	return;
}