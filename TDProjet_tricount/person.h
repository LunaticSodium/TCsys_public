#pragma once
//#include "tdprojet-tricount.h"
#include "bill.h"

class person
{
private:

#ifndef CAPITAL_IGNORE
	MONEY _capital;		
	//could always be 0 for convinience. That present how much he have already paid so should be minus from his debt. 
	//But we could totally use a bill to include that so as i do
public:
	MONEY getCapital() { return _capital; };
private:
#endif // !CAPITAL_IGNORE

	IDENTITY _identity;
	ID_LIST _events;
	void _receiveConstuit(const MONEY rcv);
public:
	person(IDENTITY id = IDENTITY("Alex","Socrate"), MONEY rcv = 0, ID_LIST events = ID_LIST());
	IDENTITY getIdentity() const { return _identity; };
	void setIdentity(const IDENTITY newidentity);
	ID_LIST getBills() const { return _events; };
	void participe(const bill bl);
	void participe(const ID bl_id);
	std::string printBill(const BILL_LIST bllist) const;
	MONEY capital(const BILL_LIST bllist) const;																//and so we could find his capital
};

