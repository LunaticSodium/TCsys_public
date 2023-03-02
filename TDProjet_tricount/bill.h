#pragma once
//#include "tdprojet-tricount.h"				Already defined all pre-compile order here.

#include <string>
#include <vector>
class bill;
class person;
class billpair;

typedef float MONEY;
typedef unsigned int ID;
typedef bool REVERSE;
typedef std::pair<std::string, std::string> IDENTITY;
typedef std::pair<bill, bill> billpair;
typedef std::vector<bill> BILL_LIST;
typedef std::vector<ID> ID_LIST;
typedef std::vector<person> PERSON_LIST;


class bill
{
private:
	ID _id;										//-1 by default but should NEVER be default.
	MONEY _amount;								//As receivable, gain a positive capital to participater, by default.
	std::string _name;
	REVERSE _rvs;								//True IF positive amount means the owner received from this event and should pay, so gain a negative capital. False by default.
	std::string _contest;

public:
	bill(ID id = -1, MONEY amount = 0, std::string name = "Default", REVERSE rvs = false, std::string contest = "No details found");

	static billpair constructBillPair(BILL_LIST& list, const ID id = -1, const MONEY amount = 0, std::string const name = "Default", REVERSE const rvs = false, std::string const contest = "No details found", int num1 = 1, int num2 = 1);
	static billpair constructBillPair(BILL_LIST& list, const MONEY amount = 0, int num2 = 1,int num1 = 1,  std::string const name = "Default", std::string const contest = "No details found") { return constructBillPair(list, list.back().getEventID() + 1, amount, name, false, contest, num1, num2); };
	//Call the construct function of event and generateEventPair to give a pair which is difined. First sequencedb by natual and second seq by utili.

	static billpair generateEventPair(BILL_LIST& list, const bill bill1, const int num1 = 1, const int num2 = 1, bill bill2 = bill());
	//All the change of eve_list due to event generated should be considered by caller. 
	//This weird sequence is by their importance. Also push the two events into event list. So the return value is not such importante.

	static bill generateEventCounter(BILL_LIST& list, const bill bill1, const int num1, const int num2);
	//To help gEP to always keeps the sum of capital equal 0. Also push the event into event list.

	ID getEventID() const { return _id; };
	std::string getName() const { return _name; };
	std::string getContest() const { return _contest; };
	REVERSE doesReverse() const { return _rvs; };
	MONEY getAmount() const { return _amount; };
	MONEY setAmount(MONEY amount) { _amount = amount; return _amount; };
	MONEY getReceive() const { return _amount * (_rvs ? -1 : 1); };
	std::string &getContest()  { return _contest; };
	std::string setContest(std::string newcontest) { return (_contest = newcontest); };

	std::string selfPrint();
};

/*
class billpair
{
public:
	std::pair<bill, bill> twin;
	billpair(std::pair<bill, bill> pair) { twin = pair; };
	MONEY sum(int num1 = 1, int num2 = 1) { return twin.first.getReceive() * num1 + twin.second.getReceive() * num2; };
};*/

