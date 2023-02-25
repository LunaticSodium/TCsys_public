#pragma once
#include "tdprojet-tricount.h"
#include "bill.h"

class person
{
private:
	IDENTITY _identity;
	MONEY _capital;
	ID_LIST _events;
	void _receiveConstuit(MONEY rcv);
public:
	person(IDENTITY id = IDENTITY("Alex","Socrate"), MONEY rcv = 0, ID_LIST events = ID_LIST());
	IDENTITY getIdentity() { return _identity; };
	void setIdentity(IDENTITY newidentity);
	void participe(bill bl);
	BILL_LIST findBill(BILL_LIST bllist);
};

