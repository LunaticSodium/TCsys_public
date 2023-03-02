#include "person.h"

person::person(IDENTITY id, MONEY rcv, ID_LIST events)
{
	_identity = id;
	_events = events;

#ifndef CAPITAL_IGNORE
	_capital = 0;
#endif // !CAPITAL_IGNORE

	if (rcv != 0) _receiveConstuit(rcv);
}

void person::_receiveConstuit(const MONEY rcv)
{
	bill bl(0, rcv,"Enter by paid",false,"Created by the construction of person "+_identity.first+" . " +_identity.second);
	participe(bl);
	return;
}

void person::setIdentity(const IDENTITY newidentity)
{
	_identity = newidentity;
	return;
}

void person::participe(const bill bl)
{
	_events.push_back(bl.getEventID());
	//_capital += bl.getReceive();
	return;
}

std::string person::printBill(const BILL_LIST bllist) const
{
	std::string prt;
	BILL_LIST bl_list;
	for (bill bl : bllist) for (int id : _events) if (bl.getEventID() == id) prt += bl.selfPrint();
	return prt;
}

MONEY person::capital(const BILL_LIST bllist) const
{
	MONEY cpt = 0;
	for (bill bl : bllist) for (int id : _events) if (bl.getEventID() == id) cpt += bl.getReceive();
#ifndef CAPITAL_IGNORE
	cpt += _capital;
#endif // !CAPITAL_IGNORE
	return cpt;
}
