#include "person.h"

person::person(IDENTITY id, MONEY rcv, ID_LIST events)
{
	_identity = id;
	_events = events;
	_capital = 0;
	if (rcv != 0) _receiveConstuit(rcv);
}


void person::_receiveConstuit(MONEY rcv)
{
	bill bl(0, rcv,"Enter by paid",false,"Created by the construction of person "+_identity.first+" . " +_identity.second);
	participe(bl);
	return;
}


void person::setIdentity(IDENTITY newidentity)
{
	_identity = newidentity;
	return;
}


void person::participe(bill bl)
{
	_events.push_back(bl.getEventID());
	_capital += bl.getReceive();
	return;
}

BILL_LIST person::findBill(BILL_LIST bllist)
{
	BILL_LIST re = BILL_LIST();
	for (int i = 0; i < bllist.size(); i++) for (int j = 0; j < _events.size(); j++) if (bllist[i].getEventID() == _events[j]) re.push_back(bllist[i]);
	return re;
}
