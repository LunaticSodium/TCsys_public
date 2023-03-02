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

vector<vector<string>> tcsys::_readAll()
{
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::in);
	vector<vector<string>> parts;	
	streampos end = _end();

	_file.seekg(0, ios::beg);

	while (_file.tellg() < end)parts.push_back(_read());

	return parts;
}//finish

void tcsys::_transfer(vector<string> part)
{
	int i = 0;
	while (part[i].empty() && i < part.size() - 1) i++;					//jump over the empty line
	string parttype= part[i++];
	/*
	switch (parttype)													ONLY available for c++ 17+ to use switch with string. So c++ 14, by default, won't compile successfully
	{																	so we'll do it in the boring old way to make sure anyone can compile it
	case "bill":
	{
		ID trid = stoul(part[i++]);
		MONEY tramount = stof(part[i++]);
		string trname = part[i++];
		REVERSE trrvs = part[i++] == "true";
		string trcontest = part[i++];
		bill trbill(trid, tramount, trname, trrvs, trcontest);
		_p().blpool.push_back(trbill);
		break;
	}
	case "person":
	{
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
		if (!alreadyinpersonbase) _personbase.push_back(trperson);		//don't worry the capital or ss, we just use the name in person base
		break;
	}
	case "pool":
	{
		_cpn = stoi(part[i++]);
		break;
	}
	default:
	{
		cout << "key word " << parttype << " transfer failed";
		break;
	}
	while (part[i].empty() && i < part.size()) i++;
	if (part[i] != "end" && _file.tellg()<_end())
	{
		vector<string> nextpart(part.begin() + i, part.end());
		_transfer(nextpart);
	}
	return;
	*/

	PARTTYPE pt = PARTTYPE::DF;
	if (parttype == "bill") pt = PARTTYPE::BL;
	else if (parttype == "person") pt = PARTTYPE::PS;
	else if (parttype == "pool") pt = PARTTYPE::PL;
	switch (pt)
	{
		case PARTTYPE::BL:
		{
			ID trid = stoul(part[i++]);
			MONEY tramount = stof(part[i++]);
			string trname = part[i++];
			REVERSE trrvs = part[i++] == "1";
			string trcontest = part[i++];
			bill trbill(trid, tramount, trname, trrvs, trcontest);
			_p().blpool.push_back(trbill);
			break;
		}
		case PARTTYPE::PS:
		{
			IDENTITY tridtt(part[i++], part[i++]);
			MONEY trcapital = 0;
#ifndef CAPITAL_IGNORE
			trcapital = stof(part[i++]);
#endif // !CAPITAL_IGNORE.											As we def the CAP, trc is 0. remember that this would cause different datafile between ver def/ndef be UNCOMPATIBLE
			stringstream ss(part[i++]);
			ID_LIST tridlist;
			int trid = -1;
			while (ss >> trid) tridlist.push_back(trid);
			person trperson(tridtt, trcapital, tridlist);
			_p().pspool.push_back(trperson);
			bool alreadyinpersonbase = false;
			for (const person& ps : _personbase) if (ps.getIdentity() == tridtt) //for (int j = 0; j < _personbase.size(); j++) if (_personbase[j].getIdentity() == tridtt)
			{
				alreadyinpersonbase = true;
			}
			if (!alreadyinpersonbase) _personbase.push_back(trperson);		//don't worry the capital or ss, we just use the name in person base
			break;
		}
		case PARTTYPE::PL:
		{
			_cpn = stoi(part[i++]);
			break;
		}
		case PARTTYPE::DF:
		{
			cout << "key word " << parttype << " transfer failed";
			break;
		}
		default:
		{
			cout << " enum switcher error : PARTTYPE";
			break;
		}
	}
	while (part[i].empty() && i < part.size() - 1) i++;
	if (part[i] != "end" && _file.tellg()<_end())
	{
		vector<string> nextpart(part.begin() + i, part.end());
		_transfer(nextpart);
	}
	return;
}//finish



void tcsys::_regist(bill bl)//i wish i have a generic type but i dont. I have no power here
{
	_file << "bill\n";
	_file << bl.getEventID() << '\n';
	_file << bl.getAmount() << '\n';
	_file << bl.getName() << '\n';
	_file << bl.doesReverse() << '\n';
	_file << bl.getContest() << '\n';
	_file << "end\n\n";
	return;
}//finish

void tcsys::_regist(person ps)
{
	_file << "person\n";
	_file << ps.getIdentity().first << '\n';
	_file << ps.getIdentity().second << '\n';
#ifndef CAPITAL_IGNORE
	_file << ps.getCapital() << '\n';
#endif // !CAPITAL_IGNORE
	for (int i = 0; i < ps.getBills().size(); i++)
	{
		_file << ps.getBills()[i] << ' ';
	}
	_file << '\n';
	_file << "end\n\n";
	return;
}//finish

void tcsys::_regist(ID pl_id)//will change the _cpn to pl_id
{
	_file << "pool\n";
	_file << pl_id << '\n';
	_file << "end\n\n";
	_cpn = pl_id;
	return;
}//finish

void tcsys::_registOne(void)//without Type T ,genetic or <any>.type(), which is totally a overkill, we use function overload. 
{
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::out | ios::app);
	_regist();
	return;
}

void tcsys::_registOne(bill bl)
{
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::out | ios::app);
	_regist(bl);
	return;
}

void tcsys::_registOne(person ps)
{
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::out | ios::app);
	_regist(ps);
	return;
}

void tcsys::_registOne(ID pl_id)
{
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::out | ios::app);
	_regist(pl_id);
	return;
}

void tcsys::_registAll()
{
	ID cpn = _cpn;
	if (_file.is_open()) _file.close();
	_file.open(DATAFILENAME, ios::out | ios::trunc);
	for (const POOL& pl : _pool)
	{										_regist(pl.pl_id);
		for (const person& ps : pl.pspool)	_regist(ps);
		for (const bill& bl : pl.blpool)	_regist(bl);
	}
	_regist(cpn);
	//_cpn = cpn;
	return;
}//finish



int tcsys::_initTcsys()
{
	_file.open(DATAFILENAME);
	if (!_file.is_open())
	{
		cout << "datafile open failed ";
		return 1;
	}
	vector<vector<string>> parts = _readAll();
	for (int i = 0; i < parts.size(); i++) _transfer(parts[i]);
	return 0;
}//finish

#ifndef ANDROID_DEPLOY
void tcsys::_copy(string txt)//copy in windows, rely on <Windows.h>
{
	if (!OpenClipboard(nullptr)) return;
	if (!EmptyClipboard()) {
		CloseClipboard();
		return;
	}
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, txt.size() + 1);
	if (!hMem) {
		CloseClipboard();
		return;
	}
	char* pMem = static_cast<char*>(GlobalLock(hMem));
	if (!pMem) {
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}
	std::strcpy(pMem, txt.c_str());
	GlobalUnlock(hMem);
	if (!SetClipboardData(CF_TEXT, hMem)) {
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}
	CloseClipboard();
	return;
}
#else
void tcsys::_copy(string txt)//copy in android
{
	return;
}
#endif // !ANDROID_DEPLOY



tcsys::tcsys()
{
	_cpn = 0;
	_ursp = 0;
	_exchangerate = 1;
	_if_exchanged = false;
	_select = POOL();
	_pool = vector<POOL>();
	_undoredo = vector<POOL>();
	_personbase = PERSON_LIST();
	_initTcsys();
}//finish

tcsys::~tcsys()
{
	_registAll();
	_file.close();
}//finish



void tcsys::newPerson(string firstname, string lastname, MONEY rcv)
{
	person ps(IDENTITY(firstname, lastname), rcv);
	_p().pspool.push_back(ps);
	_registOne(ps);
	return;
}//finish

void tcsys::selectPerson(string firstname, string lastname)
{
	for (person& ps : _p().pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)_select.pspool.push_back(ps);
	return;
}//finish

void tcsys::unSelectPerson(string firstname, string lastname)
{
	for (int i = 0; i < _select.pspool.size(); i++) if (_select.pspool[i].getIdentity().first == firstname && _select.pspool[i].getIdentity().second == lastname)_select.pspool.erase(_select.pspool.begin() + i);
	return;
}//finish

void tcsys::removePerson()
{
	string firstname, lastname;
	for (person& ps : _select.pspool)
	{
		firstname = ps.getIdentity().first;
		lastname = ps.getIdentity().second;
		for (int i = 0; i < _p().pspool.size(); i++) if (_p().pspool[i].getIdentity().first == firstname && _p().pspool[i].getIdentity().second == lastname)_p().pspool.erase(_select.pspool.begin() + i);
	}
	_select.pspool.clear();
	_registAll();
	return;
}//finish

void tcsys::clearSelectedPerson()
{
	_select.pspool.clear();
	return;
}//finish

void tcsys::copyPersonalBill()
{
	string firstname, lastname, bills;
	for (person& ps : _select.pspool)
	{
		firstname = ps.getIdentity().first;
		lastname = ps.getIdentity().second;
		for (person& ps : _p().pspool) if (ps.getIdentity().first == firstname && ps.getIdentity().second == lastname)
		{
			bills += ps.printBill(_p().blpool);

		}
	}
	_copy(bills);
#ifdef DEBUG
	cout << bills;
#endif // DEBUG
	return;
}//finish

void tcsys::newPool()
{
	POOL pl;
	pl.pl_id = _pool.size();
	_pool.push_back(pl);
	_registOne(pl.pl_id);
	return;
}//finish

void tcsys::deletePool(ID pl_id)
{
	_pool.erase(_pool.begin() + pl_id);
	for (POOL pl : _pool) if (pl.pl_id > pl_id) pl.pl_id -= 1;
	if (_cpn > pl_id) _cpn -= 1;
	return;
}//finish

void tcsys::switchPool(ID pl_id)
{
	_registOne(pl_id);
	return;
}//finish

void tcsys::setExchangeRate(MONEY rate)
{
	_exchangerate = rate;
	return;
}//finish

void tcsys::exchange()
{
	for (POOL pl : _pool) for (bill bl : pl.blpool) bl.setAmount(bl.getAmount() * _exchangerate);
	_exchangerate = 1 / _exchangerate;
	_if_exchanged = !_if_exchanged;
	return;
}//finish

