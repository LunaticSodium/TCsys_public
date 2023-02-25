#include "tcsys.h"

/*
File example :

pool
1
end

bill
1
20
dinner
false
just a dinner
end

bill
2
20
dinner
true
as a counter of dinner
end

bill
3
40
lunch
false
meals
end

person
Alexander
Robinson
150
1 3 5 7 10
end


or the same it would work:


pool
1

bill
1
20
dinner
false
just a dinner




bill
2
20
dinner
true
as a counter of dinner

bill
3
40
lunch
false
meals
person
Alexander
Robinson
150
1 3 5 7 10
end

use \end as a \} which doesn't need a \{
*/

streampos tcsys::_end()
{
	streampos gcurrent = _file.tellg();
	_file.seekg(0, ios::end);
	streampos end = _file.tellg();
	_file.seekg(gcurrent);
	return end;
}//finish

vector<string> tcsys::_read()
{
	string line;
	vector<string> part;												//whick start with class name and end with "end", all mini
	int partstartline = -1;
	while (std::getline(_file, line)) {
		if (!line.empty() && line != "end") {
			partstartline = _file.tellg();
			continue;
		}
		if (partstartline != -1) {
			part.push_back(line);
			if (line == "end") break;
		}
	}
	return part;
}//finish

vector<vector<string>> tcsys::_reReadAll()
{
	vector<vector<string>> parts;	
	streampos end = _end();

	_file.seekg(0, ios::beg);

	while (_file.tellg() < end)parts.push_back(_read());

	return parts;
}//finish

void tcsys::_transfer(vector<string> part)
{
	int i = 0;
	string parttype = part[i++];
	switch (parttype)
	{
	case "bill":
		ID trid = stoul(part[i++]);
		MONEY tramount = stof(part[i++]);
		string trname = part[i++];
		REVERSE trrvs = part[i++] == "true";
		string trcontest = part[i++];
		bill trbill(trid, tramount, trname, trrvs, trcontest);
		_p().blpool.push_back(trbill);
		break;
	case "person":
		IDENTITY tridtt(part[i++],part[i++]);
		MONEY trcapital = stof(part[i++]);
		stringstream ss(part[i++]);
		ID_LIST tridlist;
		int trid = -1;
		while (ss >> trid) tridlist.push_back(trid);
		person trperson(tridtt, trcapital, tridlist);
		_p().pspool.push_back(trperson);
		bool alreadyinpersonbase = false;
		for (int j = 0; j < _personbase.size(); j++) if (_personbase[j].getIdentity() == tridtt) alreadyinpersonbase = true;
		if (!alreadyinpersonbase) _personbase.push_back(trperson);//don't worry the capital or ss, we just use the name.
		break;
	case "pool":
		_cpn = stoi(part[i++]);
		break;
	default:
		cout << "key word " << parttype << " transfer failed";
		break;
	}
	while (part[i].empty() && i <) i++;
	if (part[i] != "end" && _file.tellg()<_end())
	{
		vector<string> nextpart(part.begin() + i, part.end());
		_transfer(nextpart);
	}
	return;
}//finish

int tcsys::_initTcsys()
{
	_file.open(DATAFILENAME);
	if (!_file.is_open()) cout << "datafile open failed. \n";
	vector<vector<string>> parts = _reReadAll();
	for (int i = 0; i < parts.size(); i++) _transfer(parts[i]);
	return 0;
}

void tcsys::_write(string str)
{

}

tcsys::tcsys()
{
	_cpn = 0;
	_ursp = 0;
	_pool = vector<POOL>();
	_undoredo = vector<POOL>();
	_personbase = PERSON_LIST();
	_initTcsys();
}

tcsys::~tcsys()
{
	_file.close();
}
