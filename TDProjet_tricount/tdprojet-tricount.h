#pragma once
//For public def. Move to bill.h

#include <string>
#include <vector>
class bill;
class person;

typedef std::pair<std::string, std::string> IDENTITY;
typedef float MONEY;
typedef unsigned int ID;
typedef std::vector<bill> BILL_LIST;
typedef bool REVERSE;

