#pragma once
#include "tdprojet-tricount.h"

class event
{
private:
	EVENT_ID _id;
	MONEY _amount;								//Receive by default.
	std::string _name;
	REVERSE _rvs;								//TRUE if positive amount means the owner should pay instead of receive. False by default.
	std::string _contest;
public:
	event(EVENT_ID id = 0, MONEY amount = 0, std::string name = "Default", REVERSE rvs = false, std::string contest = "No details found");
	static std::pair<event, event> generateEventPair(EVENT_LIST& list);
	MONEY getReceive() const ;
	std::string getContest() const { return _contest; };
	std::string setContest(std::string newcontest) { return (_contest = newcontest); };
};

