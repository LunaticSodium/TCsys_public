#include "bill.h"


bill::bill(ID id, MONEY amount, std::string name, REVERSE rvs, std::string contest)
{
	_id = id;
	_amount = amount;
	_name = name;
	_rvs = rvs;
	_contest = contest;
}


billpair bill::constructBillPair(BILL_LIST& list, const ID id, const MONEY amount, std::string const name, REVERSE const rvs, std::string const contest, int num1, int num2)
{
	bill eve1(id, amount, name, rvs, contest);
	return generateEventPair(list, eve1, num1, num2);
}


billpair bill::generateEventPair(BILL_LIST& list, const bill event1, const int num1, const int num2, bill event2)
{
	bool error = num1 < 1 || num2 < 1 || event1.getEventID() == -1;
	if (error) return;
	bill eve1 = event1, eve2;
	list.push_back(eve1);
	if (event2.getEventID() == -1)
	{
		eve2 = generateEventCounter(list, eve1, num1, num2);
	}
	else
	{
		list.push_back(eve2);
	}
}


bill bill::generateEventCounter(BILL_LIST& list, const bill event1, const int num1, const int num2)
{
	int id = list.back().getEventID() + 1;
	MONEY amount = event1.getReceive() * num1 / num2;
	bill eve2(id,amount,"Ctr_"+event1.getName(),event1.doesReverse(),"Created by generateEventCounter as a counter of "+event1.getName()+" who's as "+event1.getContest());
	list.push_back(eve2);
	return eve2;
}

