#pragma once
//#include "tdprojet-tricount.h"
#include "bill.h"

class person
{
private:


	IDENTITY _identity;
	ID_LIST _events;
public:
#ifndef CAPITAL_IGNORE
	MONEY capital = 0;
	//could always be 0 for convinience. That present how much he have already paid so should be minus from his debt. 
	//But we could totally use a bill to include that so as i do
#endif // !CAPITAL_IGNORE

	//person(IDENTITY id = IDENTITY("Alex", "Socrate"), MONEY rcv = 0, ID_LIST events = ID_LIST());
	person(IDENTITY id, ID_LIST events = ID_LIST()) : _identity(id), _events(std::move(events)) {};
	void receiveConstuit(const MONEY rcv);
	IDENTITY getIdentity() const { return _identity; };
	void setIdentity(const IDENTITY newidentity);
	ID_LIST getBills() const { return _events; };
	void participe(const bill bl);
	void participe(const ID bl_id);
	std::string printBill(const BILL_LIST bllist) const;
	MONEY getCapital(const BILL_LIST bllist) const;																//and so we could find his capital
};

