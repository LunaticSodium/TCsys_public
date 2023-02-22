#pragma once
//#include "tdprojet-tricount.h"

#include <string>
#include <vector>
class person;

typedef std::pair<std::string, std::string> IDENTITY;
typedef float MONEY;
typedef unsigned int EVENT_ID;
typedef std::vector<event> EVENT_LIST;
typedef bool REVERSE;

class event
{
private:
	EVENT_ID _id;
	MONEY _amount;								//As receivable, gain a positive capital to participater, by default.
	std::string _name;
	REVERSE _rvs;								//TRUE if positive amount means the owner received from this event and should pay so gain a negative capital. False by default.
	std::string _contest;
public:
	event(EVENT_ID id = -1, MONEY amount = 0, std::string name = "Default", REVERSE rvs = false, std::string contest = "No details found");
	static std::pair<event, event> generateEventPair(EVENT_LIST& list, event event1 = event(), int num1 = 1, event event2 = event(), int num2 = 1);
	static event generateEventCounter(event event1);
	MONEY getReceive() const { return _amount; };
	std::string getContest() const { return _contest; };
	std::string setContest(std::string newcontest) { return (_contest = newcontest); };
};

