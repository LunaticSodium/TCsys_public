#include "event.h"


event::event(EVENT_ID id = -1, MONEY amount = 0, std::string name = "Default", REVERSE rvs = false, std::string contest = "No details found")
{

}


std::pair<event, event> event::generateEventPair(EVENT_LIST& list, event event1, int num1, event event2, int num2)
{
	bool error = num1 < 1 || num2 < 1;
	if (error) return ;

}


event event::generateEventCounter(event event1)
{

}

